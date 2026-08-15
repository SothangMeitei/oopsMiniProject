#include "pong.h"
#include "../game.h"

PongScene::PongScene(GameApp* gameApp) 
    : Scene(gameApp)
    , leftScore(0)
    , rightScore(0){
    //define the initial state of the game
    winSize = sf::Vector2f(app->getWindow().getSize());
    paddleSpeed = 450.0f;

    //left paddel
    sf::Vector2f paddleSize(20.0f, 120.0f);
    leftPaddle.setSize(paddleSize);
    leftPaddle.setOrigin(sf::Vector2f(paddleSize.x / 2.0f, paddleSize.y / 2.0f));
    leftPaddle.setPosition(sf::Vector2f(50.0f, winSize.y / 2.0f));
    leftPaddle.setFillColor(sf::Color::White);
    //rigth paddle
    rightPaddle.setSize(paddleSize);
    rightPaddle.setOrigin(sf::Vector2f(paddleSize.x / 2.0f, paddleSize.y / 2.0f));
    rightPaddle.setPosition(sf::Vector2f(winSize.x - 50.0f, winSize.y / 2.0f));
    rightPaddle.setFillColor(sf::Color::White);
    // Initialize Ball
    ball.setSize(sf::Vector2f(15.0f, 15.0f));
    ball.setOrigin(sf::Vector2f(7.5f, 7.5f));
    ball.setFillColor(sf::Color::White);
    
    resetBall();
    
}

void PongScene::resetBall(){
    ball.setPosition(sf::Vector2f(winSize.x / 2.0f, winSize.y / 2.0f));
    ballVelocity = sf::Vector2f(400.0f , 300.0f);
}

void PongScene::handleEvent(const sf::Event& event, sf::RenderWindow& window){
    //there will be the occurance of 8 types of user input 
    //wasd and then the up down right left


    //and the events will be of the lost of the game
    //the ball going outside that is the left or the right line of the window
    //which will trigger envent of ball reset and score setting
}
void PongScene::update(float dt) {
    if(sf::Keyboard::isKeyPressed(
        sf::Keyboard::Scancode::W) 
        && leftPaddle.getPosition().y - leftPaddle.getSize().y / 2.0f > 0)
    {
        leftPaddle.move(sf::Vector2f(0.f , -paddleSpeed * dt));
    }
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Scancode::S) 
        && leftPaddle.getPosition().y + leftPaddle.getSize().y / 2.0f < winSize.y) 
    {
        leftPaddle.move(sf::Vector2f(0.f, paddleSpeed * dt));
    }
    
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Scancode::Up) 
        && rightPaddle.getPosition().y - rightPaddle.getSize().y / 2.0f > 0) 
    {
        rightPaddle.move(sf::Vector2f(0.f, -paddleSpeed * dt));
    }
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Scancode::Down) 
        && rightPaddle.getPosition().y + rightPaddle.getSize().y / 2.0f < winSize.y) 
    {
        rightPaddle.move(sf::Vector2f(0.f, paddleSpeed * dt));
    }


    ball.move(ballVelocity * dt);

    //wall collision top and the bottom
    sf::Vector2f ballPos = ball.getPosition();
    if (ballPos.y - ball.getSize().y / 2.0f <= 0.0f){
        ballVelocity.y = std::abs(ballVelocity.y);
    }
    else if (ballPos.y + ball.getSize().y / 2.0f >= winSize.y) {
        ballVelocity.y = -std::abs(ballVelocity.y);
    }

    //paddle collision (AABB) axis align bounding box
    if(ball.getGlobalBounds().findIntersection(leftPaddle.getGlobalBounds())){
        ballVelocity.x = std::abs(ballVelocity.x) * 1.05f;
    }
    else if(ball.getGlobalBounds().findIntersection(rightPaddle.getGlobalBounds())){
        ballVelocity.x =  - std::abs(ballVelocity.x) * 1.05f;
    }

    if (ballPos.x < 0.0f) {
        rightScore++;
        resetBall();
    } else if (ballPos.x > winSize.x) {
        leftScore++;
        resetBall();
    }
}
void PongScene::render(sf::RenderWindow& window) {
    window.draw(leftPaddle);
    window.draw(rightPaddle);
    window.draw(ball);
}
void PongScene::renderUI() {
    // Navigation HUD in the top left
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Game HUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    if (ImGui::Button("<- Return to Menu")) {
        app->changeScene(std::make_unique<MainMenuScene>(app));
    }
    ImGui::End();
    
    // Scoreboard in the top middle
    ImGui::SetNextWindowPos(ImVec2(winSize.x / 2.0f, 20.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
    ImGui::Begin("Scoreboard", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    ImGui::SetWindowFontScale(3.0f); // Scale up the default font size
    ImGui::Text("%d  -  %d", leftScore, rightScore);
    ImGui::SetWindowFontScale(1.0f); // Reset scale for other windows
    ImGui::End();
}