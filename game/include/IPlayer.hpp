/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IPlayer
*/

#ifndef IPLAYER_HPP_
#define IPLAYER_HPP_



#include "Map.hpp"
#include "Object.hpp"

#include "DataType.hpp"

namespace Bomberman {
    namespace Game {
        class IPlayer {
            public:
                virtual ~IPlayer() {};

                virtual void applyEvent(enum Event, Bomberman::Game::Map &map) = 0;
            protected:
            private:
        };
    }
}
#endif /* !IPLAYER_HPP_ */
