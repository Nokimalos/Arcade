/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** ObjectNcurses
*/

#ifndef OBJECTNCURSES_HPP_
    #define OBJECTNCURSES_HPP_

    #include "NcursesGraphical.hpp"
    #include "AObject.hpp"

using namespace graphical;

namespace ncurses {
class NcursesObject : public AObject {
	public:
        std::map<Colors, short> _colorMap = {
                {DEFAULT, COLOR_GREEN},
                {BLACK, COLOR_BLACK},
                {WHITE, COLOR_WHITE},
                {YELLOW, COLOR_YELLOW},
                {RED, COLOR_RED},
                {BLUE, COLOR_BLUE},
                {MAGENTA, COLOR_MAGENTA},
                {CYAN, COLOR_CYAN},
                {GREEN, COLOR_GREEN},
        };
		NcursesObject(const std::string &filePath);
		const std::string &getObject();
		void movPos(int offsetX, int offsetY) final;
		void setPos(const PosVector_t &pos) final;
		void setPos(int newX, int newY) final;
        PosVector_t &getPos() final;
        const FloatRect_t &getBounds() final;
        short &getId();
protected:
        short _id;
        short _color;
        std::string _sprite;
        PosVector_t _pos;
        FloatRect_t _bounds;
	};
}

#endif /* !OBJECTNCURSES_HPP_ */
