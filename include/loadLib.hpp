/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** loadLib
*/

#ifndef __LOADLIB_HPP__
	#define __LOADLIB_HPP__

#include <iostream>
#include <dlfcn.h>
#include <map>
#include "IGame.hpp"
#include "IGraphical.hpp"
#include "mainMenu.hpp"

namespace sharedLib {
	class loadGraphicalLib {
	public:
		loadGraphicalLib(std::string sharedLibName);
		std::unique_ptr<graphical::IGraphical> getLoadedLib() const;
		~loadGraphicalLib();

		class Error : std::exception {
		public:
			Error(std::string message) : _message(message) {}
			~Error() = default;
			const char *what() const noexcept override {return _message.c_str();}
		private:
			std::string _message;
		};

	private:
		void *_handle;
		std::unique_ptr<graphical::IGraphical> (*_getInstance)();
	};
	class loadGameLib {
            public:
            loadGameLib(std::string sharedLibName);
            std::unique_ptr<game::IGame> getLoadedLib() const;
            ~loadGameLib();

            class Error : std::exception {
                public:
                Error(std::string message) : _message(message) {}
                ~Error() = default;
                const char *what() const noexcept override {return _message.c_str();}
                private:
                std::string _message;
            };

            private:
            void *_handle;
            std::unique_ptr<game::IGame> (*_getInstance)();
    };
    class loadMenuLib {
    public:
        loadMenuLib(std::string sharedLibName);
        std::unique_ptr<menu::mainMenu> getLoadedLib() const;
        ~loadMenuLib();

        class Error : std::exception {
        public:
            Error(std::string message) : _message(message) {}
            ~Error() = default;
            const char *what() const noexcept override {return _message.c_str();}
        private:
            std::string _message;
        };

    private:
        void *_handle;
        std::unique_ptr<menu::mainMenu> (*_getInstance)();
    };

}

#endif /* !__LOADLIB_HPP__ */
