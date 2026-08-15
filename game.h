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
    const sf::RenderWindow& getWindow() const {return window;}
    
    GameApp() : window(sf::VideoMode({1280, 720}), "OOP Game") {
        window.setFramerateLimit(60);

        (void)ImGui::SFML::Init(window);
        ImGui::GetIO().Fonts->AddFontDefault();
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
            while (const std::optional event = window.pollEvent()) {
                
                ImGui::SFML::ProcessEvent(window, *event);
                
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

            window.clear(sf::Color::Black);
            
            if (currentScene) {
                currentScene->render(window);
            }
            
            if (currentScene) {
                currentScene->renderUI(); 
            }
            
            ImGui::SFML::Render(window);
            window.display();
        }
    }
};