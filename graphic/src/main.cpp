#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include <vector>
#include <memory>
#include "GameGraphic.hpp"

using namespace irr;

int main()
{
    Bomberman::Graphics::EventReceiver receiver;
    std::map<std::pair<float, float>, Element> map = initializeMap("./map/map3.txt");
//    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(1920, 1080), 16, false, false, false, &receiver);
    std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer = {
            {PLAYER1_INDEX, {{UP, (int) irr::KEY_KEY_Z}, {DOWN, (int) irr::KEY_KEY_S}, {LEFT, (int) irr::KEY_KEY_Q}, {RIGHT, (int) irr::KEY_KEY_D}, {ACTION, (int) irr::KEY_KEY_E}}},
            {PLAYER2_INDEX, {{UP, (int) irr::KEY_KEY_F}, {DOWN, (int) irr::KEY_KEY_V}, {LEFT, (int) irr::KEY_KEY_C}, {RIGHT, (int) irr::KEY_KEY_B}, {ACTION, (int) irr::KEY_KEY_N}}},
            {PLAYER3_INDEX, {{UP, (int) irr::KEY_KEY_Y}, {DOWN, (int) irr::KEY_KEY_G}, {LEFT, (int) irr::KEY_KEY_H}, {RIGHT, (int) irr::KEY_KEY_J}, {ACTION, (int) irr::KEY_KEY_U}}},
            {PLAYER4_INDEX, {{UP, (int) irr::KEY_KEY_O}, {DOWN, (int) irr::KEY_KEY_L}, {LEFT, (int) irr::KEY_KEY_K}, {RIGHT, (int) irr::KEY_KEY_M}, {ACTION, (int) irr::KEY_KEY_P}}},
    };
//    Bomberman::Game::Map gameMap("./map/map2.txt");
//    std::map<enum PlayerID, Bomberman::Game::Player> listPlayer = {
//            {PLAYER_1, Bomberman::Game::Player(&gameMap, PLAYER1_INDEX)},
//            {PLAYER_2, Bomberman::Game::Player(&gameMap, PLAYER2_INDEX)},
//            {PLAYER_3, Bomberman::Game::Player(&gameMap, PLAYER3_INDEX)},
//            {PLAYER_4, Bomberman::Game::Player(&gameMap, PLAYER4_INDEX)}
//    };
    std::map<enum PlayerID, Bomberman::Graphics::Player> listPlayer = {
            {PLAYER_1, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::STAND, {1, 1}, PLAYER1_INDEX)},
            {PLAYER_2, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::STAND, {9, 1}, PLAYER2_INDEX)},
            {PLAYER_3, Bomberman::Graphics::Player(Bomberman::RIGHT, Bomberman::STAND, {1, 9}, PLAYER3_INDEX)},
            {PLAYER_4, Bomberman::Graphics::Player(Bomberman::RIGHT, Bomberman::STAND, {9, 9}, PLAYER4_INDEX)}
    };
    std::map<enum PlayerID, Bomberman::Graphics::Player> listPlayer2 = {
            {PLAYER_1, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::RUNNING, {1, 1}, PLAYER1_INDEX)},
            {PLAYER_2, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::RUNNING, {9, 1}, PLAYER2_INDEX)},
            {PLAYER_3, Bomberman::Graphics::Player(Bomberman::LEFT, Bomberman::RUNNING, {2, 9}, PLAYER3_INDEX)},
            {PLAYER_4, Bomberman::Graphics::Player(Bomberman::LEFT, Bomberman::RUNNING, {9, 9}, PLAYER4_INDEX)}
    };
    std::map<enum PlayerID, Bomberman::Graphics::Player> listPlayer3 = {
            {PLAYER_1, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::PUT_THE_BOMB, {1, 1}, PLAYER1_INDEX)},
            {PLAYER_2, Bomberman::Graphics::Player(Bomberman::UP, Bomberman::PUT_THE_BOMB, {9, 1}, PLAYER2_INDEX)},
            {PLAYER_3, Bomberman::Graphics::Player(Bomberman::DOWN, Bomberman::PUT_THE_BOMB, {2, 8}, PLAYER3_INDEX)},
            {PLAYER_4, Bomberman::Graphics::Player(Bomberman::DOWN, Bomberman::PUT_THE_BOMB, {9, 9}, PLAYER4_INDEX)}
    };
    if (device == NULL)
        return (84);
//    Bomberman::Graphics::GameGraphic gr(device, receiver, map, listPlayer, std::map<PlayerIndex, std::map<enum Event, int>>{});
    Bomberman::Graphics::GameGraphic gr(device, receiver, map, listPlayer, mapKeyPlayer);
    int i = 0;
    while (gr.isRunning()) {
        if (i % 150 > 50 && i % 150 < 101)
            gr.loop(map, listPlayer2);
        else if (i % 150 > 100 && i % 150 < 151)
            gr.loop(map, listPlayer3);
        else
            gr.loop(map, listPlayer);
        gr.getEvent();
        i++;
    }
    return (0);

}
