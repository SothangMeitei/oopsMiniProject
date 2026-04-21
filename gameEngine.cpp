#include "gameEngine.h"
#include <SDL3/SDL.h>
#include <iostream>

GameEngine::GameEngine() {
    std::cout << "GameEngine initialized" << std::endl;
}

GameEngine::~GameEngine() {
    std::cout << "GameEngine destroyed" << std::endl;
}

void GameEngine::run() {
    // Initialize SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL3 initialization failed!" << std::endl;
        return;
    }

    // Create window
    window = SDL_CreateWindow("Game Engine", 800, 600, 0);
    if (!window) {
        std::cerr << "Window creation failed!" << std::endl;
        SDL_Quit();
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Renderer creation failed!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    std::cout << "Game Engine running..." << std::endl;

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        draw();
        mainLoop();
        advanceFrame();
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game Engine stopped" << std::endl;
}

void GameEngine::mainLoop() {
    while(isRunning){
        //this is the main game loop
        if(isPaused){
            continue;
        }
    }
}

void GameEngine::advanceFrame() {
    // Frame advancement logic
}

void GameEngine::draw() {
    // Drawing logic here
}
