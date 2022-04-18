/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
    #define CENTIPEDE_HPP_

    #include <vector>
    #include "IGame.hpp"

enum Directions : int {
    RIGHT,
    DOWN,
    LEFT,
    UP,
};

const int MIN_X_WINDOW = 0;
const int MAX_X_WINDOW = 47;
const int MIN_Y_WINDOW = 0;
const int MIN_Y_PLAYER = 20;
const int MAX_Y_WINDOW = 24;

namespace game {
    class Centipede : public game::IGame {
    public:
        Centipede();
        ~Centipede();
        GameState run(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event);
        void setGraphicalLib(graphical::IGraphical &graphicalLib);
        void loadGameObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib);
        void reloadGame();
        void createCentipedeMap(const std::string &mapPath);
        std::vector<std::string> &getMap();
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &getSpritePicker();
        bool caseEmpty(int offsetX, int offsetY, graphical::PosVector_t pos);
        static std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> createCentipede(std::unique_ptr<graphical::IGraphical> &graphicalLib, int length);
        bool moveCentipede(const std::function<bool(std::unique_ptr<graphical::IObject>&, Directions, bool)> &move);
        void moveFire();
        bool collideWithCentipede(std::unique_ptr<graphical::IGraphical> &graphicalLib);
    protected:
    private:
        std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> _spritePicker;
        std::vector<std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>>> _centipede;
        std::unique_ptr<graphical::IObject> _player;
        std::vector<std::unique_ptr<graphical::IObject>> _life;
        std::vector <std::string> _map;
        Directions _lastCentipedeDir;
        int _score;
    };
}

#endif /* !CENTIPEDE_HPP_ */
