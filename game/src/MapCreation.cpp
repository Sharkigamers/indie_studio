/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapCreation
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <string>

#include "MapCreation.hpp"
#include "object.hpp"

Bomberman::Game::MapCreation::MapCreation(unsigned short x, unsigned short y)
{
    srand(time(NULL));
    _xLength = x;
    _yLength = y;
}

Bomberman::Game::MapCreation::~MapCreation()
{
}

char Bomberman::Game::MapCreation::randomPlace()
{
    int objRand = rand() % 100;

    if (objRand < 20)
        return WALL;
    else if (objRand < 50)
        return GROUND;
    else
        return BOX;
}

bool Bomberman::Game::MapCreation::freeSpawnPlace(unsigned short i, unsigned short j)
{
    if (i == 1 && (j == 2 || j == 3 || j == _xLength - 3 || j == _xLength - 4))
        return true;
    if ((j == 1 || j == _xLength - 2) && (i == 2 || i == 3))
        return true;
    if (i == _yLength - 2 && (j == 2 || j == 3 || j == _xLength - 3 || j == _xLength - 4))
        return true;
    if ((j == 1 || j == _xLength - 2) && (i == _yLength - 3 || i == _yLength - 4))
        return true;
    return false;
}

char Bomberman::Game::MapCreation::placePlayersAndOther(unsigned short i, unsigned short j)
{
    if (i == 1 && j == 1)
        return PLAYER1;
    if (i == 1 && j == _xLength - 2)
        return PLAYER2;
    if (i == _yLength - 2 && j == 1)
        return PLAYER3;
    if (i == _yLength - 2 && j == _xLength - 2)
        return PLAYER4;
    if (freeSpawnPlace(i, j))
        return GROUND;
    return randomPlace();
}

void Bomberman::Game::MapCreation::createMap(std::string mapName)
{
    std::ofstream myMap(mapName);
    std::vector<std::vector<char>> map;
    std::vector<char> line;
    std::string stringLine = "";

    for (unsigned short i = 0; i < _yLength; ++i) {
        for (unsigned short j = 0; j < _xLength; ++j) {
            if (i == 0 || i == _yLength - 1 || j == 0 || j == _xLength - 1)
                line.push_back(WALL);
            else {
                line.push_back(placePlayersAndOther(i, j));
            }
        }
        stringLine = "";
        for (auto &charact: line) {
            std::string charToString(1, charact);
            stringLine.append(charToString);
        }
        myMap << stringLine << std::endl;
        line.clear();
    }
    myMap.close();
}

// int main(void)
// {
//     auto m = Bomberman::Game::MapCreation(13, 11);
//     std::vector<std::vector<char>> myMap;
//     static const std::string path = "assets/map/";

//     myMap = m.createMap(path + "map.map");
//     for (auto const &line: myMap) {
//         for (auto charact: line) {
//             printf("%c", charact);
//         }
//         printf("\n");
//     }
// }
