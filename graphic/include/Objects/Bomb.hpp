#ifndef BOMBG_HPP
#define BOMBG_HPP

#include <irrlicht.h>
#include <memory>
#include "AGameObject.hpp"
#include <chrono>
#include "MeshContainer.hpp"

namespace Bomberman {
    namespace Graphics {
        class Bomb: public MeshContainer {
            
            public:
                Bomb(irr::IrrlichtDevice *device, pos_t pos);
                ~Bomb() = default;
        };
    }
}

#endif