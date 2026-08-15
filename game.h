#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"
#include <memory>
#include <optional> // Required for SFML 3 events

#include "scene/scene.h"
#include "scene/gamePlay.h"
#include "scene/menu.h"

class GameApp {
private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
    std::unique_ptr<Scene> currentScene;

public:
    GameApp() : window(sf::VideoMode({1280, 720}), "OOP Game") {
        window.setFramerateLimit(60);
        
        // 1. Initialize the ImGui-SFML bridge
        (void)ImGui::SFML::Init(window);
        
        // 2. --- FIX FOR IMGUI 1.92.0+ FONT BUG ---
        // Manually push the default font into the atlas
        ImGui::GetIO().Fonts->AddFontDefault();
        
        // 3. Initialize your starting scene
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
            // SFML 3: pollEvent returns std::optional
            while (const std::optional event = window.pollEvent()) {
                
                // Dereference the optional to pass the actual event
                ImGui::SFML::ProcessEvent(window, *event);
                
                // Type-safe checking replacing the old enum
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                
                if (currentScene) {
                    currentScene->handleEvent(*event, window);
                }
            }

            sf::Time dt = deltaClock.restart();
            ImGui::SFML::Update(window, dt);

            if (currentScene) {
                currentScene->update(dt.asSeconds());
            }

            // SFML 3 uses Color::Black instead of Color::Black() or similar macros
            window.clear(sf::Color::Black);
            
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