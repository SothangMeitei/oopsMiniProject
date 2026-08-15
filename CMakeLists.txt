cmake_minimum_required(VERSION 3.15)
project(oopsMiniProject)

# Add these two lines to force C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the packages vcpkg installed (Note the capitalized components)
find_package(SFML COMPONENTS Graphics Window System REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

# Include all your source files so they compile and link together
add_executable(${PROJECT_NAME} 
    main.cpp 
    game.cpp
    scene/gamePlay.cpp
    scene/menu.cpp
    scene/scene.h
    scene/geometry.cpp
    scene/geometry.h
    scene/pong.h
    scene/pong.cpp
    scene/chess.h
    scene/chess.cpp
    scene/tictactoe.h
    scene/tictactoe.cpp
)

# Link everything together
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    ImGui-SFML::ImGui-SFML
)