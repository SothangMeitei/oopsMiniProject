#include "tictactoe.h"
#include "menu.h"
#include "../game.h"
#include <imgui.h>

TicTacToeScene::TicTacToeScene(GameApp* gameApp) : Scene(gameApp) {
    // Center the 600x600 board in the 1280x720 window
    sf::Vector2u winSize = app->getWindow().getSize();
    boardOffset.x = (winSize.x - boardSize) / 2.0f;
    boardOffset.y = (winSize.y - boardSize) / 2.0f;
    
    resetGame();
}

void TicTacToeScene::resetGame() {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            board[r][c] = 0;
        }
    }
    currentPlayer = 1; // X goes first
    currentGameState = TicTacToeState::Playing;
}

void TicTacToeScene::checkWinCondition() {
    // Check the 8 possible winning lines (3 rows, 3 columns, 2 diagonals)
    int wins[8][3][2] = {
        {{0,0}, {0,1}, {0,2}}, {{1,0}, {1,1}, {1,2}}, {{2,0}, {2,1}, {2,2}}, // Rows
        {{0,0}, {1,0}, {2,0}}, {{0,1}, {1,1}, {2,1}}, {{0,2}, {1,2}, {2,2}}, // Cols
        {{0,0}, {1,1}, {2,2}}, {{0,2}, {1,1}, {2,0}}                         // Diagonals
    };

    for (auto& line : wins) {
        int a = board[line[0][0]][line[0][1]];
        int b = board[line[1][0]][line[1][1]];
        int c = board[line[2][0]][line[2][1]];

        if (a != 0 && a == b && b == c) {
            currentGameState = (a == 1) ? TicTacToeState::PlayerXWon : TicTacToeState::PlayerOWon;
            return;
        }
    }

    // Check for a Draw (No empty cells left)
    bool emptyFound = false;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == 0) emptyFound = true;
        }
    }
    if (!emptyFound) {
        currentGameState = TicTacToeState::Draw;
    }
}

void TicTacToeScene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (currentGameState != TicTacToeState::Playing) return;

    // SFML 3.0 event handling for mouse clicks
    if (const auto* mouseClick = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left) {
            
            // 1. Get the raw screen coordinates
            float mouseX = static_cast<float>(mouseClick->position.x);
            float mouseY = static_cast<float>(mouseClick->position.y);

            // 2. Subtract the offset to see if the click was inside the grid area
            float localX = mouseX - boardOffset.x;
            float localY = mouseY - boardOffset.y;

            if (localX >= 0 && localX < boardSize && localY >= 0 && localY < boardSize) {
                // 3. Divide by cell size to get the matrix indices [0, 1, 2]
                int col = static_cast<int>(localX / cellSize);
                int row = static_cast<int>(localY / cellSize);

                // 4. If the cell is empty, place the piece and swap turns
                if (board[row][col] == 0) {
                    board[row][col] = currentPlayer;
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                    checkWinCondition();
                }
            }
        }
    }
}

void TicTacToeScene::update(float dt) {
    // Nothing to do here! The game only updates when the mouse is clicked.
}

void TicTacToeScene::render(sf::RenderWindow& window) {
    drawBoard(window);

    // Loop through the grid and draw X's and O's
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            float cellCenterX = boardOffset.x + (c * cellSize) + (cellSize / 2.0f);
            float cellCenterY = boardOffset.y + (r * cellSize) + (cellSize / 2.0f);

            if (board[r][c] == 1) drawX(window, cellCenterX, cellCenterY);
            if (board[r][c] == 2) drawO(window, cellCenterX, cellCenterY);
        }
    }
}

// --- PURE GEOMETRY DRAWING FUNCTIONS ---

void TicTacToeScene::drawBoard(sf::RenderWindow& window) {
    sf::RectangleShape line;
    line.setFillColor(sf::Color(150, 150, 150)); // Gray lines

    // Vertical lines
    line.setSize(sf::Vector2f(5.0f, boardSize));
    line.setPosition({boardOffset.x + cellSize, boardOffset.y});
    window.draw(line);
    line.setPosition({boardOffset.x + cellSize * 2, boardOffset.y});
    window.draw(line);

    // Horizontal lines
    line.setSize(sf::Vector2f(boardSize, 5.0f));
    line.setPosition({boardOffset.x, boardOffset.y + cellSize});
    window.draw(line);
    line.setPosition({boardOffset.x, boardOffset.y + cellSize * 2});
    window.draw(line);
}

void TicTacToeScene::drawX(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape line1(sf::Vector2f(150.0f, 10.0f));
    line1.setFillColor(sf::Color::Red);
    line1.setOrigin({75.0f, 5.0f}); // Center origin
    line1.setPosition({x, y});
    line1.setRotation(sf::degrees(45.0f)); // SFML 3.0 requires sf::degrees

    sf::RectangleShape line2(sf::Vector2f(150.0f, 10.0f));
    line2.setFillColor(sf::Color::Red);
    line2.setOrigin({75.0f, 5.0f});
    line2.setPosition({x, y});
    line2.setRotation(sf::degrees(-45.0f));

    window.draw(line1);
    window.draw(line2);
}

void TicTacToeScene::drawO(sf::RenderWindow& window, float x, float y) {
    sf::CircleShape circle(60.0f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(10.0f);
    circle.setOutlineColor(sf::Color::Blue);
    circle.setOrigin({60.0f, 60.0f});
    circle.setPosition({x, y});

    window.draw(circle);
}

// --- IMGUI HUD ---

void TicTacToeScene::renderUI() {
    // HUD Window
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Tic-Tac-Toe HUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    if (ImGui::Button("<- Return to Menu")) {
        app->changeScene(std::make_unique<MainMenuScene>(app));
    }
    ImGui::End();

    // Game Over Popup
    if (currentGameState != TicTacToeState::Playing) {
        sf::Vector2u winSize = app->getWindow().getSize();
        ImGui::SetNextWindowPos(ImVec2(winSize.x / 2.0f, 50.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
        ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        
        if (currentGameState == TicTacToeState::PlayerXWon) ImGui::TextColored(ImVec4(1, 0, 0, 1), "PLAYER X WINS!");
        if (currentGameState == TicTacToeState::PlayerOWon) ImGui::TextColored(ImVec4(0, 0, 1, 1), "PLAYER O WINS!");
        if (currentGameState == TicTacToeState::Draw)       ImGui::TextColored(ImVec4(1, 1, 1, 1), "IT'S A DRAW!");

        ImGui::Separator();
        if (ImGui::Button("Play Again", ImVec2(200, 40))) {
            resetGame();
        }
        ImGui::End();
    }
}