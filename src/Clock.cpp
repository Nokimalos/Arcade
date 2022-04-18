/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Clock
*/

#include "Clock.hpp"

Clock::Clock()
{
    _clock = std::chrono::steady_clock::now();
}

Clock::~Clock()
{
}

int Clock::getElapsedTime()
{
    auto currentTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
	    (currentTime - _clock);
    
    return elapsed.count();
}

void Clock::restart()
{
	_clock = std::chrono::steady_clock::now();
}