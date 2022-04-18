/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** GraphicalVector
*/

#ifndef GRAPHICALVECTOR_HPP_
	#define GRAPHICALVECTOR_HPP_

namespace graphical {
	struct PosVector_t {
		int x;
		int y;

        PosVector_t operator+(const PosVector_t &pos)
        {
            return {x + pos.x, y + pos.y};
        }
        bool operator==(const PosVector_t &pos) const
        {
            return (x == pos.x && y == pos.y);
        }

    };
    struct FloatVector_t {
        float x;
        float y;
    };
    struct FloatRect_t {
        float x;
        float y;
        float width;
        float heigth;
    };
}

#endif /* GRAPHICALVECTOR_HPP_ */
