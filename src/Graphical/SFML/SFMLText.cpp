/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SFMLObjects
*/

#include "SFMLText.hpp"
#include "iostream"

sfml::SFMLText::SFMLText(const std::string &filePath) : SFMLObject(filePath)
{
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile("","x", filePath).c_str()), std::atoi(getInfoFromConfigFile("", "y", filePath).c_str())};
    _font.loadFromFile(getInfoFromConfigFile("", "font", filePath));
    _text.setFont(_font);
    _color = _colorMap[_colorsFactory[getInfoFromConfigFile("", "color", filePath)]];
    _text.setFillColor(_color);
    _text.setString(getInfoFromConfigFile("", "graph-txt", filePath));
    std::string sx = getInfoFromConfigFile("", "sx", filePath);
    std::string sy = getInfoFromConfigFile("", "sy", filePath);
    try {
        _text.setScale((sf::Vector2f){std::stof(sx), std::stof(sy)});
    } catch (std::invalid_argument &) {
        _text.setScale((sf::Vector2f){1, 1});
    }
    sf::FloatRect globalBounds = _text.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
}

sf::Drawable &sfml::SFMLText::getDrawable() {
    return _text;
};

sf::Transformable &sfml::SFMLText::getTransformable()
{
    return _text;
}

const FloatRect_t &sfml::SFMLText::getBounds()
{
    sf::FloatRect globalBounds = _text.getGlobalBounds();
    _bounds = (FloatRect_t){globalBounds.left, globalBounds.top, globalBounds.width, globalBounds.height};
    return _bounds;
}