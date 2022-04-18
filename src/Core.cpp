/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Core
*/

#include <filesystem>
#include <functional>
#include "Core.hpp"

using namespace graphical;

core::Core::Core(const std::string& loadFirstLib) : _graphicalIndex(0)
{
    int posInGraphicalMap = 1;
    std::string libsPath("./lib");

    for (auto &file : std::filesystem::directory_iterator(libsPath)) {
        std::string libName = file.path().string();
        void *handle = dlopen(std::string("./" + libName).c_str(), RTLD_LAZY | RTLD_LOCAL);

        if (!handle)
            throw sharedLib::loadGraphicalLib::Error(dlerror());
        libName.erase(0, 6);
        auto getLibType = (LibType(*)())(dlsym(handle, "getInstanceType"));
        LibType libType = getLibType();
        if (libType == GRAPHICAL) {
            sharedLib::loadGraphicalLib lib("./lib/" + libName);
            if (loadFirstLib == "./lib/" + libName) {
                _graphicalLib.insert({0, (std::pair<std::string, std::unique_ptr<graphical::IGraphical>>){"./lib/" + libName, lib.getLoadedLib()}});
            } else {
                _graphicalLib.insert({posInGraphicalMap++, (std::pair<std::string, std::unique_ptr<graphical::IGraphical>>){"./lib/" + libName, lib.getLoadedLib()}});
            }
        } else if (libType == GAME) {
            sharedLib::loadGameLib lib("./lib/" + libName);
            _gameLib.insert({libName, lib.getLoadedLib()});
        } else if (libType == MENU) {
            sharedLib::loadMenuLib lib("./lib/" + libName);
            _menuLib.insert({libName, lib.getLoadedLib()});
        } else
            throw sharedLib::loadGraphicalLib::Error("Invalid library");
        dlclose(handle);
    }
}

core::Core::~Core()
{
}

std::string core::Core::getGameNameAtIndex(const int &index) const
{
    int gameNumber = 0;

    for (auto &game : _gameLib) {
        if (gameNumber == index) {
            return game.first;
        }
        gameNumber++;
    }
    throw "Index out of game lib range";
}

int core::Core::getGameIndexWithName(const std::string &name) const
{
    int gameNumber = 0;

    for (auto &game : _gameLib) {
        if (game.first == _gameIndex) {
            return gameNumber;
        }
        gameNumber++;
    }
    throw "Game " + name + " does not exist";
}

void core::Core::setLeftGame()
{
    try {
        int currentIndex = getGameIndexWithName(_gameIndex);
        int gameNumber = (currentIndex + _gameLib.size() - 1) % _gameLib.size();

        _gameIndex = getGameNameAtIndex(gameNumber);
    } catch (std::exception &) {
        std::cerr << "Error occured while switching game library" << std::endl;
    }
}

void core::Core::setRightGame()
{
    try {
        int currentIndex = getGameIndexWithName(_gameIndex);
        int gameNumber = (currentIndex + 1) % _gameLib.size();

        _gameIndex = getGameNameAtIndex(gameNumber);
    } catch (std::exception &) {
        std::cerr << "Error occured while switching game lib" << std::endl;
    }
}

void core::Core::setLeftLibrary()
{
    if (_graphicalIndex == 0)
        _graphicalIndex = _graphicalLib.size();
    _graphicalIndex = _graphicalIndex - 1;
}

void core::Core::setRightLibrary()
{
    _graphicalIndex = (_graphicalIndex + 1) % _graphicalLib.size();
}

void core::Core::displayMenu(game::event::Events &event)
{
    while (event.type != game::event::Closed) {
        _graphicalLib[_graphicalIndex].second->pollEvent(event);
        if (event.type == game::event::KeyPressed) {
            if (event.key.code == game::event::keyDown) {
                event.type = game::event::Closed;
                continue;
            }
            if (event.key.code == game::event::keyL) {
                _graphicalLib[_graphicalIndex].second->windowClose();
                setLeftLibrary();
                _graphicalLib[_graphicalIndex].second->windowOpen();
                _menuLib["arcade_mainMenu.so"]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
            }
            if (event.key.code == game::event::keyM) {
                _graphicalLib[_graphicalIndex].second->windowClose();
                setRightLibrary();
                _graphicalLib[_graphicalIndex].second->windowOpen();
                _menuLib["arcade_mainMenu.so"]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
            }
        }
        _gameIndex = _menuLib["arcade_mainMenu.so"]->run(_graphicalLib[_graphicalIndex].second, event);
        if (!_gameIndex.empty())
            break;
    }
}

void core::Core::launchGame(const std::string &game, game::event::Events &event)
{
    while (event.type != game::event::Closed) {
        if (_clock.getElapsedTime() < 40) {
            continue;
        }
        _graphicalLib[_graphicalIndex].second->pollEvent(event);
        if (event.type == game::event::KeyPressed) {
            if (event.key.code == game::event::keyDown) {
                event.type = game::event::Closed;
                continue;
            }
            if (event.key.code == game::event::keyO) {
                _gameLib[_gameIndex]->reloadGame();
                setLeftGame();
                _gameLib[_gameIndex]->loadGameObjects(_graphicalLib[_graphicalIndex].second);
                launchGame(_gameIndex, event);
                _gameLib[_gameIndex]->reloadGame();
                continue;
            }
            if (event.key.code == game::event::keyP) {
                _gameLib[_gameIndex]->reloadGame();
                setRightGame();
                _gameLib[_gameIndex]->loadGameObjects(_graphicalLib[_graphicalIndex].second);
                launchGame(_gameIndex, event);
                _gameLib[_gameIndex]->reloadGame();
                continue;
            }
            if (event.key.code == game::event::keyL) {
                _graphicalLib[_graphicalIndex].second->windowClose();
                setLeftLibrary();
                _graphicalLib[_graphicalIndex].second->windowOpen();
                _gameLib[_gameIndex]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
                _menuLib["arcade_mainMenu.so"]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
            }
            if (event.key.code == game::event::keyM) {
                _graphicalLib[_graphicalIndex].second->windowClose();
                setRightLibrary();
                _graphicalLib[_graphicalIndex].second->windowOpen();
                _gameLib[_gameIndex]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
                _menuLib["arcade_mainMenu.so"]->setGraphicalLib(*_graphicalLib[_graphicalIndex].second);
            }
            if (event.key.code == game::event::keyH) {
                displayMenu(event);
                if (event.type == game::event::Closed)
                    return;
                _gameLib[_gameIndex]->loadGameObjects(_graphicalLib[_graphicalIndex].second);
                continue;
            }
            if (event.key.code == game::event::keyR) {
                _gameLib[_gameIndex]->reloadGame();
                _gameLib[_gameIndex]->loadGameObjects(_graphicalLib[_graphicalIndex].second);
            }
        }
        if (_gameLib[_gameIndex]->run(_graphicalLib[_graphicalIndex].second, event) == game::Lose)
            return;
        _clock.restart();
    }
    _graphicalLib[_graphicalIndex].second->windowClose();
}

void core::Core::buildGame(const char *const av[])
{
    sharedLib::loadGraphicalLib lib((std::string)av[1]);
    game::event::Events event;

    _graphicalLib[_graphicalIndex].second->windowOpen();
    event.type = game::event::UnknownEvent;
    _menuLib["arcade_mainMenu.so"]->loadMenuObjects(_graphicalLib[_graphicalIndex].second);
    displayMenu(event);
    if (event.type == game::event::Closed)
        return;
    _gameLib[_gameIndex]->loadGameObjects(_graphicalLib[_graphicalIndex].second);

    launchGame(_gameIndex, event);
}