/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Graphical
*/

#include "SFMLSprite.hpp"
#include "SFMLText.hpp"
#include "SFMLRectangleShape.hpp"
#include "SFMLGraphical.hpp"
#include <fstream>

using namespace graphical;

extern "C" LibType getInstanceType()
{
    return LibType::GRAPHICAL;
}

void SFMLGraphical::windowOpen()
{
    if (!_window.isOpen())
	    _window.create(sf::VideoMode(1920, 1080), "SFML Window KB");
}

void SFMLGraphical::windowClear()
{
	_window.clear();
}

void SFMLGraphical::windowDisplay()
{
	_window.display();
}

bool SFMLGraphical::windowIsOpen()
{
    return true;
}

std::unique_ptr<graphical::IObject> SFMLGraphical::createObject(const std::string &filePath)
{
    std::map<std::string, std::function<std::unique_ptr<graphical::IObject>(std::string)>> objects = {
            {"sprite", [](const std::string& filePath) {return std::make_unique<sfml::SFMLSprite>(filePath);}},
            {"textual", [](const std::string& filePath) {return std::make_unique<sfml::SFMLText>(filePath);}},
            {"rect", [](const std::string& filePath) {return std::make_unique<sfml::SFMLRectangleShape>(filePath);}},
    };
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line);
    file.close();
    try {
        return objects[line](filePath);
    } catch (AObject::Error &) {
        return std::make_unique<sfml::SFMLRectangleShape>(filePath);
    }
}

void SFMLGraphical::drawObject(std::unique_ptr<IObject> &object)
{
    auto &sfmlObject = dynamic_cast<sfml::SFMLObject&>(*object);
    graphical::PosVector_t positionSprite = object->getPos();
    int offset = sfmlObject.getOff();
    int spriteState = sfmlObject.getSpriteState();
    sf::Vector2i vectorPos(spriteState, 0);
    sf::Vector2i sizeVector(offset, offset);
    sf::IntRect textureSize(vectorPos, sizeVector);
    sf::Vector2f ratioPos = {(float)positionSprite.x * 40, (float)positionSprite.y * 40};

    sfmlObject.setRect(textureSize);
    sfmlObject.getTransformable().setPosition(ratioPos);
    _window.draw(sfmlObject.getDrawable());
}

void SFMLGraphical::reloadSprite(std::unique_ptr<graphical::IObject> &oldSprite)
{
	std::unique_ptr<graphical::IObject> newObject = createObject(oldSprite->getConfig());

    newObject->setPos(oldSprite->getPos());
    oldSprite.release();
    oldSprite.swap(newObject);
}

extern "C" std::unique_ptr<graphical::SFMLGraphical> getInstance()
{
	return std::make_unique<SFMLGraphical>();
}

void SFMLGraphical::windowClose()
{
	_window.close();
}

void SFMLGraphical::pollEvent(game::event::Events &event)
{
    if (!_window.pollEvent(_event)) {
        event.type = game::event::UnknownEvent;
        event.key.code = game::event::Unknown;
        event.useButton.button = game::event::MouseCodeUnknown;
        return;
    }
    event.type = _keyEventType[_event.type];
    event.size = (game::event::SizeEvent){_event.size.width, _event.size
        .height};
    if (event.type == game::event::EventType::KeyPressed)
        event.key.code = _keysMap[_event.key.code];
    if (event.type == game::event::EventType::MouseButtonPressed) {
        event.mouseMove = (game::event::MouseMoveEvent){_event.mouseMove.x, _event
            .mouseMove.y};
        event.useButton = (game::event::MouseButtonEvent){_mouseButtonMap[_event
        .mouseButton.button], _event.mouseButton.x, _event.mouseButton.y};
    }
}