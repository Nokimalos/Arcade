/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
    #define IMENU_HPP_

    #include <vector>
    #include "IGame.hpp"

namespace menu {
    class IMenu {
    public:
        virtual ~IMenu() = default;
        virtual void loadMenuObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib) = 0;
        virtual std::string run(std::unique_ptr<graphical::IGraphical> &graphicalLib, game::event::Events &event) = 0;
        virtual void setGraphicalLib(graphical::IGraphical &graphicalLib) = 0;
        virtual void reloadGame() = 0;
        virtual void changeGameDisk(game::event::Events event) = 0;
        virtual void displayFixObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib) = 0;
        virtual void displayDiskObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib) = 0;
        virtual void getPseudo(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event) = 0;
    };
}

#endif /* !IMENU_HPP_ */
