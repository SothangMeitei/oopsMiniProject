#pragma once
#include "scene.h"
#include <vector>

class GameApp;

enum class TicTacToeState{Playing , PlayerXWon , PlayerOWon , Draw};

class TicTacToeScene: public Scene{
        std::vector<std::vector<int>> board{{0 , 0 , 0} , {0 , 0 , 0} , {0 , 0 , 0}};
        short currentPlayer;
        TicTacToeState currentGameState;

        float boardSize = 600.0f;
        float cellSize = 200.0f;
        sf::Vector2f boardOffset;

        void resetGame();
        void checkWinCondition();
        
        // Helper drawing functions
        void drawBoard(sf::RenderWindow& window);
        void drawX(sf::RenderWindow& window, float x, float y);
        void drawO(sf::RenderWindow& window, float x, float y);

    public:
        TicTacToeScene(GameApp*);
        ~TicTacToeScene() override = default;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;
        void renderUI() override;
};