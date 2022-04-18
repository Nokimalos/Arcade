cmake_minimum_required(VERSION 3.17)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical/SDL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_library(arcade_sdl2 SHARED
        ${PROJECT_SOURCE_DIR}/src/Clock.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphical/AObject.cpp
        ./SDLGraphical.cpp
        ./SDLSprite.cpp
        ./SDLObject.cpp
        ./SDLText.cpp
        ./SDLRectangleShape.cpp
        )

target_link_libraries(arcade_sdl2 ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_ttf -lSDL2)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")
