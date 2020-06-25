#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "Core.hpp"
#include <irrlicht.h>
#include "DataType.hpp"

int main()
{
    Bomberman::Graphics::EventReceiver receiver;
    irr::IrrlichtDevice *device = createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &receiver);
//    irr::IrrlichtDevice *device = createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, false, &receiver);
    std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer = {
            {PLAYER1_INDEX, {{ACTION_UP, (int) irr::KEY_KEY_Z}, {ACTION_DOWN, (int) irr::KEY_KEY_S}, {ACTION_LEFT, (int) irr::KEY_KEY_Q}, {ACTION_RIGHT, (int) irr::KEY_KEY_D}, {ACTION_ACTION, (int) irr::KEY_KEY_E}}},
            {PLAYER2_INDEX, {{ACTION_UP, (int) irr::KEY_KEY_F}, {ACTION_DOWN, (int) irr::KEY_KEY_V}, {ACTION_LEFT, (int) irr::KEY_KEY_C}, {ACTION_RIGHT, (int) irr::KEY_KEY_B}, {ACTION_ACTION, (int) irr::KEY_KEY_N}}},
            {PLAYER3_INDEX, {{ACTION_UP, (int) irr::KEY_KEY_Y}, {ACTION_DOWN, (int) irr::KEY_KEY_G}, {ACTION_LEFT, (int) irr::KEY_KEY_H}, {ACTION_RIGHT, (int) irr::KEY_KEY_J}, {ACTION_ACTION, (int) irr::KEY_KEY_U}}},
            {PLAYER4_INDEX, {{ACTION_UP, (int) irr::KEY_KEY_O}, {ACTION_DOWN, (int) irr::KEY_KEY_L}, {ACTION_LEFT, (int) irr::KEY_KEY_K}, {ACTION_RIGHT, (int) irr::KEY_KEY_M}, {ACTION_ACTION, (int) irr::KEY_KEY_P}}},
    };

    std::vector<enum PlayerIndex> playerIA = {}; //No AI

    Bomberman::Core core;

    // core.gameLoop(device, receiver, mapKeyPlayer, playerIA, 0, 0);
    // core.menuLoop(device, receiver);
    core.generalLoop(device, receiver);
    return 0;
}
