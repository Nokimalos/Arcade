/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SpriteSdl
*/

#ifndef SFMLRECTANGLESHAPE_HPP_
    #define SFMLRECTANGLESHAPE_HPP_

    #include "SFMLObject.hpp"
    #include <SFML/Graphics.hpp>

using namespace graphical;

namespace sfml {
class SFMLRectangleShape : public SFMLObject {
    public:
        SFMLRectangleShape(const std::string &filePath);
        void setRect(sf::IntRect textureRect) final {}
        const FloatRect_t &getBounds() final;
        sf::Drawable &getDrawable() final;
        sf::Transformable &getTransformable() final;

    private:
        sf::RectangleShape _rectangle;
        FloatRect_t _bounds;
    };
}

#endif /* !SFMLRECTANGLESHAPE_HPP_ */
