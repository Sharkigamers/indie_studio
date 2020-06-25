/*
** EPITECH PROJECT, 2020
** Map
** File description:
** IndieStudio
*/

#include <cmath>
#include <algorithm>

#include "Map.hpp"
#include "Player.hpp"

Bomberman::Game::Map::Map(const std::string path, std::string fileContent)
{
    if (path == "")
        _map = initializeMap(fileContent);
    else
        _map = initializeMap(getFileContent(path));
    _playerAliveMap[PLAYER1_INDEX] = true;
    _playerAliveMap[PLAYER2_INDEX] = true;
    _playerAliveMap[PLAYER3_INDEX] = true;
    _playerAliveMap[PLAYER4_INDEX] = true;
}

Bomberman::Game::Map::~Map()
{
}

std::string Bomberman::Game::Map::getFileContent(const std::string path)
{
    std::string mapCharged = "";
    std::ifstream mapContent;
    std::string line;

    mapContent.open(path);
    if (!mapContent) {
        std::cerr << "Error: Can't open map: " << path << std::endl;
        exit(84);
    }
    while (getline(mapContent, line))
        mapCharged += line + "\n";
    return mapCharged;
}

std::map<std::pair<float, float>, Element>
Bomberman::Game::Map::initializeMap(std::string mapCharged)
{
    int i = 0;
    int j = 0;
    std::pair<int, int> elementPosition;
    Element elementFromMap;
    std::map<std::pair<float, float>, Element> map;
    char c;

    for (char &character: mapCharged) {
        if (character != '\n') {
            elementPosition = std::make_pair(i, j);
            elementFromMap.obj = static_cast<Object>(character);
            elementFromMap.animation = 0;
            map.insert({elementPosition, elementFromMap});
            ++j;
        } else {
            elementPosition = std::make_pair(i, j + 1);
            elementFromMap.obj = static_cast<Object>(character);
            elementFromMap.animation = 0;
            map.insert({elementPosition, elementFromMap});
            ++i;
            j = 0;
        }
    }
    return map;
}

void Bomberman::Game::Map::pushBomb(const Bomberman::Game::Bomb &bomb)
{
    _listBomb.push_back(bomb);
}

void Bomberman::Game::Map::destroyBox(const Bomberman::Game::Bomb &bomb)
{
    if ((std::rand() % 100) < 35) {
        switch (std::rand() % 4) {
            case 0:
                bomb.getPlayer()->incrementBombCount();
                break;
            case 1:
                bomb.getPlayer()->incrementFire();
                break;
            case 2:
                bomb.getPlayer()->incrementSpeed();
                break;
            case 3:
                bomb.getPlayer()->setWallPass();
                break;
            default:
                break;
        }
    }
}

void Bomberman::Game::Map::handleBombTrail(const std::vector<std::pair<float, float> > &listPosition, const Bomberman::Game::Bomb &bomb)
{
    bool encounteredWall = false;

    for (const auto &x : listPosition) {
        switch (_map[x].obj) {
            case BOX:
                _map[x].obj = GROUND;
                destroyBox(bomb);
                bomb.getPlayer()->addScore(BOX_DESTROY_SCORE);
                break;
            case PLAYER1:
                _map[x].obj = GROUND;
                _playerAliveMap[PLAYER1_INDEX] = false;
                if (bomb.getPlayer()->getPlayerIndex() != static_cast<enum PlayerIndex>(PLAYER1))
                    bomb.getPlayer()->addScore(PLAYER_DESTROY_SCORE);
                break;
            case PLAYER2:
                _map[x].obj = GROUND;
                _playerAliveMap[PLAYER2_INDEX] = false;
                if (bomb.getPlayer()->getPlayerIndex() != static_cast<enum PlayerIndex>(PLAYER2))
                    bomb.getPlayer()->addScore(PLAYER_DESTROY_SCORE);
                break;
            case PLAYER3:
                _map[x].obj = GROUND;
                _playerAliveMap[PLAYER3_INDEX] = false;
                if (bomb.getPlayer()->getPlayerIndex() != static_cast<enum PlayerIndex>(PLAYER3))
                    bomb.getPlayer()->addScore(PLAYER_DESTROY_SCORE);
                break;
            case PLAYER4:
                _map[x].obj = GROUND;
                _playerAliveMap[PLAYER4_INDEX] = false;
                if (bomb.getPlayer()->getPlayerIndex() != static_cast<enum PlayerIndex>(PLAYER4))
                    bomb.getPlayer()->addScore(PLAYER_DESTROY_SCORE);
                break;
            case BOMB:
                std::find(_listBomb.begin(), _listBomb.end(), x)->setActive(false);
                break;
            case WALL:
                encounteredWall = true;
                break;
            default:
                break;
        }
        if (encounteredWall == true)
            break;
    }
}

void Bomberman::Game::Map::handleBombExplosion(const Bomberman::Game::Bomb &bomb, Bomberman::Game::Player *player)
{
    Bomberman::Game::FireCluster::ListPosition explosionPositions = Bomberman::Game::FireCluster::createListPosition(bomb.getPosition(), bomb.getPlayer()->getCurrentPowerUps().getFirePower());

    handleBombTrail(std::get<0>(explosionPositions), bomb);
    handleBombTrail(std::get<1>(explosionPositions), bomb);
    handleBombTrail(std::get<2>(explosionPositions), bomb);
    handleBombTrail(std::get<3>(explosionPositions), bomb);

    _map[bomb.getPosition()].obj = GROUND;

    if (std::get<4>(explosionPositions) == player->getPosition())
        player->setAlive(false);

    _listFireClusters.push_back(Bomberman::Game::FireCluster(bomb.getPosition(), bomb.getPlayer()->getCurrentPowerUps().getFirePower(), *this));
    addFireClusterInMap(_listFireClusters.back());
    player->decBombCount();
}

void Bomberman::Game::Map::updatePlayerPositions(std::vector<Bomberman::Game::Player> &players)
{
    std::pair<std::pair<int, int>, std::pair<int, int>> tmpPosition;

    for (auto &x : players) {
        if (x.getStatus() == PUT_THE_BOMB && x.getPlayerBombClock().getEllapsedTime() > 500)
            x.setStatus(STAND);
    }

    for (auto &x : players) {
        tmpPosition = x.getRealPosition();
        std::pair<std::pair<int, int>, std::pair<int, int>> newPosition = tmpPosition;
        
        if (x.getStatus() == RUNNING) {
            if (x.getPlayerClock().getEllapsedTime() > 75) {
                switch (x.getOrientation()) {
                    case Bomberman::UP:
                        newPosition.first.second -= (1 * x.getCurrentPowerUps().getSpeed());
                        if (newPosition.first.second <= -10) {
                            newPosition.first.first -= 1;
                            newPosition.first.second = 0;
                            x.setStatus(STAND);
                        }
                        break;
                    case Bomberman::DOWN:
                        newPosition.first.second += (1 * x.getCurrentPowerUps().getSpeed());
                        if (newPosition.first.second >= 10) {
                            newPosition.first.first += 1;
                            newPosition.first.second = 0;
                            x.setStatus(STAND);
                        }
                        break;
                    case Bomberman::LEFT:
                        newPosition.second.second -= (1 * x.getCurrentPowerUps().getSpeed());
                        if (newPosition.second.second <= -10) {
                            newPosition.second.first -= 1;
                            newPosition.second.second = 0;
                            x.setStatus(STAND);
                        }
                        break;
                    case Bomberman::RIGHT:
                        newPosition.second.second += (1 * x.getCurrentPowerUps().getSpeed());
                        if (newPosition.second.second >= 10) {
                            newPosition.second.first += 1;
                            newPosition.second.second = 0;
                            x.setStatus(STAND);
                        }
                        break;
                    default:
                        break;
                }
            x.getPlayerClock().reset();
            x.setPosition(newPosition);
            }
        }
    }
}

void Bomberman::Game::Map::checkBombsTiming(std::vector<Bomberman::Game::Player> &players)
{
    std::vector<Bomberman::Game::Bomb> tmp = _listBomb;

    for (auto &x : tmp) {
        x.updateTime();
        if (x.getActive() == false) {
            Bomberman::Game::Player *owner;
            for (auto &y : players) {
                if (y.getPlayerIndex() == x.getPlayer()->getPlayerIndex()) {
                    owner = &y;
                    break;
                }
            }
            handleBombExplosion(x, owner);
            _listBomb.erase(std::find(_listBomb.begin(), _listBomb.end(), x));
        }
    }
}

void Bomberman::Game::Map::createFireCluster(const Bomberman::Game::Bomb &bomb)
{
    _listFireClusters.push_back(Bomberman::Game::FireCluster(bomb.getPosition(), static_cast<int>(bomb.getPlayer()->getCurrentPowerUps().getFirePower()), *this));
}

void Bomberman::Game::Map::addFireClusterInMap(const Bomberman::Game::FireCluster &cluster)
{
    Bomberman::Game::FireCluster::ListPosition explosionPositions = cluster.getListPosition();

    for (const auto &x : std::get<0>(explosionPositions)) {
        if (_map[x].obj == GROUND || _map[x].obj == BOMB)
            _map[x].obj = EXPLOSION;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<1>(explosionPositions)) {
        if (_map[x].obj == GROUND || _map[x].obj == BOMB)
            _map[x].obj = EXPLOSION;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<2>(explosionPositions)) {
        if (_map[x].obj == GROUND || _map[x].obj == BOMB)
            _map[x].obj = EXPLOSION;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<3>(explosionPositions)) {
        if (_map[x].obj == GROUND || _map[x].obj == BOMB)
            _map[x].obj = EXPLOSION;
        if (_map[x].obj == WALL)
            break;
    }
    if (_map[std::get<4>(explosionPositions)].obj == BOMB ||
    _map[std::get<4>(explosionPositions)].obj == GROUND)
        _map[std::get<4>(explosionPositions)].obj = EXPLOSION;
}

void Bomberman::Game::Map::removeFireClusterFromMap(const Bomberman::Game::FireCluster &cluster)
{
    Bomberman::Game::FireCluster::ListPosition explosionPositions = cluster.getListPosition();

    for (const auto &x : std::get<0>(explosionPositions)) {
        if (_map[x].obj == EXPLOSION)
            _map[x].obj = GROUND;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<1>(explosionPositions)) {
        if (_map[x].obj == EXPLOSION)
            _map[x].obj = GROUND;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<2>(explosionPositions)) {
        if (_map[x].obj == EXPLOSION)
            _map[x].obj = GROUND;
        if (_map[x].obj == WALL)
            break;
    }

    for (const auto &x : std::get<3>(explosionPositions)) {
        if (_map[x].obj == EXPLOSION)
            _map[x].obj = GROUND;
        if (_map[x].obj == WALL)
            break;
    }
    if (_map[std::get<4>(explosionPositions)].obj == EXPLOSION)
        _map[std::get<4>(explosionPositions)].obj = GROUND;
}

void Bomberman::Game::Map::updateFireClusters()
{
    std::vector<Bomberman::Game::FireCluster> tmp = _listFireClusters;

    for (auto &x : tmp) {
        x.updateCluster();
        if (x.getActive() == false) {
            removeFireClusterFromMap(x);
            _listFireClusters.erase(std::find(_listFireClusters.begin(), _listFireClusters.end(), x));
        }
    }
}

void Bomberman::Game::Map::updateAll(std::vector<Bomberman::Game::Player> &players)
{
    updatePlayerPositions(players);
    checkBombsTiming(players);
    updateFireClusters();
}
