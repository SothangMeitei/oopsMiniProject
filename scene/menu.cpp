#include "menu.h"
#include "gamePlay.h" // Include this to transition to it
#include "../game.h"  // Needed for app->changeScene()
#include <imgui.h>
#include "chess.h"
#include "geometry.h"
#include "pong.h"
#include "tictactoe.h"
#include <memory>

void MainMenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {}
void MainMenuScene::update(float dt) {}
void MainMenuScene::render(sf::RenderWindow& window) {}

void MainMenuScene::renderUI() {

    sf::Vector2u winSize = app->getWindow().getSize();

    ImGui::SetNextWindowPos(ImVec2(winSize.x / 2.0f, winSize.y / 2.0f)
                            ,ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::Begin("Arcade Selection"
        , nullptr
        , ImGuiWindowFlags_AlwaysAutoResize 
        | ImGuiWindowFlags_NoCollapse);
    
    ImGui::Text("Select a game to play:");
    ImGui::Separator();

    if (ImGui::Button("Pong (Real-time Physics)", ImVec2(250, 40))) {
        app->changeScene(std::make_unique<PongScene>(app));
    }
    if (ImGui::Button("Tic-Tac-Toe (Grid Logic)", ImVec2(250, 40))) {
        app->changeScene(std::make_unique<TicTacToeScene>(app));
    }
    if (ImGui::Button("Geometry Wars (Vectors)", ImVec2(250, 40))) {
        app->changeScene(std::make_unique<GeometryScene>(app));
    }
    
    ImGui::Separator();
    if (ImGui::Button("Quit to Desktop", ImVec2(250, 40))) {
        exit(0);
    }
    
    ImGui::End();
}