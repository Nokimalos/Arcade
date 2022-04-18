/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Graphical
*/

#ifndef NCURSESGRAPHICAL_HPP_
    #define NCURSESGRAPHICAL_HPP_

    #include <ncurses.h>
    #include <map>
    #include "IGraphical.hpp"
    #include "Clock.hpp"

namespace graphical {
	class NcursesGraphical : public IGraphical {
	public:
		NcursesGraphical() : _window(nullptr) {};
		// Window
		void windowClear() final;
		void windowOpen() final;
		void windowClose() final;
		void windowDisplay() final;
        bool windowIsOpen() final;
		// Sprite
		std::unique_ptr<graphical::IObject> createObject(const std::string &filePath) final;
		void drawObject(std::unique_ptr<IObject> &sprite) final;
        void reloadSprite(std::unique_ptr<graphical::IObject> &oldSprite) final;
		// Event
		void pollEvent(game::event::Events &event) final;
	private:
        WINDOW *_window;
        Clock _clock;
        std::map <char, game::event::KeyCode> _keysMap = {
                {'a', game::event::keyA},
                {'b', game::event::keyB},
                {'c', game::event::keyC},
                {'d', game::event::keyD},
                {'e', game::event::keyE},
                {'f', game::event::keyF},
                {'g', game::event::keyG},
                {'h', game::event::keyH},
                {'i', game::event::keyI},
                {'j', game::event::keyJ},
                {'k', game::event::keyK},
                {'l', game::event::keyL},
                {'m', game::event::keyM},
                {'n', game::event::keyN},
                {'o', game::event::keyO},
                {'p', game::event::keyP},
                {'q', game::event::keyQ},
                {'r', game::event::keyR},
                {'s', game::event::keyS},
                {'t', game::event::keyT},
                {'u', game::event::keyU},
                {'v', game::event::keyV},
                {'w', game::event::keyW},
                {'x', game::event::keyX},
                {'y', game::event::keyY},
                {'z', game::event::keyZ},
                {'0', game::event::keyNum0},
                {'1', game::event::keyNum1},
                {'2', game::event::keyNum2},
                {'3', game::event::keyNum3},
                {'4', game::event::keyNum4},
                {'5', game::event::keyNum5},
                {'6', game::event::keyNum6},
                {'7', game::event::keyNum7},
                {'8', game::event::keyNum8},
                {'9', game::event::keyNum9},
                {' ', game::event::keySpace},
                {KEY_RIGHT, game::event::keyRight},
                {KEY_LEFT, game::event::keyLeft},
                {KEY_UP, game::event::keyBackSpace},
                {KEY_DOWN, game::event::keyDown},
                {'\n', game::event::keyReturn},
        };
    };
}

#endif /* !NCURSESGRAPHICAL_HPP_ */
