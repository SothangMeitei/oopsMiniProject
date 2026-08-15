#pragma once
#include "scene.h"

class GameApp;

class GeometryScene: public Scene{
    public:
        GeometryScene(GameApp*);
        ~GeometryScene() = default;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};