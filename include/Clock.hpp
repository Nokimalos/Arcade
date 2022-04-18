/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include <chrono>

class Clock {
    public:
        Clock();
        ~Clock();
        void restart();
        int getElapsedTime();
    protected:
    private:
		std::chrono::time_point<std::chrono::steady_clock> _clock;
};

#endif /* !CLOCK_HPP_ */
