#include "Flame.hpp"

static  std::vector<std::string> _assets = {   
            "./assets/FireBomb/flame/fire_000001.obj",
            "./assets/FireBomb/flame/fire_000002.obj",
            "./assets/FireBomb/flame/fire_000003.obj",
            "./assets/FireBomb/flame/fire_000004.obj",
            "./assets/FireBomb/flame/fire_000005.obj",
            "./assets/FireBomb/flame/fire_000006.obj",
            "./assets/FireBomb/flame/fire_000007.obj",
            "./assets/FireBomb/flame/fire_000008.obj",
            "./assets/FireBomb/flame/fire_000009.obj",
            "./assets/FireBomb/flame/fire_000010.obj",
            "./assets/FireBomb/flame/fire_000011.obj",
            "./assets/FireBomb/flame/fire_000012.obj",
            "./assets/FireBomb/flame/fire_000013.obj",
            "./assets/FireBomb/flame/fire_000014.obj",
            "./assets/FireBomb/flame/fire_000015.obj",
            "./assets/FireBomb/flame/fire_000016.obj",
            "./assets/FireBomb/flame/fire_000017.obj",
            "./assets/FireBomb/flame/fire_000018.obj",
            "./assets/FireBomb/flame/fire_000019.obj",
            "./assets/FireBomb/flame/fire_000020.obj",
            "./assets/FireBomb/flame/fire_000021.obj",
            "./assets/FireBomb/flame/fire_000022.obj",
            "./assets/FireBomb/flame/fire_000023.obj",
            "./assets/FireBomb/flame/fire_000024.obj",
            "./assets/FireBomb/flame/fire_000025.obj",
            "./assets/FireBomb/flame/fire_000026.obj",
            "./assets/FireBomb/flame/fire_000027.obj",
            "./assets/FireBomb/flame/fire_000028.obj",
            "./assets/FireBomb/flame/fire_000029.obj",
            "./assets/FireBomb/flame/fire_000030.obj",
            };

namespace Bomberman {
    namespace Graphics {
        Flame::Flame(irr::IrrlichtDevice *device, pos_t pos): 
        MeshContainer(device, "./assets/FireBomb/flame/Fire.png", 
        _assets, 
        pos, 
        irr::core::vector3df(10), 
        irr::core::vector3df({-100, 0, 0}), 
        "Flame", 
        std::chrono::milliseconds(1))
        {}
    }
}