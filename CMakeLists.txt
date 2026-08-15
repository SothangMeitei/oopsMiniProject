cmake_minimum_required(VERSION 3.15)
project(oopsMiniProject)

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
)

# Link everything together
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    ImGui-SFML::ImGui-SFML
)