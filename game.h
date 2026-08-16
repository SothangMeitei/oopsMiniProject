#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-sfml.h"
#include <memory>
#include <optional> // Required for SFML 3 events
#include <iostream>
#include <fstream>

#include "scene/scene.h"
#include "scene/gamePlay.h"
#include "scene/menu.h"

class GameApp {
private:
    sf::RenderWindow window;
    sf::Clock deltaClock;
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> nextScene;

public:
    const sf::RenderWindow& getWindow() const {return window;}

    GameApp() : window(sf::VideoMode({1280, 720}), "OOP Game") {
        window.setFramerateLimit(60);

        // 1. Initialize backend. Pass 'false' to prevent loading default fonts yet.
        if (!ImGui::SFML::Init(window, false)) {
            throw std::runtime_error("Failed to initialize ImGui-SFML");
        }

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Clear();

        // 2. USE THE ABSOLUTE WINDOWS PATH TO THE FONT
        // If you copied it to your project, use "C:/oopsMiniProject/HARNGTON.TTF"
        std::string fontPath = "C:/Windows/Fonts/HARNGTON.TTF"; 
        
        // 3. PROVE THE FILE EXISTS BEFORE IMGUI TOUCHES IT
        std::ifstream fontFile(fontPath);
        if (!fontFile.good()) {
            std::cerr << "\n[FATAL ERROR]: Could not find font at: " << fontPath << "\n";
            std::cerr << "Falling back to the default font so we don't crash...\n\n";
            io.Fonts->AddFontDefault();
        } else {
            fontFile.close();
            io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 24.0f); // Index 0 (Menu)
            io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 72.0f); // Index 1 (Scoreboard)
        }

        // 4. THE BUG BYPASS: Force ImGui to build the entire atlas right now.
        // This prevents the broken 'WantUpdates' partial update bug in ImGui-SFML.
        io.Fonts->Build();

        currentScene = std::make_unique<MainMenuScene>(this); 
    }

    ~GameApp() {
        ImGui::SFML::Shutdown();
    }

    void changeScene(std::unique_ptr<Scene> newScene) {
        nextScene = std::move(newScene);
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

            if(nextScene){
                currentScene = std::move(nextScene);
                nextScene = nullptr;
            }
        }
    }
};