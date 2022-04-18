/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** loadLib
*/

#include "loadLib.hpp"

using namespace sharedLib;

loadGraphicalLib::loadGraphicalLib(std::string sharedLibName)
{
    _handle = dlopen(std::string("./" + sharedLibName).c_str(), RTLD_LAZY | RTLD_LOCAL);

    if (!_handle)
        throw loadGraphicalLib::Error("Couldn't open graphical shared "
        "library : " + sharedLibName);
    _getInstance = (std::unique_ptr<graphical::IGraphical>(*)())
            (dlsym(_handle, "getInstance"));
}

loadGraphicalLib::~loadGraphicalLib()
{
}

std::unique_ptr<graphical::IGraphical> loadGraphicalLib::getLoadedLib() const {
    return _getInstance();
}

loadGameLib::loadGameLib(std::string sharedLibName) {
    _handle = dlopen(sharedLibName.c_str(), RTLD_LAZY | RTLD_LOCAL);
    if (!_handle)
        throw loadGameLib::Error(
        "Couldn't open game shared "
        "library : " + sharedLibName);
    _getInstance = (std::unique_ptr<game::IGame>(*)())
        (dlsym(_handle, "getInstance"));
}

std::unique_ptr<game::IGame> loadGameLib::getLoadedLib() const
{
    return _getInstance();
}

loadGameLib::~loadGameLib()
{
}

loadMenuLib::loadMenuLib(std::string sharedLibName)
{
    _handle = dlopen(std::string("./" + sharedLibName).c_str(), RTLD_LAZY | RTLD_LOCAL);

    if (!_handle)
        throw loadMenuLib::Error("Couldn't open graphical shared "
                                      "library : " + sharedLibName);
    _getInstance = (std::unique_ptr<menu::mainMenu>(*)())
            (dlsym(_handle, "getInstance"));
}

loadMenuLib::~loadMenuLib()
{
}

std::unique_ptr<menu::mainMenu> loadMenuLib::getLoadedLib() const {
    return _getInstance();
}
