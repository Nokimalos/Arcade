/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Event
*/

#ifndef EVENT_HPP_
	#define EVENT_HPP_

namespace game::event {

    enum KeyCode : int {
        Unknown = -1,
        keyA,
        keyB,
        keyC,
        keyD,
        keyE,
        keyF,
        keyG,
        keyH,
        keyI,
        keyJ,
        keyK,
        keyL,
        keyM,
        keyN,
        keyO,
        keyP,
        keyQ,
        keyR,
        keyS,
        keyT,
        keyU,
        keyV,
        keyW,
        keyX,
        keyY,
        keyZ,
        keyNum0,
        keyNum1,
        keyNum2,
        keyNum3,
        keyNum4,
        keyNum5,
        keyNum6,
        keyNum7,
        keyNum8,
        keyNum9,
        keyEscape,
        keyLControl,
        keyLShift,
        keyLAlt,
        keyRControl,
        keyRShift,
        keyRAlt,
        keyMenu,
        keyLBracket,
        keyRBracket,
        keySemiColon,
        keyComma,
        keyPeriod,
        keyQuote,
        keySlash,
        keyBackSlash,
        keyBackSpace,
        keyEqual,
        keyDash,
        keySpace,
        keyReturn,
        keyBack,
        keyTab,
        keyPageUp,
        keyPageDown,
        keyEnd,
        keyHome,
        keyInsert,
        keyDelete,
        keyAdd,
        keySubtract,
        keyMultiply,
        keyDivide,
        keyLeft,
        keyRight,
        keyUp,
        keyDown,
        keyNumpad0,
        keyNumpad1,
        keyNumpad2,
        keyNumpad3,
        keyNumpad4,
        keyNumpad5,
        keyNumpad6,
        keyNumpad7,
        keyNumpad8,
        keyNumpad9,
        keyF1,
        keyF2,
        keyF3,
        keyF4,
        keyF5,
        keyF6,
        keyF7,
        keyF8,
        keyF9,
        keyF10,
        keyF11,
        keyF12,
        keyF13,
        keyF14,
        keyF15,
        keyPause,
        keyCount,
        keyMouse
    };
    enum MouseKeyCode : int {
        MouseCodeUnknown = -1,
        KeyLeft,
        KeyRight,
        KeyMiddle,
    };
    struct SizeEvent {
        unsigned int width;
        unsigned int height;
    };
    struct KeyEvent {
        game::event::KeyCode code;
    };

    struct MouseMoveEvent {
        int x;
        int y;
    };
    struct MouseButtonEvent {
        game::event::MouseKeyCode button;
        int x;
        int y;
    };
    enum EventType : int {
        UnknownEvent = -1,
        Resized,
        Closed,
        KeyPressed,
        KeyReleased,
        MouseMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        Count
    };
    struct Events {
        EventType type = UnknownEvent;
        SizeEvent size;
        KeyEvent key = {game::event::Unknown};
        MouseMoveEvent mouseMove;
        MouseButtonEvent useButton;
    };
}

#endif /* !IGAME_HPP_ */
