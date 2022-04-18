cmake_minimum_required(VERSION 3.17)
project(arcade)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ldl -g3 -std=c++17")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(./include)
include_directories(./include/Games)
include_directories(./include/Menu)
include_directories(./include/Graphical)

add_subdirectory(./src/Graphical/ncurses)
add_subdirectory(./src/Graphical/SDL)
add_subdirectory(./src/Graphical/SFML)

add_library(arcade_pacman SHARED
        src/Clock.cpp
        src/Games/Pacman/Map.cpp
        src/Games/Pacman/Utils.cpp
        src/Games/Pacman/Pacman.cpp
        )

add_library(arcade_centipede SHARED
        src/Games/Centipede.cpp
        )

add_library(arcade_nibbler SHARED
        src/Games/Nibbler/Nibbler.cpp
        src/Games/Nibbler/NibblerGame.cpp
        )

add_library(arcade_mainMenu SHARED
        src/Graphical/AObject.cpp
        src/Menu/mainMenu.cpp
        )

add_executable(arcade
        src/Core.cpp
        src/main.cpp
        src/loadLib.cpp
        src/Clock.cpp
        )

set_target_properties(arcade_pacman PROPERTIES PREFIX "")
set_target_properties(arcade_centipede PROPERTIES PREFIX "")
set_target_properties(arcade_nibbler PROPERTIES PREFIX "")
set_target_properties(arcade_mainMenu PROPERTIES PREFIX "")