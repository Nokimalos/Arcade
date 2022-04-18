/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** TextNcurses
*/

#ifndef TEXTNCURSES_HPP_
    #define TEXTNCURSES_HPP_

    #include "NcursesGraphical.hpp"
    #include "NcursesObject.hpp"

using namespace graphical;

namespace ncurses {
    class NcursesText : public NcursesObject {
    public:
        NcursesText(const std::string &filePath);
    };
}

#endif /* !TEXTNCURSES_HPP_ */