/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLGraphical
*/

#ifndef SDLGRAPHICAL_HPP_
	#define SDLGRAPHICAL_HPP_

    #include "IGraphical.hpp"
    #include <SDL.h>
    #include <map>

namespace graphical {
class SDLGraphical : public graphical::IGraphical {
	public:
		class Error : std::exception {
		public:
			Error(std::string message) : _message(message) {}
			~Error() = default;
			const char *what() const noexcept override {return _message.c_str();}
		private:
			std::string _message;
		};
        SDLGraphical();
        ~SDLGraphical() final;
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
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Event _event;
        std::map <Uint32, game::event::EventType> _keyEventType
            = {
                {SDL_QUIT, game::event::Closed},
                {SDL_WINDOWEVENT, game::event::Resized},
                {SDL_KEYUP, game::event::KeyReleased},
                {SDL_KEYDOWN, game::event::KeyPressed},
                {SDL_MOUSEMOTION, game::event::MouseMoved},
                {SDL_MOUSEBUTTONDOWN, game::event::MouseButtonPressed},
                {SDL_MOUSEBUTTONUP, game::event::MouseButtonReleased},
            };
        std::map <Uint8, game::event::MouseKeyCode>
            _mouseButtonMap = {
            {SDL_BUTTON_LEFT, game::event::KeyLeft},
            {SDL_BUTTON_RIGHT, game::event::KeyRight},
            {SDL_BUTTON_MIDDLE, game::event::KeyMiddle},
            {SDL_BUTTON_X1, game::event::MouseCodeUnknown},
            {SDL_BUTTON_X2, game::event::MouseCodeUnknown},
        };
		std::map <SDL_Keycode, game::event::KeyCode> _keysMap = {
			{SDLK_a, game::event::keyA},
			{SDLK_b, game::event::keyB},
			{SDLK_c, game::event::keyC},
			{SDLK_d, game::event::keyD},
			{SDLK_e, game::event::keyE},
			{SDLK_f, game::event::keyF},
			{SDLK_g, game::event::keyG},
			{SDLK_h, game::event::keyH},
			{SDLK_i, game::event::keyI},
			{SDLK_j, game::event::keyJ},
			{SDLK_k, game::event::keyK},
			{SDLK_l, game::event::keyL},
			{SDLK_m, game::event::keyM},
			{SDLK_n, game::event::keyN},
			{SDLK_o, game::event::keyO},
			{SDLK_p, game::event::keyP},
			{SDLK_q, game::event::keyQ},
			{SDLK_r, game::event::keyR},
			{SDLK_s, game::event::keyS},
			{SDLK_t, game::event::keyT},
			{SDLK_u, game::event::keyU},
			{SDLK_v, game::event::keyV},
			{SDLK_w, game::event::keyW},
			{SDLK_x, game::event::keyX},
			{SDLK_y, game::event::keyY},
			{SDLK_z, game::event::keyZ},
			{SDLK_0, game::event::keyNum0},
			{SDLK_1, game::event::keyNum1},
			{SDLK_2, game::event::keyNum2},
			{SDLK_3, game::event::keyNum3},
			{SDLK_4, game::event::keyNum4},
			{SDLK_5, game::event::keyNum5},
			{SDLK_6, game::event::keyNum6},
			{SDLK_7, game::event::keyNum7},
			{SDLK_8, game::event::keyNum8},
			{SDLK_9, game::event::keyNum9},
			{SDLK_ESCAPE, game::event::keyEscape},
			{SDLK_LCTRL, game::event::keyLControl},
			{SDLK_LSHIFT, game::event::keyLShift},
			{SDLK_LALT, game::event::keyLAlt},
			{SDLK_RCTRL, game::event::keyRControl},
			{SDLK_RSHIFT, game::event::keyRShift},
			{SDLK_RALT, game::event::keyRAlt},
			{SDLK_MENU, game::event::keyMenu},
			{SDLK_KP_LEFTBRACE, game::event::keyLBracket},
			{SDLK_KP_RIGHTBRACE, game::event::keyRBracket},
			{SDLK_SEMICOLON, game::event::keySemiColon},
			{SDLK_COMMA, game::event::keyComma},
			{SDLK_KP_PERIOD, game::event::keyPeriod},
			{SDLK_QUOTEDBL, game::event::keyQuote},
			{SDLK_KP_DIVIDE, game::event::keySlash},
			{SDLK_BACKSLASH, game::event::keyBackSlash},
			{SDLK_BACKSPACE, game::event::keyBackSpace},
			{SDLK_KP_EQUALS, game::event::keyEqual},
			{SDLK_SPACE, game::event::keySpace},
			{SDLK_KP_TAB, game::event::keyTab},
			{SDL_SCANCODE_PAGEUP, game::event::keyPageUp},
			{SDL_SCANCODE_PAGEDOWN, game::event::keyPageDown},
			{SDL_SCANCODE_END, game::event::keyEnd},
			{SDL_SCANCODE_HOME, game::event::keyHome},
			{SDL_SCANCODE_INSERT, game::event::keyInsert},
			{SDL_SCANCODE_DELETE, game::event::keyDelete},
			{SDLK_KP_PLUS, game::event::keyAdd},
			{SDLK_KP_MINUS, game::event::keySubtract},
			{SDL_SCANCODE_KP_MULTIPLY, game::event::keyMultiply},
			{SDL_SCANCODE_KP_DIVIDE, game::event::keyDivide},
			{SDLK_LEFT, game::event::keyLeft},
			{SDLK_RIGHT, game::event::keyRight},
			{SDLK_UP, game::event::keyUp},
			{SDLK_DOWN, game::event::keyDown},
			{SDLK_0, game::event::keyNumpad0},
			{SDLK_1, game::event::keyNumpad1},
			{SDLK_2, game::event::keyNumpad2},
			{SDLK_3, game::event::keyNumpad3},
			{SDLK_4, game::event::keyNumpad4},
			{SDLK_5, game::event::keyNumpad5},
			{SDLK_6, game::event::keyNumpad6},
			{SDLK_7, game::event::keyNumpad7},
			{SDLK_8, game::event::keyNumpad8},
			{SDLK_9, game::event::keyNumpad9},
			{SDLK_F1, game::event::keyF1},
			{SDLK_F2, game::event::keyF2},
			{SDLK_F3, game::event::keyF3},
			{SDLK_F4, game::event::keyF4},
			{SDLK_F5, game::event::keyF5},
			{SDLK_F6, game::event::keyF6},
			{SDLK_F7, game::event::keyF7},
			{SDLK_F8, game::event::keyF8},
			{SDLK_F9, game::event::keyF9},
			{SDLK_F10, game::event::keyF10},
			{SDLK_F11, game::event::keyF11},
			{SDLK_F12, game::event::keyF12},
			{SDLK_F13, game::event::keyF13},
			{SDLK_F14, game::event::keyF14},
			{SDLK_F15, game::event::keyF15},
			{SDLK_PAUSE, game::event::keyPause},
            {SDLK_RETURN, game::event::keyReturn},
		};
	};
}

#endif /* !SDLGRAPHICAL_HPP_ */
