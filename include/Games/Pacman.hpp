/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_

    #include <vector>
    #include "IGame.hpp"
    #include "GraphicalVector.hpp"
    #include "Clock.hpp"

enum Directions : int {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

namespace game {
    class Pacman : public game::IGame {
    public:
        Pacman();
        ~Pacman();
        GameState run(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event);
        void setGraphicalLib(graphical::IGraphical &graphicalLib);
        void loadGameObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib);
        void reloadGame();
        void createPacmanMap(const std::string &mapPath);
        std::vector<std::string> &getMap();
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &getSpritePicker();
        bool canMove(const Directions &direction, const Directions &oldDirection,
            std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos);
        Directions move(const Directions &dir, std::map<Directions,
            std::tuple<int, int, game::event::KeyCode>> &playerPos);
        void displayMap(std::vector<std::string> &map, std::unique_ptr<graphical::IGraphical> &graphicalLib,
                std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &spritePicker);
        bool isObstacle(char tile);
        bool isTeleporter(char tile);
        void checkTeleporter();
        void teleportPacman(int tpLine, int tpCol);
        bool eatPoints();
        void eatBubbleGum();
        void endTimeToEat();
        void eatPhantoms();
        void createPhantomVector();
        void displayPhantoms(std::unique_ptr<graphical::IGraphical> &lib);
        std::vector<graphical::PosVector_t> getFreePositionAround(graphical::PosVector_t &phantomPos) const;
        void movePhantoms();
    protected:
    private:
        int _frame;
        int _score;
        int _numberOfPoints;
        std::map<char, int> _charMap;
        std::map<char, graphical::PosVector_t> _phantom;
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> _spritePicker;
        std::array<std::unique_ptr<graphical::IObject>, 4> _pacman;
        std::vector <std::string> _map;
        bool _timeToEat;
        Clock _clockToEat;
        Clock _clockForPhantoms;
    };
}

#endif /* !PACMAN_HPP_ */
