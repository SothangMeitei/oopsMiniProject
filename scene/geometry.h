#pragma once
#include "scene.h"

class GameApp;

inline float getLength(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}
inline sf::Vector2f normalize(const sf::Vector2f& v) {
    float len = getLength(v);
    return (len > 0) ? v / len : sf::Vector2f(0.f, 0.f);
}

// scene/geometry_wars.h
struct Entity {
    sf::Vector2f pos;
    sf::Vector2f vel;
    float speed;
    int color[3];
    float radius;
    float health;
    bool active = false;
};

struct Player : public Entity {
    float superMeter = 0.0f; // 0.0 to 100.0
    int score = 0;
};

struct Enemy : public Entity {

};

struct Bullet : public Entity {
    float lifeTime = 0.0f;
};

class GeometryScene: public Scene{
    private:
        Player player;

        std::vector<Enemy> enemies;
        std::vector<Bullet> bullets;

        float fireCooldown = 0.0f;
        const float FIRE_RATE = 0.1f;

        float spawnTimer = 0.0f;
        void manageSpawning(float dt);

        void spawnEnemy(sf::Vector2f position , float size);
        void fireBullet(const sf::Vector2f& targetAttackPosition);
        void superAttack();
        void resolveCollision();

        void determineNextStateOfEnemyAI();

    public:
        GeometryScene(GameApp*);
        ~GeometryScene() = default;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};