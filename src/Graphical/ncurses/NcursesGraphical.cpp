/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** NcursesGraphical
*/

#include "NcursesSprite.hpp"
#include "NcursesText.hpp"
#include "NcursesGraphical.hpp"
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>

using namespace graphical;

extern "C" LibType getInstanceType()
{
    return LibType::GRAPHICAL;
}

void NcursesGraphical::windowOpen()
{
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();
}

void NcursesGraphical::windowClear()
{
    clear();
}

bool NcursesGraphical::windowIsOpen()
{
    return true;
}

void NcursesGraphical::windowDisplay()
{
    refresh();
}

std::unique_ptr<graphical::IObject> NcursesGraphical::createObject(const std::string &filePath)
{
    std::map<std::string, std::function<std::unique_ptr<graphical::IObject>(std::string)>> objects = {
            {"sprite", [](const std::string& filePath) {return std::make_unique<ncurses::NcursesSprite>(filePath);}},
            {"textual", [](const std::string& filePath) {return std::make_unique<ncurses::NcursesText>(filePath);}},
    };
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line);
    file.close();
    return objects[line](filePath);
}

std::vector<std::string> mySplit(std::string str, const std::string &delimiter)
{
    std::vector<std::string> internal;
    std::size_t pos = 0;
    std::string token;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        internal.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    internal.push_back(str);
    return internal;
}

void NcursesGraphical::drawObject(std::unique_ptr<IObject> &object)
{
    auto &sprite = dynamic_cast<ncurses::NcursesObject &>(*object);
    PosVector_t posVec = sprite.getPos();
    std::string spritePath = sprite.getObject();
    std::vector<std::string> spritePathVector = mySplit(spritePath, ",");

    short spriteId = sprite.getId();
    int offset = sprite.getOff();
    int spriteState = sprite.getSpriteState();

    attron(COLOR_PAIR(spriteId));
    if (offset > 0) {
        mvprintw(posVec.y, posVec.x, "%s", spritePathVector[(spriteState / offset) % spritePathVector.size()].c_str());
    } else {
        mvprintw(posVec.y, posVec.x, "%s", std::string(spritePathVector[0]).c_str());
    }
    attroff(COLOR_PAIR(spriteId));
}

void NcursesGraphical::reloadSprite(std::unique_ptr<graphical::IObject> &oldSprite)
{
    std::unique_ptr<graphical::IObject> newObject = createObject(oldSprite->getConfig());

    newObject->setPos(oldSprite->getPos());
    oldSprite.release();
    oldSprite.swap(newObject);
}

extern "C" std::unique_ptr<graphical::NcursesGraphical> getInstance()
{
	return std::make_unique<NcursesGraphical>();
}

void NcursesGraphical::windowClose()
{
    endwin();
}

void NcursesGraphical::pollEvent(game::event::Events &event)
{
    char key = wgetch(stdscr);

    event.key.code = _keysMap[key];
    if (key == ERR) {
        event.key.code = game::event::Unknown;
    }
    // event.key.code = _keysMap[getch()];
    if (event.key.code == game::event::keyE)
        event.type = game::event::Closed;
    else
        event.type = game::event::KeyPressed;
}
