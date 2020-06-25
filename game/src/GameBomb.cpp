/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "GameBomb.hpp"

Bomberman::Game::Bomb::Bomb(std::pair<float, float> position, uint64_t explosionTiming, Bomberman::Game::Player *player)
    : ObjectClass(MOVEABLE, "Bomb"), _position(position), _explosionTiming(explosionTiming), _player(player)
{
}

Bomberman::Game::Bomb::~Bomb()
{
}

void Bomberman::Game::Bomb::updateTime()
{
    if (_bombClock.getEllapsedTime() >= _explosionTiming)
        _active = false;
}