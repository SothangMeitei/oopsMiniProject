#pragma once
#include "scene.h"

class ChessScene : public Scene{
    public:
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};