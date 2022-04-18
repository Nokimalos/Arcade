/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLText
*/

#ifndef TEXTSDL_HPP_
    #define TEXTSDL_HPP_

    #include "SDLObject.hpp"
    #include <SDL_ttf.h>

using namespace graphical;

namespace sdl {
    class SDLText final : public SDLObject {
    public:
        SDLText(const std::string &filePath, SDL_Renderer *renderer);
        ~SDLText() final;
    private:
        TTF_Font *_font;
    };
}

#endif /* !TEXTSDL_HPP_ */
