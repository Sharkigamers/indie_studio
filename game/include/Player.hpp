/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

namespace Bomberman {
    namespace Game {
        class Map;
    }
}

#include "IPlayer.hpp"
#include "DataType.hpp"
#include "PowerUps.hpp"
#include "GameClock.hpp"

#include <memory>
#include <algorithm>

namespace Bomberman {
    namespace Game {
        class Player : public IPlayer {
            public:
                Player(Bomberman::Game::Map &map, enum PlayerIndex index, bool isIA, const std::string name = "random");
                ~Player();

                void applyEvent(enum Event, Bomberman::Game::Map &map) final;
                enum Orientation getOrientation() const { return _playerOrientation; }
                enum Status getStatus() const { return _playerStatus; }
                void setStatus(const enum Status status) { _playerStatus = status; }
                std::pair<float, float> getPosition() const;
                std::pair<std::pair<int, int>, std::pair<int, int>> getRealPosition() const { return _position; };
                void setPosition(const std::pair<std::pair<int, int>, std::pair<int, int>> &newPos) { _position = newPos; }
                enum PlayerIndex getPlayerIndex() const { return _playerIndex; }
                void movePlayer(Bomberman::Game::Map &map, int yDirection, int xDirection);
                void putBomb(Bomberman::Game::Map &map);
                bool isIA() const { return _isIA; }
                std::string getName() const { return _name; }
                int getScore() const { return _score; }
                void addScore(int toAdd) { _score += toAdd; };
                Bomberman::GameClock &getPlayerClock() { return _playerClock; }
                Bomberman::GameClock &getPlayerBombClock() { return _playerPutBombClock; }

                bool isAlive() const { return _alive; }
                void setAlive(bool alive) { _alive = alive; }
                void updateMap(Bomberman::Game::Map &map) { _map = std::make_shared<Bomberman::Game::Map>(map); }

                int getPlacedBombCount() const { return _placedBombCount; }
                void incBombCount() { _placedBombCount++; }
                void decBombCount() { _placedBombCount--; }

                Bomberman::Game::PowerUps getCurrentPowerUps() const { return _currentPowerUps; }
                bool operator==(const PlayerIndex &idx) { return _playerIndex == idx; }

                void findBestPath(std::vector<std::vector<char>> myMap);
                std::vector<std::vector<char>> copyMap();
                
                bool walkablePath(std::vector<std::vector<char>> &myMap, short &x,
                short &y, std::vector<std::pair<char, short>> &action, bool specificWalk);
                
                bool backOnWalked(std::vector<std::vector<char>> &myMap, short &x,
                short &y, std::vector<std::pair<char, short>> &action, bool specificWalk);

                void drawWalkablePath();

                void wichKeepBombPlacement(std::vector<std::vector<char>> &myMap);
                std::tuple<std::pair<int, int>, char, float> findRange(
                std::pair<int, int> currentPlacement, std::vector<std::vector<char>> &myMap,
                std::tuple<std::pair<int, int>, char, float> bestPlacement);

                enum Event chooseDirectionOfAi();
                enum Event moveAi();

                void actionAi(Bomberman::Game::Map &map);

                void runOutOfBomb(Bomberman::Game::Map &map);
                void putExplosionRange(short bombX, short bombY, uint16_t range,
                short x, short y, std::vector<std::vector<char>> &myMap);

                void incrementFire() { _currentPowerUps.incrementFire(); }
                void incrementBombCount() { _currentPowerUps.incrementBombCount(); }
                void incrementSpeed() { _currentPowerUps.incrementSpeed(); }
                void setWallPass(bool canPass = true) { _currentPowerUps.setWallPass(); }

            protected:
            private:
                enum Orientation _playerOrientation;
                enum Status _playerStatus;
                std::shared_ptr<Bomberman::Game::Map> _map;
                std::pair<std::pair<int, int>, std::pair<int, int>> _position;
                enum PlayerIndex _playerIndex;
                bool _isIA;
                Bomberman::Game::PowerUps _currentPowerUps;
                std::string _name;
                int _score = 0;
                std::vector<std::vector<char>> _aiMap;
                Bomberman::GameClock _playerClock;
                Bomberman::GameClock _playerPutBombClock;
                bool _isOnPlacementBomb = false;
                bool _isOnSafe = false;
                int _placedBombCount = 0;
                std::vector<std::pair<float, float>> _walkPositions;
                std::vector<std::pair<float, float>> _walkSafe;
                std::vector<std::pair<float, float>> _onSafe;
                bool _alive = true;
        };
    }
}

#endif /* !PLAYER_HPP_ */
