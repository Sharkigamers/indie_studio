/*
** EPITECH PROJECT, 2020
** Map
** File description:
** IndieStudio
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

namespace Bomberman {
    namespace Game {
        class Bomb;
        class Player;
        class FireCluster;
    }
}

#include "GameBomb.hpp"
#include "FireCluster.hpp"
#include "Player.hpp"
#include "object.hpp"
#include "DataType.hpp"

#define BOX_DESTROY_SCORE 50
#define PLAYER_DESTROY_SCORE 500

namespace Bomberman {
    namespace Game {
        class Map {
            public:
                Map(const std::string path = "", std::string fileContent = "");
                ~Map();

                std::map<std::pair<float, float>, Element> &getMap() { return _map; }
                std::string getFileContent(const std::string path);
                std::map<std::pair<float, float>, Element> initializeMap(const std::string path);

                std::map<enum PlayerIndex, bool> getAlivePlayerMap() const { return _playerAliveMap; }

                void pushBomb(const Bomberman::Game::Bomb &bomb);
                std::vector<Bomberman::Game::Bomb> &getListBomb() { return _listBomb; }
                void checkBombsTiming(std::vector<Bomberman::Game::Player> &players);

                void updateAll(std::vector<Bomberman::Game::Player> &players);
                void handleBombExplosion(const Bomberman::Game::Bomb &bomb, Bomberman::Game::Player *players);
                void updatePlayerPositions(std::vector<Bomberman::Game::Player> &players);

                void destroyBox(const Bomberman::Game::Bomb &bomb);

                void createFireCluster(const Bomberman::Game::Bomb &bomb);
                void addFireClusterInMap(const Bomberman::Game::FireCluster &cluster);
                void removeFireClusterFromMap(const Bomberman::Game::FireCluster &cluster);
                void updateFireClusters();

                void handleBombTrail(const std::vector<std::pair<float, float> > &listPosition, const Bomberman::Game::Bomb &bomb);

            protected:
            private:
                std::map<std::pair<float, float>, Element> _map;
                std::vector<Bomberman::Game::Bomb> _listBomb;
                std::vector<Bomberman::Game::FireCluster> _listFireClusters;
                std::map<enum PlayerIndex, bool> _playerAliveMap;
        };
    }
}

#endif /* !MAP_HPP_ */
