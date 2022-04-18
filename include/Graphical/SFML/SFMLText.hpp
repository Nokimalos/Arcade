/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SpriteSdl
*/

#ifndef TEXTSFML_HPP_
    #define TEXTSFML_HPP_

    #include "SFMLObject.hpp"
    #include <SFML/Graphics.hpp>

using namespace graphical;

namespace sfml {
class SFMLText : public SFMLObject {
	public:
		SFMLText(const std::string &filePath);
        void setRect(sf::IntRect textureRect) final {}
        sf::Drawable &getDrawable() final;
        sf::Transformable &getTransformable() final;
        const FloatRect_t &getBounds() final;
	private:
        sf::Color _color;
		sf::Font _font;
		sf::Text _text;
        FloatRect_t _bounds;
	};
}

#endif /* !TEXTSFML_HPP_ */
