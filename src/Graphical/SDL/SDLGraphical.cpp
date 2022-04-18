/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLGraphical
*/

#include "SDLGraphical.hpp"
#include "SDLText.hpp"
#include "SDLSprite.hpp"
#include "SDLRectangleShape.hpp"
#include <functional>
#include <fstream>
#include <iostream>

using namespace graphical;

SDLGraphical::SDLGraphical() : _window(nullptr)
{
    _event.type = SDL_USEREVENT;
    _event.key.keysym.sym = 0;
    _event.user.code = 0;
    _event.user.data1 = nullptr;
    _event.user.data2 = nullptr;
}

extern "C" LibType getInstanceType()
{
    return LibType::GRAPHICAL;
}

void SDLGraphical::windowOpen()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw SDLGraphical::Error("Couldn't init the SDL window");
	_window = SDL_CreateWindow("SDL Window KB", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
}

void SDLGraphical::windowClose()
{
	if (_window != nullptr)  {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        _window = nullptr;
    }
}

void SDLGraphical::windowDisplay()
{
	SDL_RenderPresent(_renderer);
}

void SDLGraphical::windowClear()
{
	SDL_RenderClear(_renderer);
}

bool SDLGraphical::windowIsOpen()
{
    return true;
}

std::unique_ptr <graphical::IObject> SDLGraphical::createObject(const
std::string &filePath)
{
	std::map<std::string, std::function<std::unique_ptr<graphical::IObject>(std::string, SDL_Renderer *)>> objects = {
        {"sprite", [](const std::string& filePath, SDL_Renderer *renderer) {return std::make_unique<sdl::SDLSprite>(filePath, renderer);}},
        {"textual", [](const std::string& filePath, SDL_Renderer *renderer) {return std::make_unique<sdl::SDLText>(filePath, renderer);}},
        {"rect", [](const std::string& filePath, SDL_Renderer *renderer) {return std::make_unique<sdl::SDLRectangleShape>(filePath, renderer);}},
    };
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line);
    file.close();
    try {
        return objects[line](filePath, _renderer);
    } catch (AObject::Error &) {
        return std::make_unique<sdl::SDLRectangleShape>(filePath, _renderer);
    }
}

void SDLGraphical::drawObject(std::unique_ptr <IObject> &object)
{
    auto &sdlObject = dynamic_cast<sdl::SDLObject&>(*object);
    PosVector_t positionObject = sdlObject.getPos();
    PosVector_t sizeObject = sdlObject.getSize();
    FloatVector_t scaleObject = sdlObject.getScale();
    int offset = sdlObject.getOff();
    int spriteState = sdlObject.getSpriteState();
    PosVector_t vectorPos = {spriteState, 0};

    SDL_Rect textureShape = {vectorPos.x, vectorPos.y, sizeObject.x, sizeObject.y};
    SDL_Rect objectShape = {positionObject.x * 40, positionObject.y * 40, static_cast<int>((float)sizeObject.x * scaleObject.x), static_cast<int>((float)sizeObject.y * scaleObject.y)};
    SDL_RenderCopy(_renderer, sdlObject.getObject(), &textureShape, &objectShape);
}

void SDLGraphical::reloadSprite(std::unique_ptr<graphical::IObject> &oldSprite)
{
	std::unique_ptr<graphical::IObject> newObject = createObject(oldSprite->getConfig());
    PosVector_t reducedPos = {oldSprite->getPos().x / 40, oldSprite->getPos().y / 40};

    newObject->setPos(oldSprite->getPos());
    oldSprite.release();
    oldSprite.swap(newObject);
}

extern "C" std::unique_ptr <graphical::SDLGraphical> getInstance()
{
	return std::make_unique<SDLGraphical>();
}

void SDLGraphical::pollEvent(game::event::Events &event)
{
    if (!SDL_PollEvent(&_event)) {
        event.type = game::event::UnknownEvent;
        event.key.code = game::event::Unknown;
        event.useButton.button = game::event::MouseCodeUnknown;
    }
    event.type = _keyEventType[_event.type];
    event.size = (game::event::SizeEvent){(unsigned int)_event.window.data1,
        (unsigned int)_event.window.data2};
    auto it1 = _keysMap.find(_event.key.keysym.sym);
    if (it1 != _keysMap.end())
        event.key.code = _keysMap[_event.key.keysym.sym];
    event.mouseMove = (game::event::MouseMoveEvent){_event.motion.x, _event.motion.y};
    auto it2 = _mouseButtonMap.find(_event.button.button);
    if (it2 != _mouseButtonMap.end())
        event.useButton = (game::event::MouseButtonEvent){_mouseButtonMap[_event
            .button.button], _event.button.x, _event.button.y};
}

SDLGraphical::~SDLGraphical()
{
    windowClose();
}
