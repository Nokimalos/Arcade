/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** AObject
*/

#include "AObject.hpp"
#include "Clock.hpp"
#include <fstream>
#include <iostream>

graphical::AObject::AObject(const std::string &filePath) : _configFile(filePath), _spriteState(0)
{
	_off = std::atoi(getInfoFromConfigFile(".graph-2d", "off", filePath).c_str());
	_width = std::atoi(getInfoFromConfigFile(".graph-2d", "width", filePath).c_str());
}

int &graphical::AObject::getSpriteState()
{
	if (_clock.getElapsedTime() < 100)
		return _spriteState;
    _clock.restart();
	_spriteState += _off;
	if (_spriteState == _width)
		_spriteState = 0;
	return _spriteState;
}

int &graphical::AObject::getOff()
{
	return _off;
}

std::string graphical::getInfoFromConfigFile(const std::string &part, const std::string &info,
	const std::string &filePath)
{
	std::ifstream file(filePath);
	std::string line;
	bool inPart = part.empty();

	while (std::getline(file, line)) {
        if (line.substr(0, part.length()) == part)
            inPart = true;
        if (line.substr(0, info.length() + 1) == info + ":" && inPart)
            return line.substr(info.length() + 1);
	}
	file.close();
	return "";
}

const std::string &graphical::AObject::getConfig() const
{
	return _configFile;
}