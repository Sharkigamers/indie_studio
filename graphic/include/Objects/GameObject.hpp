
#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <irrlicht.h>
#include <vector>
#include <string>
#include <memory>
#include "AGameObject.hpp"

namespace Bomberman {
    namespace Graphics {
        class Grass : public AGameObject 
        {
            public:
                Grass(IrrlichtDevice *device, pos_t pos) : AGameObject(device, pos, "./assets/Terrain/grass.png", "Grass") {};
                ~Grass() = default;
        };
    }
}

namespace Bomberman {
    namespace Graphics {
        class Wall : public AGameObject
        {
            public:
                Wall(IrrlichtDevice *device, pos_t pos): AGameObject(device, pos, "./assets/textures/minecraftBrick.png", "Wall") {};
                ~Wall() = default;
        };
    }
}

namespace Bomberman {
    namespace Graphics {
        class Box : public AGameObject {
            public:
                Box(IrrlichtDevice *device, pos_t pos) : AGameObject(device, pos, "./assets/textures/box.jpg", "Box") {};
                ~Box() = default;
        };
    }
}

#endif