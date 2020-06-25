/*
** EPITECH PROJECT, 2020
** Game
** File description:
** IndieStudio
*/

#include "GameClass.hpp"

#include <tuple>

Bomberman::Game::GameClass::GameClass(const std::vector<PlayerIndex> &IAS, int musicId, const std::string mapPath)
: _map(Map(mapPath))
{
    std::vector<PlayerIndex> all = {PLAYER1_INDEX, PLAYER2_INDEX, PLAYER3_INDEX, PLAYER4_INDEX};
    for (const auto &x : IAS) {
        pushIA(x);
        all.erase(std::find(all.begin(), all.end(), x));
    }
    for (const auto &x : all)
        pushPlayer(x);
}

Bomberman::Game::GameClass::GameClass(const std::string &gameFilePath)
{
    Bomberman::Game::Saver gameSave;

    gameSave.load(gameFilePath);
    _map = Map("", gameSave.getMap());
    for (const auto &x : gameSave.getCharacter()) {
        if (std::get<0>(x.second).compare("ai") == 0) {
            pushIA(static_cast<PlayerIndex>(x.first));
            _players.back().getCurrentPowerUps().setFire(std::get<2>(x.second)[0]);
            _players.back().getCurrentPowerUps().setBombCount(std::get<2>(x.second)[1]);
            _players.back().getCurrentPowerUps().setSpeed(std::get<2>(x.second)[2]);
            _players.back().getCurrentPowerUps().setWallPass(static_cast<bool>(std::get<2>(x.second)[3]));
            _players.back().addScore(std::get<3>(x.second));
        } else {
            pushPlayer(static_cast<PlayerIndex>(x.first), std::get<0>(x.second));
            _players.back().getCurrentPowerUps().setBombCount(std::get<2>(x.second)[1]);
            _players.back().getCurrentPowerUps().setSpeed(std::get<2>(x.second)[2]);
            _players.back().getCurrentPowerUps().setWallPass(static_cast<bool>(std::get<2>(x.second)[3]));
            _players.back().addScore(std::get<3>(x.second));
        }
    }
}

Bomberman::Game::GameClass::~GameClass()
{
}

void Bomberman::Game::GameClass::pushPlayer(PlayerIndex playerIndex, const std::string name)
{
    for (int i = 0;; i++) {
        bool available = true;
        for (const auto &x : _players) {
            if (i == 0) {
                if (x.getName() == static_cast<std::string>(name))
                    available = false;
            } else {
                if (x.getName() == static_cast<std::string>(name + std::to_string(i)))
                    available = false;
            }
        }
        if (available == true) {
            if (i == 0)
                _players.push_back(Bomberman::Game::Player(_map, playerIndex, false, name));
            else
                _players.push_back(Bomberman::Game::Player(_map, playerIndex, false, name + std::to_string(i)));
            break;
        }
    }
}

void Bomberman::Game::GameClass::pushIA(PlayerIndex playerIndex)
{
    for (int i = 1;; i++) {
        bool available = true;
        for (const auto &x : _players) {
            if (x.getName() == static_cast<std::string>("ai_" + std::to_string(i)))
                available = false;
        }
        if (available == true) {
            _players.push_back(Bomberman::Game::Player(_map, playerIndex, true, "ai_" + std::to_string(i)));
            break;
        }
    }
}

std::map<PlayerIndex, Bomberman::Game::Player &> Bomberman::Game::GameClass::getPlayers()
{
    std::map<PlayerIndex, Bomberman::Game::Player &> players;

    for (auto &x : _players) {
        players.insert({x.getPlayerIndex(), x});
    }
    return players;
}

int Bomberman::Game::GameClass::input(const std::map<PlayerIndex, std::vector<enum Event>> &inputs)
{
    for (const auto &x : inputs) {
        for (const auto &events : x.second) {
            if (std::find(_players.begin(), _players.end(), x.first)->isAlive() == true)
                std::find(_players.begin(), _players.end(), x.first)->applyEvent(events, getObjMap());
        }
    }
    return 0;
}

void Bomberman::Game::GameClass::updateGameState()
{
    for (auto &x : _players)
        x.updateMap(_map);
    updateAi();
    _map.updateAll(_players);
    for (const auto &x : _map.getAlivePlayerMap())
        std::find(_players.begin(), _players.end(), x.first)->setAlive(x.second);
}

bool Bomberman::Game::GameClass::isGameOver() const
{
    uint16_t aliveCount = 0;

    for (const auto &x : _players)
        aliveCount += (x.isAlive() == true ? 1 : 0);
    if (aliveCount <= 1)
        return true;
    return false;
}

std::map<std::string, int> Bomberman::Game::GameClass::getFinalScore() const
{
    std::map<std::string, int> resultMap;

    for (const auto &x : _players)
        resultMap["Player" + std::to_string(x.getPlayerIndex() - '0')] = x.getScore();
    return resultMap;
}

void Bomberman::Game::GameClass::updateAi()
{
    short x;
    short y;
    std::pair<float, float> pos;

    for (auto &player: _players) {
        if (player.isAlive() == false)
            continue;
        if (player.isIA() && player.getStatus() == STAND) {
            player.actionAi(_map);
        }
    }
    for (auto &player: _players) {
        if (player.isAlive() == false)
            continue;
        x = (short)player.getPosition().second;
        y = (short)player.getPosition().first;
        pos = std::make_pair(y, x);
        if (_map.getMap()[pos].obj == BOX) {
            if (player.getOrientation() == UP)
                player.movePlayer(_map, -1, 0);
            else if (player.getOrientation() == DOWN)
                player.movePlayer(_map, 1, 0);
            else if (player.getOrientation() == RIGHT)
                player.movePlayer(_map, 0, 1);
            else if (player.getOrientation() == LEFT)
                player.movePlayer(_map, 0, -1);
        }
    }
}

// int main()
// {
//     std::vector<PlayerIndex> playerVector;
//     playerVector.push_back(PLAYER1_INDEX);
//     playerVector.push_back(PLAYER2_INDEX);
//     Bomberman::GameClock aya;
//     auto m = Bomberman::Game::MapCreation(13, 11);
//     static const std::string path = "../../assets/map/";
//     m.createMap(path + "map.map");
//     auto game = Bomberman::Game::GameClass(playerVector, 1, path + "map.map");
//     Bomberman::Game::Player p3(game.getObjMap(), PLAYER3_INDEX, false);
//     Bomberman::Game::Player p4(game.getObjMap(), PLAYER4_INDEX, false);
//     float caca = 0;
//     std::map<PlayerIndex, std::vector<enum Event>> in = {
//         {PLAYER3_INDEX, {ACTION_ACTION}}
//     };
//     std::map<PlayerIndex, std::vector<enum Event>> after = {
//         {PLAYER3_INDEX, {ACTION_UP}}
//     };
//     std::map<PlayerIndex, std::vector<enum Event>> after2 = {
//         {PLAYER3_INDEX, {ACTION_UP}}
//     };

//     bool lopes = false;
//     bool lopes2 = false;

//     while (aya.getEllapsedTime() < 20000) {
//         if (lopes == false) {
//             game.input(in);
//             lopes = true;
//         }
//         if (aya.getEllapsedTime() > 3000 && lopes2 == false) {
//             printf("After");
//             game.input(after);
//             lopes2 = true;
//         }
//         game.updateGameState();
//         for (auto map : game.getMap()) {
//             printf("%c", map.second.obj);
//         }
//         // p1.applyEvent(ACTION_RIGHT, game.getObjMap());
//         // p2.applyEvent(ACTION_DOWN, game.getObjMap());
//         // p3.applyEvent(ACTION_UP, game.getObjMap());
//         // p4.applyEvent(ACTION_LEFT, game.getObjMap());
//         // p1.applyEvent(ACTION_ACTION, game.getObjMap());
//         // p2.applyEvent(ACTION_ACTION, game.getObjMap());
//         // p3.applyEvent(ACTION_ACTION, game.getObjMap());
//         // p4.applyEvent(ACTION_ACTION, game.getObjMap());
//         // p1.applyEvent(DOWN, game.getObjMap());
//         // system("clear");
//     }
// }
