/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** SFMLObject
*/

#ifndef SFMLOBJECT_HPP_
    #define SFMLOBJECT_HPP_

    #include "AObject.hpp"
    #include "SFMLGraphical.hpp"

using namespace graphical;

namespace sfml {
    class SFMLObject : public AObject {
        public:
            std::map<Colors, sf::Color> _colorMap = {
                {DEFAULT, sf::Color::Green},
                {BLACK, sf::Color::Black},
                {WHITE, sf::Color::White},
                {YELLOW, sf::Color::Yellow},
                {RED, sf::Color::Red},
                {BLUE, sf::Color::Blue},
                {MAGENTA, sf::Color::Magenta},
                {CYAN, sf::Color::Cyan},
                {GREEN, sf::Color::Green},
            };
            SFMLObject(const std::string &filePath);
            void movPos(int offsetX, int offsetY) final;
            void setPos(const PosVector_t &pos) final;
            void setPos(int newX, int newY) final;
            PosVector_t &getPos() final;
            virtual void setRect(sf::IntRect textureRect) = 0;
            virtual sf::Drawable &getDrawable() = 0;
            virtual sf::Transformable &getTransformable() = 0;
        protected:
            graphical::PosVector_t _pos;
    };
}

#endif //SFMLOBJECT_HPP_
