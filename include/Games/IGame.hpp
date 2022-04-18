/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

#include "IGraphical.hpp"

namespace game {
    enum GameState : int {
        Lose = -1,
        Running,
        Win,
    };
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual void loadGameObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib) = 0;
            virtual GameState run(std::unique_ptr<graphical::IGraphical> &graphicalLib, game::event::Events &event) = 0;
            virtual void setGraphicalLib(graphical::IGraphical &graphicalLib) = 0;
            virtual void reloadGame() = 0;
    };
}

#endif /* !IGAME_HPP_ */
