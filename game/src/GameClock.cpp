/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameClock
*/

#include "GameClock.hpp"

Bomberman::GameClock::GameClock()
    : _start(std::chrono::system_clock::now())
{
}

Bomberman::GameClock::GameClock(const GameClock &other)
{
    if (&other != this) {
        this->_start = other._start;
    }
}

Bomberman::GameClock::~GameClock()
{
}

Bomberman::GameClock &Bomberman::GameClock::operator=(const GameClock &other)
{
    if (&other != this) {
        this->_start = other._start;
    }
    return *this;
}

void Bomberman::GameClock::start()
{
    _start = std::chrono::system_clock::now();
}

void Bomberman::GameClock::reset()
{
    _start = std::chrono::system_clock::now();
}

uint64_t Bomberman::GameClock::getEllapsedTime() const
{
    std::chrono::time_point<std::chrono::system_clock> end;
    uint64_t elapsed = 0.0f;

    end = std::chrono::system_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-this->_start).count();
    return elapsed;
}
