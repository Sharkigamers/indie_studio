/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FireCluster
*/

#include "FireCluster.hpp"

Bomberman::Game::FireCluster::FireCluster(const std::pair<float, float> &origin, int firePower, Bomberman::Game::Map &map)
    : _origin(origin), _firePower(firePower), _clock(Bomberman::GameClock()), _map(std::make_shared<Bomberman::Game::Map>(map)), _isActive(true)
{
    _positions = createListPosition(origin, firePower);
}

Bomberman::Game::FireCluster::~FireCluster()
{
}

Bomberman::Game::FireCluster::ListPosition Bomberman::Game::FireCluster::createListPosition(const std::pair<float, float> &origin, int firePower)
{
    ListPosition listPosition;

    std::get<4>(listPosition) = origin;

    for (float i = origin.first, y = origin.second, count = 0; count < firePower; count++) {
        y--;
        if (y <= 0)
            break;
        std::get<0>(listPosition).push_back(std::make_pair(i, y));
    }

    for (float i = origin.first, y = origin.second, count = 0; count < firePower; count++) {
        y++;
        std::get<2>(listPosition).push_back(std::make_pair(i, y));
    }

    for (float i = origin.first, y = origin.second, count = 0; count < firePower; count++) {
        i--;
        if (i <= 0)
            break;
        std::get<1>(listPosition).push_back(std::make_pair(i, y));
    }

    for (float i = origin.first, y = origin.second, count = 0; count < firePower; count++) {
        i++;
        std::get<3>(listPosition).push_back(std::make_pair(i, y));
    }

    return listPosition;
}


void Bomberman::Game::FireCluster::updateMap(bool create)
{
    if (create == true) {

    } else {

    }
}

void Bomberman::Game::FireCluster::updateCluster()
{
    if (_clock.getEllapsedTime() > _expireTiming)
        _isActive = false;
}