/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SpriteNcurses
*/

#ifndef SPRITENCURSES_HPP_
    #define SPRITENCURSES_HPP_

    #include "NcursesGraphical.hpp"
    #include "NcursesObject.hpp"

using namespace graphical;

namespace ncurses {
class NcursesSprite : public NcursesObject {
	public:
		NcursesSprite(const std::string &filePath);
	};
}

#endif /* !SPRITENCURSES_HPP_ */
