/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FireCluster
*/

#ifndef FIRECLUSTER_HPP_
#define FIRECLUSTER_HPP_

#include "GameClock.hpp"
#include "Map.hpp"

#include <tuple>

namespace Bomberman {
    namespace Game {
        class FireCluster {
            public:
                using ListPosition = std::tuple<std::vector<std::pair<float, float>>, std::vector<std::pair<float, float>>, std::vector<std::pair<float, float>>, std::vector<std::pair<float, float>>, std::pair<float, float> >;

            public:
                FireCluster(const std::pair<float, float> &origin, int firePower, Bomberman::Game::Map &map);
                ~FireCluster();

                void updateMap(bool create);
                void updateCluster();

                std::pair<float, float> getOrigin() const { return _origin; }
                bool getActive() const { return _isActive; }

                static ListPosition createListPosition(const std::pair<float, float> &origin, int firePower);
                ListPosition getListPosition() const { return _positions; }

                bool operator==(const FireCluster &other) { return _origin == other.getOrigin();}

            protected:
            private:
                std::pair<float, float> _origin;
                ListPosition _positions;
                int _firePower;
                Bomberman::GameClock _clock;
                std::shared_ptr<Bomberman::Game::Map> _map;
                bool _isActive;
                float _expireTiming = 2000;
        };
    }
}

#endif /* !FIRECLUSTER_HPP_ */
