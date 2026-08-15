#pragma once
#include "scene.h"

class MainMenuScene : public Scene {
public:
    // Accept the GameApp pointer and pass it to the base Scene constructor
    MainMenuScene(GameApp* gameApp) : Scene(gameApp) {
        // You can do specific Main Menu initialization here
    }

    // Override declarations
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void renderUI() override;
};