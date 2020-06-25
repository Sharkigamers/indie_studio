#ifndef FLAME_HPP
#define FLAME_HPP

#include <irrlicht.h>
#include <memory>
#include "AGameObject.hpp"
#include <chrono>
#include "MeshContainer.hpp"

namespace Bomberman {
    namespace Graphics {
        class Flame: public MeshContainer {
           
            public:
                Flame(irr::IrrlichtDevice *device, pos_t pos);
                ~Flame() = default;
        };
    }
}

#endif