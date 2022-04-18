/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SDLObject
*/

#ifndef SDLOBJECT_HPP_
    #define SDLOBJECT_HPP_

    #include "AObject.hpp"
    #include <SDL.h>

using namespace graphical;

namespace sdl {
    class SDLObject : public AObject {
    public:

        std::map <Colors, SDL_Color> _colorMap = {
                {DEFAULT, (SDL_Color){0, 255, 0}},
                {BLACK,   (SDL_Color){0, 0, 0}},
                {WHITE,   (SDL_Color){255, 255, 255}},
                {YELLOW,  (SDL_Color){255, 255, 0}},
                {RED,     (SDL_Color){255, 0, 0}},
                {BLUE,    (SDL_Color){0, 0, 255}},
                {MAGENTA, (SDL_Color){255, 0, 255}},
                {CYAN,    (SDL_Color){0, 255, 255}},
                {GREEN,   (SDL_Color){0, 255, 0}},
        };

        SDLObject(const std::string &filePath);
        ~SDLObject() override;
        void movPos(int offsetX, int offsetY) final;
        void setPos(const PosVector_t &pos) final;
        void setPos(int newX, int newY) final;
        PosVector_t &getPos() final;
        const PosVector_t &getSize();
        const FloatVector_t &getScale();
        const FloatRect_t &getBounds() final;
        SDL_Texture *getObject();
    protected:
        SDL_Texture *_object;
        graphical::PosVector_t _pos;
        graphical::PosVector_t _size;
        graphical::FloatVector_t _scale;
        std::string _configFile;
        FloatRect_t _bounds;
    };
}

#endif //SDLOBJECT_HPP_