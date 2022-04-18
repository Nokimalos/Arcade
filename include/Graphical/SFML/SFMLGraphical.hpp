/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Graphical
*/

#ifndef SFMLGRAPHICAL_HPP_
    #define SFMLGRAPHICAL_HPP_

    #include <SFML/Graphics.hpp>
    #include "IGraphical.hpp"

namespace graphical {
	class SFMLGraphical : public IGraphical {
	public:
		SFMLGraphical() = default;
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
		sf::RenderWindow _window;
		sf::Event _event{};
        std::map <sf::Event::EventType, game::event::EventType> _keyEventType = {
            {sf::Event::Closed, game::event::Closed},
            {sf::Event::Resized, game::event::Resized},
            {sf::Event::KeyPressed, game::event::KeyPressed},
            {sf::Event::KeyReleased, game::event::KeyReleased},
            {sf::Event::MouseMoved, game::event::MouseMoved},
            {sf::Event::MouseButtonPressed, game::event::MouseButtonPressed},
            {sf::Event::MouseButtonReleased, game::event::MouseButtonReleased},
            {sf::Event::Count, game::event::Count},
        };
        std::map <sf::Mouse::Button, game::event::MouseKeyCode>
            _mouseButtonMap = {
            {sf::Mouse::Left, game::event::KeyLeft},
            {sf::Mouse::Right, game::event::KeyRight},
            {sf::Mouse::Middle, game::event::KeyMiddle},
            {sf::Mouse::XButton1, game::event::MouseCodeUnknown},
            {sf::Mouse::XButton2, game::event::MouseCodeUnknown},
            {sf::Mouse::ButtonCount, game::event::MouseCodeUnknown},
        };

		std::map <sf::Keyboard::Key, game::event::KeyCode> _keysMap = {
			{sf::Keyboard::A, game::event::keyA},
			{sf::Keyboard::B, game::event::keyB},
			{sf::Keyboard::C, game::event::keyC},
			{sf::Keyboard::D, game::event::keyD},
			{sf::Keyboard::E, game::event::keyE},
			{sf::Keyboard::F, game::event::keyF},
			{sf::Keyboard::G, game::event::keyG},
			{sf::Keyboard::H, game::event::keyH},
			{sf::Keyboard::I, game::event::keyI},
			{sf::Keyboard::J, game::event::keyJ},
			{sf::Keyboard::K, game::event::keyK},
			{sf::Keyboard::L, game::event::keyL},
			{sf::Keyboard::M, game::event::keyM},
			{sf::Keyboard::N, game::event::keyN},
			{sf::Keyboard::O, game::event::keyO},
			{sf::Keyboard::P, game::event::keyP},
			{sf::Keyboard::Q, game::event::keyQ},
			{sf::Keyboard::R, game::event::keyR},
			{sf::Keyboard::S, game::event::keyS},
			{sf::Keyboard::T, game::event::keyT},
			{sf::Keyboard::U, game::event::keyU},
			{sf::Keyboard::V, game::event::keyV},
			{sf::Keyboard::W, game::event::keyW},
			{sf::Keyboard::X, game::event::keyX},
			{sf::Keyboard::Y, game::event::keyY},
			{sf::Keyboard::Z, game::event::keyZ},
			{sf::Keyboard::Num0, game::event::keyNum0},
			{sf::Keyboard::Num1, game::event::keyNum1},
			{sf::Keyboard::Num2, game::event::keyNum2},
			{sf::Keyboard::Num3, game::event::keyNum3},
			{sf::Keyboard::Num4, game::event::keyNum4},
			{sf::Keyboard::Num5, game::event::keyNum5},
			{sf::Keyboard::Num6, game::event::keyNum6},
			{sf::Keyboard::Num7, game::event::keyNum7},
			{sf::Keyboard::Num8, game::event::keyNum8},
			{sf::Keyboard::Num9, game::event::keyNum9},
			{sf::Keyboard::Escape, game::event::keyEscape},
			{sf::Keyboard::LControl, game::event::keyLControl},
			{sf::Keyboard::LShift, game::event::keyLShift},
			{sf::Keyboard::LAlt, game::event::keyLAlt},
			{sf::Keyboard::RControl, game::event::keyRControl},
			{sf::Keyboard::RShift, game::event::keyRShift},
			{sf::Keyboard::RAlt, game::event::keyRAlt},
			{sf::Keyboard::Menu, game::event::keyMenu},
			{sf::Keyboard::LBracket, game::event::keyLBracket},
			{sf::Keyboard::RBracket, game::event::keyRBracket},
			{sf::Keyboard::Semicolon, game::event::keySemiColon},
			{sf::Keyboard::Comma, game::event::keyComma},
			{sf::Keyboard::Period, game::event::keyPeriod},
			{sf::Keyboard::Quote, game::event::keyQuote},
			{sf::Keyboard::Slash, game::event::keySlash},
			{sf::Keyboard::Backslash, game::event::keyBackSlash},
			{sf::Keyboard::Backspace, game::event::keyBackSpace},
			{sf::Keyboard::Equal, game::event::keyEqual},
			{sf::Keyboard::Space, game::event::keySpace},
			{sf::Keyboard::Tab, game::event::keyTab},
			{sf::Keyboard::PageUp, game::event::keyPageUp},
			{sf::Keyboard::PageDown, game::event::keyPageDown},
			{sf::Keyboard::End, game::event::keyEnd},
			{sf::Keyboard::Home, game::event::keyHome},
			{sf::Keyboard::Insert, game::event::keyInsert},
			{sf::Keyboard::Delete, game::event::keyDelete},
			{sf::Keyboard::Add, game::event::keyAdd},
			{sf::Keyboard::Subtract, game::event::keySubtract},
			{sf::Keyboard::Multiply, game::event::keyMultiply},
			{sf::Keyboard::Divide, game::event::keyDivide},
			{sf::Keyboard::Left, game::event::keyLeft},
			{sf::Keyboard::Right, game::event::keyRight},
			{sf::Keyboard::Up, game::event::keyUp},
			{sf::Keyboard::Down, game::event::keyDown},
			{sf::Keyboard::Numpad0, game::event::keyNumpad0},
			{sf::Keyboard::Numpad1, game::event::keyNumpad1},
			{sf::Keyboard::Numpad2, game::event::keyNumpad2},
			{sf::Keyboard::Numpad3, game::event::keyNumpad3},
			{sf::Keyboard::Numpad4, game::event::keyNumpad4},
			{sf::Keyboard::Numpad5, game::event::keyNumpad5},
			{sf::Keyboard::Numpad6, game::event::keyNumpad6},
			{sf::Keyboard::Numpad7, game::event::keyNumpad7},
			{sf::Keyboard::Numpad8, game::event::keyNumpad8},
			{sf::Keyboard::Numpad9, game::event::keyNumpad9},
			{sf::Keyboard::F1, game::event::keyF1},
			{sf::Keyboard::F2, game::event::keyF2},
			{sf::Keyboard::F3, game::event::keyF3},
			{sf::Keyboard::F4, game::event::keyF4},
			{sf::Keyboard::F5, game::event::keyF5},
			{sf::Keyboard::F6, game::event::keyF6},
			{sf::Keyboard::F7, game::event::keyF7},
			{sf::Keyboard::F8, game::event::keyF8},
			{sf::Keyboard::F9, game::event::keyF9},
			{sf::Keyboard::F10, game::event::keyF10},
			{sf::Keyboard::F11, game::event::keyF11},
			{sf::Keyboard::F12, game::event::keyF12},
			{sf::Keyboard::F13, game::event::keyF13},
			{sf::Keyboard::F14, game::event::keyF14},
			{sf::Keyboard::F15, game::event::keyF15},
			{sf::Keyboard::Pause, game::event::keyPause},
			{sf::Keyboard::KeyCount, game::event::keyCount},
			{sf::Keyboard::Return, game::event::keyReturn},
		};
	};
}

#endif /* !SFMLGRAPHICAL_HPP_ */
