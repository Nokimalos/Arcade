cmake_minimum_required(VERSION 3.17)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical)
include_directories(${PROJECT_SOURCE_DIR}/include/Graphical/ncurses)

add_library(arcade_ncurses SHARED
        ${PROJECT_SOURCE_DIR}/src/Clock.cpp
        ${PROJECT_SOURCE_DIR}/src/Graphical/AObject.cpp
        ./NcursesGraphical.cpp
        ./NcursesSprite.cpp
        ./NcursesText.cpp
        ./NcursesObject.cpp
        )

target_link_libraries(arcade_ncurses PRIVATE -lncurses)
set_target_properties(arcade_ncurses PROPERTIES PREFIX "")
