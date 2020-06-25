#include "Core.hpp"
#include "Menu.hpp"
#include <stdlib.h>
Bomberman::
Core::Core() {}


void
Bomberman::
Core::generalLoop(irr::IrrlichtDevice *device, Bomberman::Graphics::EventReceiver &receiver)
{
    while (status != QUIT && device->run()) {
        if (status == MENU)
            status = menuLoop(device, receiver);
        if (status == GAME) {
            device->setEventReceiver(&receiver);
            status = gameLoop(device, receiver, _keyBinding, _playerIA, 0, _volume);
        }
        if (status == LOAD_GAME) {
            device->setEventReceiver(&receiver);
            status = loadedGameLoop(device, receiver, _keyBinding, _playerIA, _filePath);
        }
    }
}

status_t 
Bomberman::
Core::menuLoop(irr::IrrlichtDevice * device, Bomberman::Graphics::EventReceiver &receiver)
{
    MyMenu bomb;
    bomb.menu(device);
    _playerIA = bomb.getPlayers();
    // _playerIA = {PLAYER2_INDEX};

    _keyBinding = bomb.getMapkeyPlayer();
    state_t state = bomb.getState();
    _volume = bomb.getSoundLevel();

    if (state == PLAY) {
        return (GAME);
    }
    else if (state == LOAD) {
        std::wstring w = bomb.getFileName();
        for (auto &e : w) {
            char c;
            wctomb(&c, e);
            _filePath += c;
        }
        // std::cout << "filepath" << _filePath << std::endl;
        return (LOAD_GAME);
    }
    return (QUIT);
}

status_t 
Bomberman::
Core::gameLoop(
    irr::IrrlichtDevice *device, 
    Graphics::EventReceiver &receiver, 
    std::map<PlayerIndex, 
    std::map<enum Event, int>> mapKeyPlayer,
    std::vector<enum PlayerIndex> playerIA, 
    int mapId, float volume
)
{
    auto m = Bomberman::Game::MapCreation(13, 11);
    const std::string path = "./assets/map/";
    m.createMap(path + "map.map");

    Bomberman::Game::GameClass game(playerIA, 0, path + "map.map");
    Bomberman::Graphics::GameGraphic disp(device,
    receiver, game.getMap(),
    game.getPlayers(), mapKeyPlayer, volume);

    while (disp.isRunning() && game.isGameOver() == false) {
        std::map<enum PlayerIndex, std::vector<enum Event>> events = disp.getEvent();
        game.input(events);
        game.updateGameState();

        std::map<PlayerIndex, Bomberman::Game::Player &> players = game.getPlayers();
        std::map<std::pair<float, float>, Element> map = game.getMap();

        if (disp.getAction() == Graphics::MenuPauseStatus::SAVE_ID) {
            std::cout << "save"<< std::endl;
            game.saveGame(map, players);
        }
        disp.loop(map, players);
    }
    if (game.isGameOver())
        while (disp.isRunning() && disp.displayEndScore(game.getFinalScore()) == 0);
    std::cout << "quit game" << std::endl;
    enum Graphics::MenuPauseStatus ret = disp.getAction();
    if (ret == Graphics::MenuPauseStatus::QUIT_ID) {
        return (QUIT);
    }
    return (MENU);
}

status_t 
Bomberman::
Core::loadedGameLoop(
    irr::IrrlichtDevice *device, 
    Graphics::EventReceiver &receiver, 
    std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer,
    std::vector<enum PlayerIndex> playerIA,
    const std::string &path
)
{
    Game::GameClass game(path);

    Bomberman::Graphics::GameGraphic disp(device,
    receiver, game.getMap(),
    game.getPlayers(), mapKeyPlayer, _volume);

    for (const auto &x : mapKeyPlayer) {
        for (const auto &y : x.second) {
            std::cerr << "Map : " << x.first << " : " << y.first << " " << y.second << std::endl;
        }
    }

    while (disp.isRunning()) {
        std::map<enum PlayerIndex, std::vector<enum Event>> events = disp.getEvent();
        game.input(events);
        game.updateGameState();

        std::map<PlayerIndex, Bomberman::Game::Player &> players = game.getPlayers();
        std::map<std::pair<float, float>, Element> map = game.getMap();

        if (disp.getAction() == Graphics::MenuPauseStatus::SAVE_ID) {
            std::cout << "save"<< std::endl;
            game.saveGame(map, players);
        }
        disp.loop(map, players);
    }
    std::cout << "quit game" << std::endl;
    enum Graphics::MenuPauseStatus ret = disp.getAction();
    if (ret == Graphics::MenuPauseStatus::QUIT_ID) {
        return (QUIT);
    }
    return (MENU);
}
