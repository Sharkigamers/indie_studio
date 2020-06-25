#include "Bomberman.hpp"

#include <utility>
#include "BombermanRotation.hpp"

namespace Bomberman {
    namespace Graphics {
        Bomberman::Bomberman(irr::IrrlichtDevice *device, pos_t pos, int bomberNb, enum Orientation direction)
                : _device(device),_bomberNb(bomberNb), _direction(direction), _status(STAND), _pos(std::move(pos))
        {
            if (bomberNb == '1') {
                bomberNb = 0;
            }
            if (bomberNb == '2') {
                bomberNb = 1;
            }
            if (bomberNb == '3') {
                bomberNb = 2;
            }
            if (bomberNb == '4') {
                bomberNb = 3;
            }
            _bomberNb = bomberNb;
            _gameObject = std::make_shared<AGameObject>(_device, _pos, _pathAsset[_bomberNb], "bomberman", "./assets/models/bomberman_stand.b3d");
            _gameObject->setScale({6, 6, 6});
            _gameObject->setRotation({-100, 0, 0});
            this->turn(direction);
        };

        Bomberman::Bomberman(Bomberman &&cpy)
        {
            std::cout << "cpy_ctor" << std::endl;
            this->_device = cpy._device;
            this->_gameObject = cpy._gameObject;
            this->_bomberNb = cpy._bomberNb;
            std::cout << "cpy._direction = " << cpy._direction << std::endl;
            this->_direction = cpy._direction;
            this->_status = cpy._status;
            this->_pos = cpy._pos;
        };

        Bomberman &Bomberman::operator=(Bomberman const &cpy)
        {
            this->_device = cpy._device;
            this->_gameObject = cpy._gameObject;
            this->_bomberNb = cpy._bomberNb;
            this->_direction = cpy._direction;
            this->_status = cpy._status;
            this->_pos = cpy._pos;
            return (*this);
        };

        void Bomberman::run()
        {
            std::shared_ptr<AGameObject> cpy(new AGameObject(_device, _pos, _pathAsset[_bomberNb], "bomberman", "./assets/models/bomberman_run.b3d"));
            irr::core::vector3df rotation = _gameObject->getRotation();

            _gameObject.swap(cpy);
            _gameObject->setScale({6, 6, 6});
            _gameObject->setRotation(rotation);
        }

        void Bomberman::stand()
        {
            std::shared_ptr<AGameObject> cpy(new AGameObject(_device, _pos, _pathAsset[_bomberNb], "bomberman", "./assets/models/bomberman_stand.b3d"));
            irr::core::vector3df rotation = _gameObject->getRotation();

            _gameObject.swap(cpy);
            _gameObject->setScale({6, 6, 6});
            _gameObject->setRotation(rotation);
        }

        void Bomberman::drop()
        {
                    std::cerr << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO = " << std::endl;
            irr::core::vector3df rotation = _gameObject->getRotation();
            std::shared_ptr<AGameObject> cpy(new AGameObject(_device, _pos, _pathAsset[_bomberNb], "bomberman", "./assets/models/bomberman_drop.b3d"));

            _gameObject.swap(cpy);
            _gameObject->setScale({6, 6, 6});
            _gameObject->setRotation(rotation);
        }

        void Bomberman::turn(const enum Orientation &dir) //TODO check why they take forever to turn
        {
            if (dir == _direction)
                return;
            if (dir == UP)
                _gameObject->setRotation({-100, 0, -90});
            if (dir == DOWN)
                _gameObject->setRotation({-100, 0, 90});
            if (dir == RIGHT)
                _gameObject->setRotation({-100, 0, 180});
            if (dir == LEFT)
                _gameObject->setRotation({-100, 0, 0});
        //    irr::scene::ISceneNodeAnimator *ani = new BombermanRotation(_gameObject->getRotation(), _direction, dir);
        //    _gameObject->addAnimator(ani);
        //    ani->drop();
            _direction = dir;
        }

        int Bomberman::getId() const
        {
            return _bomberNb;
        }

       void Bomberman::refreshPlayer(const Game::Player &player) {
            enum Orientation dir = player.getOrientation();
            if (dir != _direction) {
                this->turn(dir);
            }
            enum Status status = player.getStatus();
            if (status != _status) {
                if (status == STAND && _status != STAND) {
                    this->stand();
                }
                else if (status == RUNNING && _status != RUNNING) {
                    this->run();
                }
                else if (status == PUT_THE_BOMB && _status != PUT_THE_BOMB) {
                    this->drop();
                }
                _status = status;
            }
            std::pair<float, float> position = player.getPosition();
//            std::cout << _pos.first << "%" << _pos.second << std::endl;
            if (position != _pos) {
                _pos = position;
                _gameObject->setPosition(_pos);
            }
//            std::cerr << "player.getPlayerIndex() = " << (char) player.getPlayerIndex() << std::endl;
//            std::cerr << "dir = " << dir << std::endl;
//            std::cerr << "status = " << status << std::endl;
//            std::cerr << "position.first = " << position.first << std::endl;
//            std::cerr << "position.second = " << position.second << std::endl;
        }
    };
};
