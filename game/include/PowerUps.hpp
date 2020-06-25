/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUps
*/

#ifndef POWERUPS_HPP_
#define POWERUPS_HPP_

#include <stdint.h>

namespace Bomberman {
    namespace Game {
        class PowerUps {
            public:
                PowerUps() {};
                ~PowerUps() {};

                uint16_t getFirePower() const { return _fire; }
                uint16_t getBombCount() const { return _bombCount; }
                uint16_t getSpeed() const { return _speed; }
                bool canWallPass() const { return _wallPass; }

                void incrementFire() { _fire++; }
                void incrementBombCount() { _bombCount++; }
                void incrementSpeed() { _speed++; }
                void setWallPass(bool canPass = true) { _wallPass = canPass; }

                void setFire(uint16_t fire) { _fire = fire; }
                void setBombCount(uint16_t BombCount) { _bombCount = BombCount; }
                void setSpeed(uint16_t Speed) { _speed = Speed; }

            protected:
            private:
                uint16_t _fire = 1;
                uint16_t _bombCount = 1;
                uint16_t _speed = 1;
                bool _wallPass = false;
        };
    }
}

#endif /* !POWERUPS_HPP_ */
