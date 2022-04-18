/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "loadLib.hpp"
#include "IGraphical.hpp"
#include "IGame.hpp"
#include "IMenu.hpp"
#include "Clock.hpp"
#include <vector>

namespace core {
    class Core {
    public:
        Core(const std::string& loadFirstLib);
        ~Core();
        void buildGame(const char *const av[]);
        void setLeftLibrary();
        void setRightLibrary();
        void setLeftGame();
        void setRightGame();
        void launchGame(const std::string &game, game::event::Events &event);
        std::string getGameNameAtIndex(const int &index) const;
        int getGameIndexWithName(const std::string &name) const;
        void displayMenu(game::event::Events &events);
    protected:
    private:
        Clock _clock;
        std::string _gameIndex;
        int _graphicalIndex;
        std::map<std::string, std::unique_ptr<game::IGame>> _gameLib;
        std::map<std::string, std::unique_ptr<menu::mainMenu>> _menuLib;
        std::map<int, std::pair<std::string, std::unique_ptr<graphical::IGraphical>>> _graphicalLib;
    };
};

#endif /* !CORE_HPP_ */