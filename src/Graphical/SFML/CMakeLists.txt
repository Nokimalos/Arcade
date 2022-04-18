cmake_minimum_required(VERSION 3.17)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical/SFML)

add_library(arcade_sfml SHARED
        ${PROJECT_SOURCE_DIR}/src/Clock.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphical/AObject.cpp
        ./SFMLGraphical.cpp
        ./SFMLObject.cpp
        ./SFMLSprite.cpp
        ./SFMLText.cpp
        ./SFMLRectangleShape.cpp
        )

target_link_libraries(arcade_sfml PRIVATE -lsfml-window -lsfml-graphics -lsfml-system)
set_target_properties(arcade_sfml PROPERTIES PREFIX "")
