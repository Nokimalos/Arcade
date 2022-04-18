/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SFMLObjects
*/

#include "SFMLSprite.hpp"

sfml::SFMLSprite::SFMLSprite(const std::string &filePath) : SFMLObject(filePath) {
    std::string spritePath = getInfoFromConfigFile(".graph-2d", "path", filePath);

    if (!_texture.loadFromFile(spritePath))
        throw AObject::Error("Cannot load texture from given path");
    _sprite.setTexture(_texture);
    std::string sx = getInfoFromConfigFile(".graph-2d", "sx", filePath);
    std::string sy = getInfoFromConfigFile(".graph-2d", "sy", filePath);
    try {
        _sprite.setScale((sf::Vector2f){std::stof(sx), std::stof(sy)});
    } catch (std::invalid_argument &) {
        _sprite.setScale((sf::Vector2f){1, 1});
    }
    sf::FloatRect globalBounds = _sprite.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
}

void sfml::SFMLSprite::setRect(sf::IntRect textureRect)
{
    if (textureRect.width == 0 || textureRect.height == 0)
        return;
    _sprite.setTextureRect(textureRect);
}

sf::Drawable &sfml::SFMLSprite::getDrawable() {
    return _sprite;
};

sf::Transformable &sfml::SFMLSprite::getTransformable()
{
    return _sprite;
}

const FloatRect_t &sfml::SFMLSprite::getBounds()
{
    sf::FloatRect globalBounds = _sprite.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
    return _bounds;
}