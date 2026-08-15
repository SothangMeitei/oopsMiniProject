#pragma once
#include <SFML/Graphics.hpp>

// Forward declare to prevent circular inclusion dependencies
class GameApp; 

class Scene {
protected:
    // Protected so derived scenes (MainMenu, GamePlay) can access it
    GameApp* app;

public:
    // Force all scenes to take the GameApp pointer upon creation
    Scene(GameApp* gameApp) : app(gameApp) {}
    virtual ~Scene() = default;
    
    // Pure virtual interface
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void renderUI() = 0;
};