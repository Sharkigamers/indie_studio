/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <memory>

#include "GameClock.hpp"
#include "Object.hpp"

namespace Bomberman {
    namespace Game {
        class Player;
        class Bomb;
    }
}

#include "Player.hpp"

namespace Bomberman {
    namespace Game {
        class Bomb : public Bomberman::Game::ObjectClass {
            public:
                Bomb(std::pair<float, float> position, uint64_t explosionTiming, Bomberman::Game::Player *playerIndex);
                ~Bomb();

                bool getActive() const { return _active; }
                void setActive(bool newState) { _active = newState; }
                std::pair<float, float> getPosition() const { return _position; }
                void updateTime();

                bool operator==(const Bomb &other) { return getPosition() == other.getPosition(); }
                bool operator==(const std::pair<float, float> &pos) { return getPosition() == pos; }

                Bomberman::Game::Player *getPlayer() const { return _player; }

            protected:
            private:
                Bomberman::GameClock _bombClock;
                bool _active = true;
                uint64_t _explosionTiming;
                Bomberman::Game::Player *_player;
                std::pair<float, float> _position;
        };
    }
}

#endif /* !BOMB_HPP_ */
