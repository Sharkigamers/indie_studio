
#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include "Player.hpp"
#include "AGameObject.hpp"
#include <utility>

#include "Player.hpp"

namespace Bomberman {
    namespace Graphics {
//         class Player {//TODO DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEe
//             Orientation _playerOrientation;
//             Status _playerStatus;
//             std::pair<float, float> _position;
//             PlayerIndex _playerIndex;

//             public:
//                 Player(Orientation playerOrientation, Status playerStatus, std::pair<float, float> position, PlayerIndex index)
//                 : _playerOrientation(playerOrientation), _playerStatus(playerStatus), _position(std::move(position)), _playerIndex(index) {
// //                    std::cerr << "player.getPlayerIndex() = " << (char) _playerIndex << std::endl;
// //                    std::cerr << "dir = " << _playerOrientation << std::endl;
// //                    std::cerr << "status = " << _playerStatus << std::endl;
// //                    std::cerr << "position.first = " << _position.first << std::endl;
// //                    std::cerr << "position.second = " << _position.second << std::endl;
//                 };
//                 ~Player() = default;

// //                void applyEvent(enum Event, Bomberman::Game::Map &map) final;
//                 Orientation getOrientation() const { return _playerOrientation; }
//                 Status getStatus() const { return _playerStatus; }
//                 PlayerIndex getPlayerIndex() const { return _playerIndex; }
//                 std::pair<float, float> getPosition() const { return _position; }
//         };

        class Bomberman {
            irr::IrrlichtDevice *_device;
            std::shared_ptr<AGameObject> _gameObject;

            std::vector<std::string> _pathAsset = {"./assets/textures/bomberman_black.png",
                                                "./assets/textures/bomberman_blue.png", 
                                                "./assets/textures/bomberman_green.png",
                                                "./assets/textures/bomberman_lblue.png"};

            int _bomberNb;
            enum Orientation _direction;
            enum Status _status;
            std::pair<float, float> _pos;

            public:
                Bomberman(irr::IrrlichtDevice *device, pos_t pos, int bomberNb, enum Orientation direction);
                Bomberman(Bomberman &&cpy);
                Bomberman &operator=(Bomberman const &cpy);
                ~Bomberman() = default;

                void run();
                void stand();
                void drop();
                void turn(const enum Orientation &dir);
                int getId() const;
                void refreshPlayer(const Game::Player &player);

                bool operator==(const int toCompare) const { return getId() == toCompare; }

        };
    };
};

#endif