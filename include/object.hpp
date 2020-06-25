/*
** EPITECH PROJECT, 2020
** object
** File description:
** IndieStudio
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

enum Object {
    PLAYER1 = '1',
    PLAYER2 = '2',
    PLAYER3 = '3',
    PLAYER4 = '4',
    WALL = 'W',
    BOX = 'O',
    BOMB = 'B',
    EXPLOSION = '!',
    GROUND = ' ',
    AIPATH = 'z',
    AIFREEPATH = 'f',
    AIBOMBPLACEMENT = 'p',
    AIRUNOUT = 'r',
    EXPLOSIONRANGE = 'e',
};

struct Element {
    enum Object obj;
    int animation;
};

#endif /* !OBJECT_HPP_ */
