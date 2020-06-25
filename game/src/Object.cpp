/*
** EPITECH PROJECT, 2020
** Object
** File description:
** Object
*/

#include "Object.hpp"

Bomberman::Game::ObjectClass::ObjectClass(const objectStatus givenStatus, const std::string &name)
: _status(givenStatus), _name(name)
{
}

Bomberman::Game::ObjectClass::~ObjectClass()
{
}

objectStatus Bomberman::Game::ObjectClass::getStatus() const
{
    return _status;
}

void Bomberman::Game::ObjectClass::damageObject()
{
    _alive = false;
}

bool Bomberman::Game::ObjectClass::isBreak()
{
    if (_status == BREAKABLE && !_alive)
        return true;
    return false;
}
