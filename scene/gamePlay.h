#pragma once
#include "scene.h"

class GamePlayScene : public Scene{
    public:
        GamePlayScene();
        ~GamePlayScene();

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};