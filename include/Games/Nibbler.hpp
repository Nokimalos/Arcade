/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_

    #include <vector>
    #include "IGame.hpp"

enum Directions : int {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

namespace game {
    class Nibbler : public game::IGame {
    public:
        Nibbler();
        ~Nibbler();
        GameState run(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event);
        void setGraphicalLib(graphical::IGraphical &graphicalLib);
        void loadGameObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib);
        void reloadGame();
        void createNibblerMap(const std::string &mapPath);
        std::array<std::unique_ptr<graphical::IObject>, 4> &getNibbler();
        std::vector<std::string> &getMap();
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &getSpritePicker();
        void displayBody(std::unique_ptr<graphical::IGraphical> &lib);
        void displayMap(std::unique_ptr<graphical::IGraphical> &graphicalLib);
        void moveBody();
        bool canMove(const Directions &direction, const Directions &oldDirection,
            std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos);
        std::vector<std::pair<int, graphical::PosVector_t>> &getBody();
        Directions move(const Directions &direction,
            std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos);
        void addFood(int &frameCounter);
        void eatFood();
        void die();
    protected:
    private:
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> _spritePicker;
        std::array<std::unique_ptr<graphical::IObject>, 4> _nibbler;
        std::vector<std::string> _map;
        std::vector<std::pair<int, graphical::PosVector_t>> _body;
        std::map<char, int> _charMap;
        int _score;
        Directions _toDraw;
    };
}

#endif /* !NIBBLER_HPP_ */
