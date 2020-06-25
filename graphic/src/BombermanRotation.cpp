#include "BombermanRotation.hpp"

namespace Bomberman {
    namespace Graphics {
        BombermanRotation::BombermanRotation(const irr::core::vector3df &vect, enum Orientation current_dir, enum Orientation dir):
        _finished(false), _dir(dir)
        {
            _goal = vect;
            _vect = vect;
            _inc = 1;
            if (current_dir == dir)
                _finished == true;

            if (current_dir == DOWN) {
                if (dir == LEFT) {
                    _inc *= -1;
                    _goal.Z = -90; 
                }
                if (dir == RIGHT) {
                    _goal.Z = 90; 
                }
                if (dir == UP) {
                    _goal.Z = 180; 
                }
            }
            if (current_dir == RIGHT) {
                if (dir == LEFT) {
                    _goal.Z = 270; 
                }
                if (dir == UP) {
                    _goal.Z = 180; 
                }
                if (dir == DOWN) {
                    _inc *= -1;
                    _goal.Z = 0;
                }
            }
            if (current_dir == UP) {
                if (dir == LEFT) {
                    _goal.Z = 270; 
                }
                if (dir == RIGHT) {
                    _inc *= -1;
                    _goal.Z = 90; 
                }
                if (dir == DOWN) {
                    _inc *= -1;
                    _goal.Z = 0;
                }
            }
            if (current_dir == LEFT) {
                if (dir == UP) {
                    _inc *= -1;
                    _goal.Z = -180; 
                }
                if (dir == RIGHT) {
                    _goal.Z = 90;
                }
                if (dir == DOWN) {
                    _goal.Z = 0;
                }
            }
        }

        BombermanRotation::BombermanRotation(const BombermanRotation &cpy)
        {
            _finished = cpy._finished; 
            _dir = cpy._dir;
            _goal = cpy._goal;
            _vect = cpy._vect;
        }


        void BombermanRotation::animateNode(irr::scene::ISceneNode *node, irr::u32 timeMs)
        {
            // std::cout << "coucou" << std::endl;
            if (!_finished) {
                _vect.Z += _inc;
                std::cout << "Z = " << _vect.Z << std::endl;
                std::cout << "goal Z = " << _goal.Z << std::endl;
                // std::cout << finished << _goal.Z << std::endl;
                node->setRotation(irr::core::vector3df(_vect));
                if (_vect == _goal) {
                    std::cout << "succeed" << std::endl;
                    if (_vect.Z == 270)
                        _vect.Z = -90;
                    if (_vect.Z == -180)
                        _vect.Z = 180;
                    node->setRotation(_vect);
                    _finished = true;
                }
            }
        }

        irr::scene::ISceneNodeAnimator *BombermanRotation::createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager)
        {
            BombermanRotation *cpy = new BombermanRotation(*this);
            node->addAnimator(cpy);
            return cpy;
        }
    }
}