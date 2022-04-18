/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** mainMenu
*/

#ifndef MAINMENU_HPP_
    #define MAINMENU_HPP_

    #include "IMenu.hpp"

namespace menu {
class mainMenu : public menu::IMenu {
    public:
        mainMenu();
        void loadMenuObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib);
        std::string run(std::unique_ptr<graphical::IGraphical> &graphicalLib, game::event::Events &event);
        void setGraphicalLib(graphical::IGraphical &graphicalLib);
        void reloadGame();
        void changeGameDisk(game::event::Events event);
        void displayFixObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib);
        void displayDiskObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib);
        void getPseudo(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event);
    protected:
    private:
        int _objectIndex;
        std::vector<std::pair<std::string, std::unique_ptr<graphical::IObject>>> _diskObjects;
        std::vector<std::unique_ptr<graphical::IObject>> _fixObjects;
    };
}

#endif /* !MAINMENU_HPP_ */
