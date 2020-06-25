/*
** EPITECH PROJECT, 2020
** DataType
** File description:
** DataType
*/

#ifndef DATATYPE_HPP_
#define DATATYPE_HPP_
#include <unordered_map>
#include <vector>

namespace Bomberman {
    enum Orientation {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    enum Status {
        RUNNING,
        STAND,
        PUT_THE_BOMB
    };
}

enum Action {
    A,
    Z,
    Q,
    S,
    D
};

enum Event {
    ACTION_STAND,
    ACTION_UP,
    ACTION_DOWN,
    ACTION_RIGHT,
    ACTION_LEFT,
    ACTION_ACTION
};

struct ActionMouse {
    std::pair<int, int> pos;
    bool press;
};

typedef enum PlayerIndex {
    PLAYER1_INDEX = '1',
    PLAYER2_INDEX = '2',
    PLAYER3_INDEX = '3',
    PLAYER4_INDEX = '4'
} PlayerIndex;

#endif
