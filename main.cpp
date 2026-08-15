#include <iostream>
#include <memory>
#include "game.h" // Include your GameApp class

int main() {
    try {
        GameApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << '\n';
        return -1;
    }
    return 0;
}