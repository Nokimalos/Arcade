/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** IObject
*/

#ifndef ISPRITE_HPP_
	#define ISPRITE_HPP_

    #include "GraphicalVector.hpp"
    #include <string>

namespace graphical {
	class IObject {
	public:
		virtual ~IObject() = default;
		// Setter
		virtual void setPos(const PosVector_t &newPos) = 0;
		virtual void setPos(int newX, int newY) = 0;
		virtual void movPos(int offsetX, int offsetY) = 0;
		// Getter
		virtual PosVector_t &getPos() = 0;
		virtual const FloatRect_t &getBounds() = 0;
		virtual const std::string &getConfig() const = 0;
	};
}

#endif /* !ISPRITE_HPP_ */
