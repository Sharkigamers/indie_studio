/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameClock
*/

#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <inttypes.h>
#include <chrono>
#include <time.h>

namespace Bomberman {
    class GameClock {
        public:
            GameClock(const GameClock &other);
            GameClock();
            ~GameClock();

            GameClock &operator=(const GameClock &other);

            void start();
            void reset();
            
            uint64_t getEllapsedTime() const;

        protected:
        private:
            std::chrono::time_point<std::chrono::system_clock> _start;
    };
}


#endif /* !GAMECLOCK_HPP_ */
