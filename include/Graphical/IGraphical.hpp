/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** IGraphical
*/

#ifndef IGRAPHICAL_HPP_
	#define IGRAPHICAL_HPP_

#include <string>
#include <memory>
#include "IObject.hpp"
#include "Event.hpp"

namespace graphical {

    enum LibType {
        UNKNOWN = -1,
        GRAPHICAL,
        GAME,
        MENU
    };

	class IGraphical {
	public:
		virtual ~IGraphical() = default;

		// Window
		virtual void windowClear() = 0;
		virtual void windowOpen() = 0;
		virtual void windowClose() = 0;
		virtual void windowDisplay() = 0;
		virtual bool windowIsOpen() = 0;

		// Sprite
		virtual std::unique_ptr<graphical::IObject> createObject(const std::string	&filePath) = 0;
		virtual void drawObject(std::unique_ptr<IObject> &sprite) = 0;
        virtual void reloadSprite(std::unique_ptr<graphical::IObject> &oldSprite) = 0;

        // Event
		virtual void pollEvent(game::event::Events &event) = 0;
	};
}

#endif /* !IGRAPHICAL_HPP_ */