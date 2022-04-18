/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** mainMenu
*/

#include <fstream>
#include <iostream>
#include <functional>
#include <map>
#include "mainMenu.hpp"
#include "AObject.hpp"

using namespace graphical;

enum MenuObject {
    BG,
    ARROW_LEFT,
    ARROW_RIGHT,
};

static bool isInRect(const graphical::FloatRect_t &bounds, graphical::PosVector_t mousePos)
{
    if ((float)mousePos.x >= bounds.x && (float)mousePos.x <= bounds.x + bounds.width && (float)mousePos.y >= bounds.y &&
        (float)mousePos.y <= bounds.y + bounds.heigth) {
        return true;
    }
    return false;
}

static bool checkSelection(std::unique_ptr <graphical::IObject> &object, game::event::Events event)
{
    if (event.type != game::event::MouseButtonPressed)
        return false;
    if (event.useButton.button != game::event::KeyLeft)
        return false;
    return isInRect(object->getBounds(), (graphical::PosVector_t){event.useButton.x, event.useButton.y});
}

void menu::mainMenu::changeGameDisk(game::event::Events event)
{
    int i = 0;

    for (auto &it: _fixObjects) {
        if (i == ARROW_RIGHT)
            if (checkSelection(it, event) || event.key.code == game::event::keyRight) {
                _objectIndex = (_objectIndex < 2) ? _objectIndex + 1 : 0;
            }
        if (i == ARROW_LEFT)
            if (checkSelection(it, event) || event.key.code == game::event::keyLeft) {
                _objectIndex = (_objectIndex > 0) ? _objectIndex - 1 : 2;
            }
        ++i;
    }}

void menu::mainMenu::displayFixObjects(std::unique_ptr<graphical::IGraphical> &graphicalLib)
{
    for (auto &it: _fixObjects)
        graphicalLib->drawObject(it);
}

void menu::mainMenu::displayDiskObjects(std::unique_ptr <graphical::IGraphical> &graphicalLib)
{
    graphicalLib->drawObject(_diskObjects[_objectIndex].second);
}

void addInFile(char c, const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    std::string fileContent;

    while (std::getline(file, line)) {
        fileContent += line;
        if (line.substr(0, 10) == "graph-txt:" && line.length() < 30)
            fileContent += c;
        fileContent += "\n";
    }
    std::ofstream out_file(filePath);
    out_file << fileContent;
}

void deleteInPseudo(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    std::string fileContent;

    while (std::getline(file, line)) {
        fileContent += line;
        if (line.substr(0, 10) == "graph-txt:" && line.length() > 10)
            fileContent = fileContent.substr(0, fileContent.length() - 1);
        fileContent += "\n";
    }
    std::ofstream out_file(filePath);
    out_file << fileContent;
}

int modifyPseudo(game::event::Events &event)
{
    std::map<game::event::KeyCode, char> keyToChar = {
            {game::event::keyA, 'a'},
            {game::event::keyB, 'b'},
            {game::event::keyC, 'c'},
            {game::event::keyD, 'd'},
            {game::event::keyE, 'e'},
            {game::event::keyF, 'f'},
            {game::event::keyG, 'g'},
            {game::event::keyH, 'h'},
            {game::event::keyI, 'i'},
            {game::event::keyJ, 'j'},
            {game::event::keyK, 'k'},
            {game::event::keyL, 'l'},
            {game::event::keyM, 'm'},
            {game::event::keyN, 'n'},
            {game::event::keyO, 'o'},
            {game::event::keyP, 'p'},
            {game::event::keyQ, 'q'},
            {game::event::keyR, 'r'},
            {game::event::keyS, 's'},
            {game::event::keyT, 't'},
            {game::event::keyU, 'u'},
            {game::event::keyV, 'v'},
            {game::event::keyW, 'w'},
            {game::event::keyX, 'x'},
            {game::event::keyY, 'y'},
            {game::event::keyZ, 'z'},
    };
    switch (event.key.code) {
        case game::event::keyReturn:
            return 1;
        case game::event::keyBackSpace:
            deleteInPseudo("conf/pseudo.conf");
            deleteInPseudo("conf/txt/pseudo.txt");
            return 0;
        default:
            if (event.key.code >= game::event::keyA && event.key.code <= game::event::keyZ) {
                addInFile(keyToChar[event.key.code], "conf/pseudo.conf");
                addInFile(keyToChar[event.key.code], "conf/txt/pseudo.txt");
            }
            return 0;
    }
}

void menu::mainMenu::getPseudo(std::unique_ptr <graphical::IGraphical> &graphicalLib, game::event::Events &event)
{
   while (event.type != game::event::Closed) {
        graphicalLib->pollEvent(event);
        graphicalLib->windowClear();
        if (event.type == game::event::KeyPressed) {
            switch (modifyPseudo(event)) {
                case 0:
                    _fixObjects[2] = graphicalLib->createObject("conf/pseudo.conf");
                    break;
                case 1:
                    return;
                default:
                    break;
            }
        }
        displayFixObjects(graphicalLib);
        graphicalLib->windowDisplay();
    }
}

menu::mainMenu::mainMenu()
{
}

extern "C" std::unique_ptr<menu::mainMenu> getInstance()
{
    return std::make_unique<menu::mainMenu>();
}

extern "C" LibType getInstanceType()
{
    return LibType::MENU;
}

void menu::mainMenu::loadMenuObjects(std::unique_ptr<IGraphical> &graphicalLib)
{
    _objectIndex = 0;
    _fixObjects.emplace_back(graphicalLib->createObject("conf/main-menu-bg.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/menu/arrow-left.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/menu/arrow-right.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/textPseudo.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/change-lib-text.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/arcade_sfml.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/arcade_sdl.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/arcade_ncurses.conf"));
    _fixObjects.emplace_back(graphicalLib->createObject("conf/pseudo.conf"));
    _diskObjects.emplace_back((std::pair<std::string, std::unique_ptr<graphical::IObject>>){"conf/menu/pacman-disk.conf", graphicalLib->createObject("conf/menu/pacman-disk.conf")});
    _diskObjects.emplace_back((std::pair<std::string, std::unique_ptr<graphical::IObject>>){"conf/menu/nibbler-disk.conf", graphicalLib->createObject("conf/menu/nibbler-disk.conf")});
    _diskObjects.emplace_back((std::pair<std::string, std::unique_ptr<graphical::IObject>>){"conf/menu/centipede-disk.conf", graphicalLib->createObject("conf/menu/centipede-disk.conf")});
}

std::string menu::mainMenu::run(std::unique_ptr<IGraphical> &graphicalLib, game::event::Events &event)
{
    graphicalLib->windowClear();
    displayFixObjects(graphicalLib);
    displayDiskObjects(graphicalLib);
    changeGameDisk(event);
    if (event.type == game::event::KeyPressed) {
        switch (modifyPseudo(event)) {
            case 0:
                _fixObjects.pop_back();
                _fixObjects.emplace_back(graphicalLib->createObject("conf/pseudo.conf"));
                break;
            case 1:
                return getInfoFromConfigFile("", "libGameName", _diskObjects[_objectIndex].first);
            default:
                break;
        }
    }
    graphicalLib->windowDisplay();
    return "";
}

void menu::mainMenu::setGraphicalLib(IGraphical &graphicalLib)
{
    for (auto &diskObject : _diskObjects) {
        graphicalLib.reloadSprite(diskObject.second);
    }
    for (auto &fixObject : _fixObjects) {
        graphicalLib.reloadSprite(fixObject);
    }
}

void menu::mainMenu::reloadGame()
{
    _diskObjects.clear();
    _fixObjects.clear();
    _objectIndex = 0;
}