#pragma once

class GameEngine{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        bool isRunning;
        bool isPaused;
        
    public:
        GameEngine();
        ~GameEngine();

        void run();
        void mainLoop();
        void advanceFrame();
        void draw();
};