/*
** EPITECH PROJECT, 2020
** keys.cpp
** File description:
** Keys
*/

#include "Menu.hpp"

// order is UP LEFT DOWN RIGHT

movement_t MyMenu::createMapKey(std::wstring &keys) const
{
    movement_t move;

    if (keys[0] >= 97 && keys[0] <= 122)
        keys[0] -= 32;
    if (keys[1] >= 97 && keys[1] <= 122)
        keys[1] -= 32;
    if (keys[2] >= 97 && keys[2] <= 122)
        keys[2] -= 32;
    if (keys[3] >= 97 && keys[3] <= 122)
        keys[3] -= 32;
    if (keys[4] >= 97 && keys[4] <= 122)
        keys[4] -= 32;
    move[ACTION_RIGHT] = keys[0];
    move[ACTION_UP] = keys[1];
    move[ACTION_LEFT] = keys[2];
    move[ACTION_DOWN] = keys[3];
    move[ACTION_ACTION] = keys[4];
    return (move);
}

PlayerIndex MyMenu::intToIndex(int nb) const
{
    switch (nb) {
        case 0:
            return (PLAYER1_INDEX);
        case 1:
            return (PLAYER2_INDEX);
        case 2:
            return (PLAYER3_INDEX);
        case 3:
            return (PLAYER4_INDEX);
        default:
            return (PLAYER4_INDEX);
    }
}

playerKeys_t MyMenu::bindPlayerKeys()
{
    playerKeys_t map;

    for (size_t i = 0; i != _playables.size(); ++i)
        map[intToIndex(_playables[i])] = createMapKey(_keymap[i]);
    return (map);
}