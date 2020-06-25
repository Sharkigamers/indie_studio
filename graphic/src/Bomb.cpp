#include "Bomb.hpp"

static std::vector<std::string> _assets = {   
            "./assets/FireBomb/bomb/bomb_000001.obj",
            "./assets/FireBomb/bomb/bomb_000002.obj",
            "./assets/FireBomb/bomb/bomb_000003.obj",
            "./assets/FireBomb/bomb/bomb_000004.obj",
            "./assets/FireBomb/bomb/bomb_000005.obj",
            "./assets/FireBomb/bomb/bomb_000006.obj",
            "./assets/FireBomb/bomb/bomb_000007.obj",
            "./assets/FireBomb/bomb/bomb_000008.obj",
            "./assets/FireBomb/bomb/bomb_000009.obj",
            "./assets/FireBomb/bomb/bomb_000010.obj",
            "./assets/FireBomb/bomb/bomb_000011.obj",
            "./assets/FireBomb/bomb/bomb_000012.obj",
            "./assets/FireBomb/bomb/bomb_000013.obj",
            "./assets/FireBomb/bomb/bomb_000014.obj",
            "./assets/FireBomb/bomb/bomb_000015.obj",
            "./assets/FireBomb/bomb/bomb_000016.obj",
            "./assets/FireBomb/bomb/bomb_000017.obj",
            "./assets/FireBomb/bomb/bomb_000018.obj",
            "./assets/FireBomb/bomb/bomb_000019.obj",
            "./assets/FireBomb/bomb/bomb_000020.obj",
            "./assets/FireBomb/bomb/bomb_000021.obj",
            "./assets/FireBomb/bomb/bomb_000022.obj",
            "./assets/FireBomb/bomb/bomb_000023.obj",
            "./assets/FireBomb/bomb/bomb_000024.obj",
            "./assets/FireBomb/bomb/bomb_000025.obj",
            "./assets/FireBomb/bomb/bomb_000026.obj",
            "./assets/FireBomb/bomb/bomb_000027.obj",
            "./assets/FireBomb/bomb/bomb_000028.obj",
            "./assets/FireBomb/bomb/bomb_000029.obj",
            "./assets/FireBomb/bomb/bomb_000030.obj",
            };

namespace Bomberman {
    namespace Graphics {
        Bomb::Bomb(irr::IrrlichtDevice *device, pos_t pos): 
        MeshContainer(device, "./assets/FireBomb/bomb/textures/Bomb.png", _assets, pos, irr::core::vector3df(5), irr::core::vector3df(-100, 0, 0), "Bomb", std::chrono::milliseconds(10))
        {}
            
    }
}
