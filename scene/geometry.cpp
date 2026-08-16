#include "geometry.h"
#include "../game.h" // Assuming GameApp is defined here
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <imgui.h>
#include <random>
#include <algorithm>

GeometryScene::GeometryScene(GameApp* gameApp) : Scene(gameApp) {
    // 1. Initialize Player
    player.pos = sf::Vector2f(640.f, 360.f); // Center of 1280x720 window
    player.vel = sf::Vector2f(0.f, 0.f);
    player.speed = 1500.f; // Acceleration rate
    player.radius = 20.f;
    player.health = 100.f;
    player.superMeter = 0.f;
    player.active = true;

    // 2. Pre-allocate Object Pools to prevent vector reallocations
    const int MAX_ENEMIES = 500;
    const int MAX_BULLETS = 1000;
    
    enemies.resize(MAX_ENEMIES);
    bullets.resize(MAX_BULLETS);
    
    // Ensure everything starts inactive in the memory block
    for(auto& e : enemies) e.active = false;
    for(auto& b : bullets) b.active = false;
}

void GeometryScene::manageSpawning(float dt) {
    spawnTimer -= dt;
    if (spawnTimer > 0.0f) return; // Not time to spawn yet

    // 1. DYNAMIC SPAWN RATE: Decreases as score increases
    // At score 0, spawn every 1.0s. At score 10000+, spawn every 0.2s.
    float difficulty = std::min(1.0f, static_cast<float>(player.score) / 10000.0f);
    float currentInterval = 1.0f - (difficulty * 0.8f); 
    spawnTimer = currentInterval;

    // 2. STOCHASTIC RNG SETUP
    // 'static' ensures we don't re-seed the RNG every single frame (which ruins randomness)
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> randFloat(0.0f, 1.0f);
    
    // 3. DYNAMIC PROBABILITY CURVE
    float roll = randFloat(rng);
    roll += (difficulty * 0.5f); // Inflate the roll based on how well the player is doing

    float enemySize;
    if (roll < 0.5f) {
        // Tier 1: Grunt (Radius 15) - Edible! The player (Radius 20) can ram these.
        enemySize = 15.0f; 
    } else if (roll < 0.9f) {
        // Tier 2: Bruiser (Radius 25) - Dangerous! The player will bounce off and take damage.
        enemySize = 25.0f; 
    } else {
        // Tier 3: Juggernaut (Radius 45) - Massive bullet sponges that crowd the screen.
        enemySize = 45.0f; 
    }

    // 4. DETERMINE SPAWN LOCATION
    // Enemies must spawn outside the 1280x720 screen to avoid popping in on the player
    std::uniform_int_distribution<int> sideChoice(0, 3);
    int side = sideChoice(rng);
    sf::Vector2f spawnPos;

    float spawnOffset = 50.0f; // Spawn 50 pixels out of bounds

    if (side == 0) { // Top
        spawnPos = sf::Vector2f(randFloat(rng) * 1280.f, -spawnOffset);
    } else if (side == 1) { // Bottom
        spawnPos = sf::Vector2f(randFloat(rng) * 1280.f, 720.f + spawnOffset);
    } else if (side == 2) { // Left
        spawnPos = sf::Vector2f(-spawnOffset, randFloat(rng) * 720.f);
    } else { // Right
        spawnPos = sf::Vector2f(1280.f + spawnOffset, randFloat(rng) * 720.f);
    }

    // 5. INJECT INTO OBJECT POOL
    spawnEnemy(spawnPos, enemySize);
}
void GeometryScene::spawnEnemy(sf::Vector2f position, float size) {
    for (auto& enemy : enemies) {
        if (!enemy.active) {
            enemy.pos = position;
            enemy.vel = sf::Vector2f(0.f, 0.f);
            enemy.speed = 200.f; // Base enemy speed
            enemy.radius = size;
            enemy.health = size * 2.f; // Larger enemies have more health
            enemy.active = true;
            return; // Bail out after spawning one
        }
    }
}

void GeometryScene::fireBullet(const sf::Vector2f& targetAttackPosition) {
    if (fireCooldown > 0.0f) return;

    // Calculate normalized direction vector: (Target - Player) / ||Target - Player||
    sf::Vector2f dir = normalize(targetAttackPosition - player.pos);
    
    for (auto& bullet : bullets) {
        if (!bullet.active) {
            bullet.pos = player.pos;
            bullet.vel = dir * 800.f; // Bullet velocity scalar
            bullet.speed = 800.f;
            bullet.radius = 5.f;
            bullet.lifeTime = 2.0f; // Bullet dies after 2 seconds
            bullet.active = true;
            
            fireCooldown = FIRE_RATE;
            return;
        }
    }
}

void GeometryScene::superAttack() {
    if (player.superMeter < 100.0f) return;
    
    // Radial burst: Spawn 36 bullets in a 360-degree circle
    int bulletsFired = 0;
    for (auto& bullet : bullets) {
        if (!bullet.active) {
            float angle = (bulletsFired * 10.0f) * (3.14159f / 180.f);
            sf::Vector2f dir(std::cos(angle), std::sin(angle));
            
            bullet.pos = player.pos;
            bullet.vel = dir * 1000.f; 
            bullet.radius = 8.f;
            bullet.lifeTime = 3.0f;
            bullet.active = true;
            
            bulletsFired++;
            if (bulletsFired >= 36) break;
        }
    }
    player.superMeter = 0.0f; // Reset meter
}
void GeometryScene::resolveCollision() {
    // A. Bullet vs Enemy Collisions
    for (auto& bullet : bullets) {
        if (!bullet.active) continue;
        
        for (auto& enemy : enemies) {
            if (!enemy.active) continue;
            
            float dist = getLength(bullet.pos - enemy.pos);
            if (dist < (bullet.radius + enemy.radius)) {
                // Impact!
                enemy.health -= 10.f; 
                bullet.active = false; 
                
                // --- ENEMY DEATH LOGIC ---
                if (enemy.health <= 0.f) {
                    enemy.active = false; // Tombstone the memory slot
                    
                    // Award score based on enemy size (e.g., radius 20 = 200 points)
                    player.score += static_cast<int>(enemy.radius * 10.f);
                    
                    // Increment super meter
                    player.superMeter = std::min(100.0f, player.superMeter + 5.0f);
                }
                break; 
            }
        }
    }

    for (auto& enemy : enemies) {
        if (!enemy.active) continue;
        
        float dist = getLength(player.pos - enemy.pos);
        if (dist < (player.radius + enemy.radius)) {
            if (player.radius > enemy.radius) {
                enemy.active = false;
                
                player.score += static_cast<int>(enemy.radius * 20.f); 
                player.superMeter = std::min(100.0f, player.superMeter + 15.0f);
            } else {
                sf::Vector2f normal = normalize(player.pos - enemy.pos);
                float bounceForce = 800.f; 
                player.vel = normal * bounceForce;
                
                player.health -= 10.f;
                if (player.health <= 0.f) player.active = false;
            }
        }
    }
    
    if (player.pos.x < player.radius) player.pos.x = player.radius;
    if (player.pos.x > 1280.f - player.radius) player.pos.x = 1280.f - player.radius;
    if (player.pos.y < player.radius) player.pos.y = player.radius;
    if (player.pos.y > 720.f - player.radius) player.pos.y = 720.f - player.radius;
}

void GeometryScene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    // Single-fire inputs or window closures go here.
    // Continuous WASD movement is better handled directly in update() via keyboard state.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
        superAttack();        
    }
}

void GeometryScene::determineNextStateOfEnemyAI() {
    // Flocking AI: Enemies steer directly towards the player's current position
    for (auto& enemy : enemies) {
        if (!enemy.active) continue;
        sf::Vector2f dir = normalize(player.pos - enemy.pos);
        enemy.vel = dir * enemy.speed;
    }
}

void GeometryScene::update(float dt) {
    if (!player.active) return; // Game over state

    // 1. Process Player Input (Kinematic Acceleration)
    sf::Vector2f accel(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) accel.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) accel.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) accel.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) accel.x += 1.f;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) accel *= 3.f;
    // 2. Player Kinematics (Applying Friction and Acceleration)
    if (getLength(accel) > 0.f) accel = normalize(accel) * player.speed;
    player.vel += accel * dt;
    player.vel *= 0.95f; // Friction/Drag so player doesn't slide infinitely
    player.pos += player.vel * dt;

    // 3. Shooting Logic
    fireCooldown -= dt;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(app->getWindow());
        fireBullet(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
    }

    // 4. Update Enemies
    determineNextStateOfEnemyAI();
    for (auto& enemy : enemies) {
        if (!enemy.active) continue;
        enemy.pos += enemy.vel * dt;
    }

    // 5. Update Bullets
    for (auto& bullet : bullets) {
        if (!bullet.active) continue;
        bullet.lifeTime -= dt;
        if (bullet.lifeTime <= 0.0f) {
            bullet.active = false;
            continue;
        }
        bullet.pos += bullet.vel * dt;
    }

    // 6. Resolve all spatial interactions
    resolveCollision();
}

void GeometryScene::render(sf::RenderWindow& window) {
    // Instantiate exactly ONE reusable shape to save CPU cycles
    sf::CircleShape shape;

    // 1. Draw Bullets (Rendered first so they stay in the background)
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineThickness(0.0f);
    for (const auto& bullet : bullets) {
        if (!bullet.active) continue;
        
        shape.setRadius(bullet.radius);
        shape.setOrigin({bullet.radius, bullet.radius}); // Center the origin
        shape.setPosition(bullet.pos);
        window.draw(shape);
    }

    // 2. Draw Enemies
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color(150, 0, 0)); // Dark red outline
    for (const auto& enemy : enemies) {
        if (!enemy.active) continue;
        
        shape.setRadius(enemy.radius);
        shape.setOrigin({enemy.radius, enemy.radius});
        shape.setPosition(enemy.pos);
        window.draw(shape);
    }

    // 3. Draw Player (Rendered last so they are always on top)
    if (player.active) {
        shape.setRadius(player.radius);
        shape.setOrigin({player.radius, player.radius});
        shape.setPosition(player.pos);
        shape.setFillColor(sf::Color::Green);
        
        // Visual feedback: Make the player glow cyan when the Super is ready
        if (player.superMeter >= 100.0f) {
            shape.setOutlineThickness(3.0f);
            shape.setOutlineColor(sf::Color::Cyan);
        } else {
            shape.setOutlineThickness(0.0f);
        }
        
        window.draw(shape);
    }
}
#include <imgui.h>

void GeometryScene::renderUI() {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin(
        "Geometry HUD"
        , nullptr
        , ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_AlwaysAutoResize 
        | ImGuiWindowFlags_NoBackground);
    
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "SCORE: %d", player.score);
    ImGui::TextColored(ImVec4(1, 0, 0, 1), "HEALTH: %.0f", player.health);
    
    float superProgress = player.superMeter / 100.0f;
    ImGui::ProgressBar(
        superProgress
        , ImVec2(200.0f, 0.0f)
        , "SUPER ATTACK (Right Click)");

    ImGui::Separator();
    if (ImGui::Button("<- Quit to Menu")) {
        app->changeScene(std::make_unique<MainMenuScene>(app));
        ImGui::End();
        return;
    }
    ImGui::End();

    if (!player.active) {
        sf::Vector2u winSize = app->getWindow().getSize();
        ImGui::SetNextWindowPos(ImVec2(winSize.x / 2.0f, winSize.y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "GAME OVER");
        ImGui::Text("Final Score: %d", player.score);
        ImGui::Separator();
        
        if (ImGui::Button("Return to Main Menu", ImVec2(200, 40))) {
            app->changeScene(std::make_unique<MainMenuScene>(app));
            ImGui::End();
            return;
        }
        ImGui::End();
    }
}