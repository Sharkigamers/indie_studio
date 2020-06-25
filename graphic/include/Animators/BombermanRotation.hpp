#ifndef BOMBERMAN_ROTATION_HPP 
#define BOMBERMAN_ROTATION_HPP

#include <irrlicht.h>
#include <iostream>
#include "DataType.hpp"
//#include "Player.hpp"

// #include ""

namespace Bomberman {
    namespace Graphics {
        class BombermanRotation: public irr::scene::ISceneNodeAnimator {

            irr::core::vector3df _vect;
            irr::core::vector3df _goal;

            bool _finished;
            enum Orientation _dir;
            int _inc;

            public:
                BombermanRotation(const irr::core::vector3df &vect, enum Orientation current_dir, enum Orientation dir);
                BombermanRotation(const BombermanRotation& cpy);
                ~BombermanRotation() = default;
                void animateNode(irr::scene::ISceneNode *node, irr::u32 timeMs) override;
                irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                        irr::scene::ISceneManager* newManager) override;
                bool hasFinished(void) const override
                {
                    return _finished;
                }
            };

    };
}


#endif