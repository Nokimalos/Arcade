/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** AObject
*/

#ifndef AOBJECT_HPP_
	#define AOBJECT_HPP_

#include <map>
#include "IObject.hpp"
#include "Clock.hpp"

namespace graphical {
	class AObject : public IObject {
	public:
		class Error : std::exception {
		public:
			Error(std::string message) : _message(message) {}
			~Error() = default;
			const char *what() const noexcept override {return _message.c_str();}
		private:
			std::string _message;
		};

        enum Colors {
            DEFAULT,
            BLACK,
            WHITE,
            YELLOW,
            RED,
            BLUE,
            MAGENTA,
            CYAN,
            GREEN,
        };

        std::map<std::string, Colors> _colorsFactory = {
            {"black", BLACK},
            {"white", WHITE},
            {"yellow", YELLOW},
            {"red", RED},
            {"blue", BLUE},
            {"magenta", MAGENTA},
            {"cyan", CYAN},
            {"green", GREEN},
        };

		AObject(const std::string &filePath);
		~AObject() {};
		int &getSpriteState();
		int &getOff();
        const std::string &getConfig() const;
	protected:
		int _width;
		int _spriteState;
		int _off;
        Clock _clock;
		const std::string _configFile;
	};
	std::string getInfoFromConfigFile(const std::string &part, const std::string &info,
		const std::string &filePath);
}

#endif /* !AOBJECT_HPP_ */
