/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SpriteSdl
*/

#ifndef SPRITESFML_HPP_
    #define SPRITESFML_HPP_

    #include "SFMLObject.hpp"
    #include <SFML/Graphics.hpp>

using namespace graphical;

namespace sfml {
class SFMLSprite : public SFMLObject {
	public:
		SFMLSprite(const std::string &filePath);
        void setRect(sf::IntRect textureRect) final;
        sf::Drawable &getDrawable() final;
        sf::Transformable &getTransformable() final;
        const FloatRect_t &getBounds() final;
	private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        FloatRect_t _bounds;
	};
}

#endif /* !SPRITESFML_HPP_ */
