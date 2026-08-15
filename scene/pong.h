#pragma once
#include "scene.h"

class PongScene: public Scene{
    private:
        sf::RectangleShape leftPaddle;
        sf::RectangleShape rightPaddle;
        sf::RectangleShape ball;

        sf::Vector2f ballVelocity;
        float paddleSpeed;

        int leftScore;
        int rightScore;
        sf::Vector2f winSize;

        void resetBall();
    public:
        PongScene(GameApp* gameApp);
        ~PongScene() override = default;

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};