/*
    container class for the scenes
*/

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"
#include <memory>
#include "scene/gamePlay.h"
#include "scene/menu.h"
#include "scene/scene.h"

class GameApp {
private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
    std::unique_ptr<Scene> currentScene;

public:
    GameApp() : window(sf::VideoMode(1280, 720), "OOP Game") {
        ImGui::SFML::Init(window);
        // Initialize your starting scene
        currentScene = std::make_unique<MainMenuScene>(this); 
    }

    ~GameApp() {
        ImGui::SFML::Shutdown();
    }

    void changeScene(std::unique_ptr<Scene> newScene) {
        currentScene = std::move(newScene);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed)
                    window.close();
                
                if (currentScene)
                    currentScene->handleEvent(event, window);
            }

            sf::Time dt = deltaClock.restart();
            ImGui::SFML::Update(window, dt);

            if (currentScene) {
                currentScene->update(dt.asSeconds());
            }

            window.clear();
            
            // 1. Render SFML game objects
            if (currentScene) {
                currentScene->render(window);
            }
            
            // 2. Render ImGui UI on top
            if (currentScene) {
                currentScene->renderUI(); 
            }
            ImGui::SFML::Render(window);

            window.display();
        }
    }
};