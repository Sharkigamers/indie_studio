/*
** EPITECH PROJECT, 2020
** GameClass
** File description:
** IndieStudio
*/

#ifndef GAMECLASS_HPP_
#define GAMECLASS_HPP_

#include <map>
#include <vector>
#include <algorithm>

namespace Bomberman {
    namespace Game {
        class Bomb;
        class Player;
        class Map;
    }
}

#include "Object.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "DataType.hpp"
#include "MapCreation.hpp"
#include "Saver.hpp"

namespace Bomberman {
    namespace Game {
        class GameClass {
            public:
                GameClass(const std::vector<PlayerIndex> &IAS, int musicId, const std::string mapPath);
                GameClass(const std::string &gameSavePath);
                ~GameClass();

                int input(const std::map<PlayerIndex, std::vector<enum Event>> &inputs);
                std::map<std::pair<float, float>, Element> &getMap() { return _map.getMap(); }
                std::map<PlayerIndex, Bomberman::Game::Player &> getPlayers();
                void pushPlayer(PlayerIndex playerIndex, const std::string name = "Lopez");
                void pushIA(PlayerIndex playerIndex);
                void updateGameState();

                Bomberman::Game::Map &getObjMap() { return _map; }
                bool isGameOver() const;
                std::map<std::string, int> getFinalScore() const;

                void updateAi();

                void saveGame(std::map<std::pair<float, float>, Element> &map,
                std::map<PlayerIndex, Bomberman::Game::Player&> player) { 
                    Bomberman::Game::Saver gameSave;
                    
                    gameSave.save(map, player);
                }

            protected:
            private:
                Bomberman::Game::Map _map;
                std::vector<Bomberman::Game::Player> _players;
        };
    }
}

#endif /* !GAMECLASS_HPP_ */
