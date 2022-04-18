/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SFMLObjects
*/

#include "SFMLRectangleShape.hpp"

sfml::SFMLRectangleShape::SFMLRectangleShape(const std::string &filePath) : SFMLObject(filePath)
{
    _rectangle.setScale((sf::Vector2f){1,1});
    _rectangle.setSize((sf::Vector2f){40, 40});
    _rectangle.setFillColor(_colorMap[YELLOW]);
    sf::FloatRect globalBounds = _rectangle.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
}

sf::Drawable &sfml::SFMLRectangleShape::getDrawable()
{
    return _rectangle;
}

sf::Transformable &sfml::SFMLRectangleShape::getTransformable()
{
    return _rectangle;
}

const FloatRect_t &sfml::SFMLRectangleShape::getBounds()
{
    sf::FloatRect globalBounds = _rectangle.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
    return _bounds;
}