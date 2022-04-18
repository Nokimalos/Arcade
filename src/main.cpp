/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** main
*/

#include "Core.hpp"

static const std::string USAGE = "Usage:\n./arcade [lib]\nExample:\n./arcade ./lib/arcade_ncurses.so";

int main(const int ac, const char * const * const av)
{
	if (ac != 2) {
        std::cout << USAGE << std::endl;
		return 84;
    }
	try {
        std::srand(std::time(0));
        core::Core game(av[1]);
		game.buildGame(av);
	} catch (sharedLib::loadGraphicalLib::Error &err) {
		std::cerr << err.what() << std::endl;
		return 84;
	}
	return 0;
}
