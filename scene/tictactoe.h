#pragma once
#include "scene.h"

class GameApp;

class TicTacToeScene: public Scene{
    public:
        TicTacToeScene(GameApp*);
        ~TicTacToeScene() = default;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};