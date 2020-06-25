/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapCreation
*/

#ifndef MAPCREATION_HPP_
#define MAPCREATION_HPP_

#include <vector>

namespace Bomberman {
    namespace Game {
        class MapCreation {
            public:
                MapCreation(unsigned short x, unsigned short y);
                ~MapCreation();

                void createMap(std::string mapName);

                void setLengths(unsigned short x, unsigned short y) {
                    _xLength = x;
                    _yLength = y;
                }

                char randomPlace();
                char placePlayersAndOther(unsigned short i, unsigned short j);
                bool freeSpawnPlace(unsigned short i, unsigned short j);

            protected:
            private:
                unsigned short _xLength;
                unsigned short _yLength;
        };
    }
}

#endif /* !MAPCREATION_HPP_ */
