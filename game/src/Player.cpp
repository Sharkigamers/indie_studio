/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include <unistd.h>
#include <tuple>
#include <cmath>
#include <algorithm>

#include "Player.hpp"

Bomberman::Game::Player::Player(Bomberman::Game::Map &map, enum PlayerIndex index, bool isIA, const std::string name)
: _map(std::make_shared<Bomberman::Game::Map>(map)), _playerStatus(Bomberman::STAND), _playerOrientation(Bomberman::DOWN), _playerIndex(index), _isIA(isIA), 
_currentPowerUps(Bomberman::Game::PowerUps()), _name(name), _playerClock(Bomberman::GameClock()), _playerPutBombClock(Bomberman::GameClock())
{
    char playerIndex = getPlayerIndex();
    std::pair<std::pair<int, int>, std::pair<int, int>> pos;

    for (const auto &elem: _map->getMap()) {
        if (elem.second.obj == playerIndex) {
            pos = {{elem.first.first, 0}, {elem.first.second, 0}};
            setPosition(pos);
            break;
        }
    }
}

Bomberman::Game::Player::~Player()
{
}

std::tuple<std::pair<int, int>, char, float> Bomberman::Game::Player::findRange(
std::pair<int, int> currentPlacement, std::vector<std::vector<char>> &myMap,
std::tuple<std::pair<int, int>, char, float> bestPlacement)
{
    std::pair<int, int> position;
    std::tuple<std::pair<int, int>, char, float> currentBestPlacement = std::make_tuple(position, 0, -1);
    float range = 0;
    int i = 0;
    int j = 0;

    for (auto &line: myMap) {
        for (auto &character: line) {
            if (character != getPlayerIndex() && (character == '1' || character == '2' ||
            character == '3' || character == '4')) {
                position = std::make_pair(i, j);
                range = abs(i - currentPlacement.first) + abs(j - currentPlacement.second);
                if (std::get<2>(currentBestPlacement) == -1 || std::get<2>(currentBestPlacement) > range)
                    currentBestPlacement = std::make_tuple(currentPlacement, character, range);
            }
            ++j;
        }
        j = 0;
        ++i;
    }
    if (std::get<2>(bestPlacement) == -1 || std::get<2>(bestPlacement) > std::get<2>(currentBestPlacement)) {
        if (std::get<2>(bestPlacement) != -1)
            myMap[std::get<0>(bestPlacement).first][std::get<0>(bestPlacement).second] = GROUND;
        return currentBestPlacement;
    }
    myMap[currentPlacement.first][currentPlacement.second] = GROUND;
    return bestPlacement;
}

void Bomberman::Game::Player::wichKeepBombPlacement(std::vector<std::vector<char>> &myMap)
{
    std::pair<int, int> currentPlacement = std::make_pair(-1, -1);
    std::tuple<std::pair<int, int>, char, float> bestPlacement = std::make_tuple(currentPlacement, 0, -1);
    float range;
    int i = 0;
    int j = 0;

    for (auto &line: myMap) {
        for (auto &character: line) {
            if (character == AIBOMBPLACEMENT) {
                currentPlacement = std::make_pair(i, j);
                range = std::get<2>(bestPlacement);
                bestPlacement = findRange(currentPlacement, myMap, bestPlacement);
            } else if (character == AIFREEPATH)
                character = GROUND;
            ++j;
        }
        j = 0;
        ++i;
    }
}

std::vector<std::vector<char>> Bomberman::Game::Player::copyMap()
{
    std::vector<char> line;
    std::vector<std::vector<char>> map;

    for (auto element: _map->getMap()) {
        if (element.second.obj == '\n') {
            map.push_back(line);
            line.clear();
        } else
            line.push_back(element.second.obj);
    }
    return map;
}

bool Bomberman::Game::Player::backOnWalked(std::vector<std::vector<char>> &myMap,
short &x, short &y, std::vector<std::pair<char, short>> &action, bool specificWalk)
{
    if (myMap[y][x + 1] == BOX || myMap[y][x - 1] == BOX ||
    myMap[y + 1][x] == BOX || myMap[y - 1][x] == BOX) {
        if (specificWalk)
            myMap[y][x] = AIFREEPATH;
        else
            myMap[y][x] = AIBOMBPLACEMENT;
    }
    else if (myMap[y][x] == getPlayerIndex() && myMap[y][x + 1] != GROUND &&
    myMap[y][x - 1] != GROUND && myMap[y + 1][x] != GROUND && myMap[y - 1][x] != GROUND)
        return false;
    else
        myMap[y][x] = AIFREEPATH;
    if (!action.empty()) {
        if (action.back().first == 'x') {
            x += action.back().second * -1;
            action.pop_back();
        }
        else {
            y += action.back().second * -1;
            action.pop_back();
        }
        return true;
    }
    return false;
}

bool Bomberman::Game::Player::walkablePath(std::vector<std::vector<char>> &myMap,
short &x, short &y, std::vector<std::pair<char, short>> &action, bool specificWalk)
{
    std::pair<char, short> currentAction;

    if (myMap[y][x + 1] == GROUND) {
        myMap[y][x + 1] = AIPATH;
        x += 1;
        currentAction = std::make_pair('x', 1);
        action.push_back(currentAction);
    } else if (x > 0 && myMap[y][x - 1] == GROUND) {
        myMap[y][x - 1] = AIPATH;
        x -= 1;
        currentAction = std::make_pair('x', -1);
        action.push_back(currentAction);
    } else if (myMap[y + 1][x] == GROUND) {
        myMap[y + 1][x] = AIPATH;
        y += 1;
        currentAction = std::make_pair('y', 1);
        action.push_back(currentAction);
    } else if (y > 0 && myMap[y - 1][x] == GROUND) {
        myMap[y - 1][x] = AIPATH;
        y -= 1;
        currentAction = std::make_pair('y', -1);
        action.push_back(currentAction);
    } else
        return backOnWalked(myMap, x, y, action, specificWalk);
    return true;
}

void Bomberman::Game::Player::drawWalkablePath()
{
    short x = (short)getPosition().second;
    short y = (short)getPosition().first;
    std::vector<std::pair<char, short>> action;
    int i = 0;
    int j = 0;
    std::pair<float, float> casePosition;

    while (1) {
        if (_aiMap[y - 1][x] == AIBOMBPLACEMENT || _aiMap[y + 1][x] == AIBOMBPLACEMENT ||
        _aiMap[y][x - 1] == AIBOMBPLACEMENT || _aiMap[y][x + 1] == AIBOMBPLACEMENT)
            break;
        if (!walkablePath(_aiMap, x, y, action, true))
            break;
        ++i;
    }
    i = 0;
    for (auto &line: _aiMap) {
        for (auto &character: line) {
            if (character == AIPATH) {
                casePosition = std::make_pair(i, j);
                _walkPositions.push_back(casePosition);
            }
            ++j;
        }
        j = 0;
        ++i;
    }
    i = 0;
    j = 0;
    for (auto &line: _aiMap) {
        for (auto &character: line) {
            if (character == AIFREEPATH)
                character = GROUND;
            if (character == AIBOMBPLACEMENT) {
                casePosition = std::make_pair(i, j);
                _walkPositions.push_back(casePosition);
            }
            j++;
        }
        j = 0;
        ++i;
    }
}

void Bomberman::Game::Player::findBestPath(std::vector<std::vector<char>> myMap)
{
    short x = (short)getPosition().second;
    short y = (short)getPosition().first;
    std::vector<std::pair<char, short>> action;

    while (1) {
        if (!walkablePath(myMap, x, y, action, false))
            break;
    }
    wichKeepBombPlacement(myMap);
    action.clear();
    _aiMap = myMap;
    drawWalkablePath();
}

enum Event Bomberman::Game::Player::chooseDirectionOfAi()
{
    enum Event action = ACTION_STAND;
    short x = (short)getPosition().second;
    short y = (short)getPosition().first;

    if (_aiMap[y][x + 1] == AIPATH || _aiMap[y][x + 1] == AIBOMBPLACEMENT || _aiMap[y][x + 1] == AIRUNOUT) {
        action = ACTION_RIGHT;
    }
    else if (_aiMap[y][x - 1] == AIPATH || _aiMap[y][x - 1] == AIBOMBPLACEMENT || _aiMap[y][x - 1] == AIRUNOUT)
        action = ACTION_LEFT;
    else if (_aiMap[y + 1][x] == AIPATH || _aiMap[y + 1][x] == AIBOMBPLACEMENT || _aiMap[y + 1][x] == AIRUNOUT)
        action = ACTION_DOWN;
    else if (_aiMap[y - 1][x] == AIPATH || _aiMap[y - 1][x] == AIBOMBPLACEMENT || _aiMap[y - 1][x] == AIRUNOUT)
        action = ACTION_UP;
    if (_aiMap[y][x + 1] == AIBOMBPLACEMENT || _aiMap[y][x - 1] == AIBOMBPLACEMENT ||
    _aiMap[y + 1][x] == AIBOMBPLACEMENT || _aiMap[y - 1][x] == AIBOMBPLACEMENT)
        _isOnPlacementBomb = true;
    if (!_walkPositions.empty())
        _walkPositions.erase(_walkPositions.end());
    return action;
}

void Bomberman::Game::Player::putExplosionRange(short bombX, short bombY, uint16_t range,
short x, short y, std::vector<std::vector<char>> &myMap)
{
    bool foundSave = false;
    std::pair<float, float> aiPath;

    for (short i = 0; i < range; ++i) {
        bombX += x;
        bombY += y;
        if (myMap[bombY][bombX] != WALL && myMap[bombY][bombX] != BOX && myMap[bombY][bombX] != BOMB &&
        myMap[bombY][bombX] != '1' && myMap[bombY][bombX] != '2' &&
        myMap[bombY][bombX] != '3' && myMap[bombY][bombX] != '4')
            myMap[bombY][bombX] = EXPLOSIONRANGE;
        else
            break;
        if (myMap[bombY][bombX + 1] == GROUND) {
            myMap[bombY][bombX + 1] = AIRUNOUT;
            foundSave = true;
            aiPath = std::make_pair(bombY, bombX + 1);
            _onSafe.push_back(aiPath);
        }
        if (myMap[bombY][bombX - 1] == GROUND) {
            myMap[bombY][bombX - 1] = AIRUNOUT;
            foundSave = true;
            aiPath = std::make_pair(bombY, bombX - 1);
            _onSafe.push_back(aiPath);
        }
        if (myMap[bombY + 1][bombX] == GROUND) {
            myMap[bombY + 1][bombX] = AIRUNOUT;
            foundSave = true;
            aiPath = std::make_pair(bombY + 1, bombX);
            _onSafe.push_back(aiPath);
        }
        if (myMap[bombY - 1][bombX] == GROUND) {
            myMap[bombY - 1][bombX] = AIRUNOUT;
            foundSave = true;
            aiPath = std::make_pair(bombY - 1, bombX);
            _onSafe.push_back(aiPath);
        }
        if (foundSave) {
            for (; i >= 0; --i) {
                aiPath = std::make_pair(bombY, bombX);
                _walkSafe.push_back(aiPath);
                myMap[bombY][bombX] = AIPATH;
                bombX += x * -1;
                bombY += y * -1;
            }
            break;
        }
    }
}

void Bomberman::Game::Player::runOutOfBomb(Bomberman::Game::Map &map)
{
    std::vector<std::vector<char>> myMap = copyMap();
    short charaX = (short)getPosition().second;
    short charaY = (short)getPosition().first;
    short bombX;
    short bombY;
    uint16_t range = 0;

    if (_onSafe.empty()) {
        for (auto &bomb: _map->getListBomb()) {
            short bombX = (short)bomb.getPosition().second;
            short bombY = (short)bomb.getPosition().first;
            range = _currentPowerUps.getFirePower();
            putExplosionRange(bombX, bombY, range, 1, 0, myMap);
            putExplosionRange(bombX, bombY, range, -1, 0, myMap);
            putExplosionRange(bombX, bombY, range, 0, 1, myMap);
            putExplosionRange(bombX, bombY, range, 0, -1, myMap);
        }
    } else {
        for (auto &elem: _walkSafe)
            myMap[elem.first][elem.second] = AIPATH;
        for (auto &elem: _onSafe) {
            if (getPosition() != elem)
                myMap[elem.first][elem.second] = AIRUNOUT;
            else
                _isOnSafe = true;
        }
    }
    if (!_isOnSafe)
        applyEvent(chooseDirectionOfAi(), map);
    _aiMap = myMap;
}

enum Event Bomberman::Game::Player::moveAi()
{
    int i = 0;
    int j = 0;
    short x = (short)getPosition().second;
    short y = (short)getPosition().first;
    bool isBombPlacement = false;

    _aiMap = copyMap();
    if (!_walkPositions.empty()) {
        for (const auto &walk: _walkPositions) {
            if (_aiMap[walk.first][walk.second] == GROUND)
                _aiMap[walk.first][walk.second] = AIPATH;
        }
        _aiMap[_walkPositions.back().first][_walkPositions.back().second] = AIBOMBPLACEMENT;
    }
    for (auto &elem: _aiMap) {
        for (auto &character: elem) {
            if (character == AIBOMBPLACEMENT) {
                isBombPlacement = true;
                break;
            }
            ++j;
        }
        j = 0;
        ++i;
    }
    if (!isBombPlacement || _walkPositions.empty())
        findBestPath(_aiMap);
    return chooseDirectionOfAi();
}

void Bomberman::Game::Player::actionAi(Bomberman::Game::Map &map)
{
    static int i = 0;
    short x = (short)getPosition().second;
    short y = (short)getPosition().first;
    bool runingOut = false;

    for (auto elem: _map->getListBomb()) {
        if (elem.getPlayer()->getPlayerIndex() == getPlayerIndex()) {
            runOutOfBomb(map);
            runingOut = true;
            _isOnPlacementBomb = false;
        } else {
            runingOut = false;
            _walkSafe.clear();
            _onSafe.clear();
        }
    }
    if (!runingOut) {
        if (_isOnPlacementBomb) {
            putBomb(map);
            _walkSafe.clear();
            _onSafe.clear();
            _walkPositions.clear();
        } else
            applyEvent(moveAi(), map);
    }
    i = i + 1;
}

void Bomberman::Game::Player::movePlayer(Bomberman::Game::Map &map, int yDirection, int xDirection)
{
    char playerIndex = getPlayerIndex();
    char characterNextPosition;
    std::pair<float, float> nextPosition;
    std::pair<float, float> wallPathPosition;
    std::pair<float, float> currentPosition = this->getPosition();
    std::pair<std::pair<int, int>, std::pair<int, int>> nextPlayerPosition;

    nextPosition = std::make_pair((currentPosition.first) + yDirection, (currentPosition.second) + xDirection);
    wallPathPosition = std::make_pair((currentPosition.first) + yDirection * 2, (currentPosition.second) + xDirection * 2);
    
    characterNextPosition = map.getMap()[nextPosition].obj;

    if (map.getMap()[nextPosition].obj == GROUND || map.getMap()[nextPosition].obj == AIPATH ||
    (map.getMap()[nextPosition].obj == BOX && map.getMap()[wallPathPosition].obj == GROUND && getCurrentPowerUps().canWallPass())) {
        if (map.getMap()[nextPosition].obj != BOX)
            map.getMap()[nextPosition].obj = (Object)playerIndex;
        if (yDirection > 0)
            nextPlayerPosition = {
                {currentPosition.first, 1},
                {currentPosition.second, 0}
            };
        else if (yDirection < 0)
            nextPlayerPosition = {
                {currentPosition.first, -1},
                {currentPosition.second, 0}
            };
        else if (xDirection > 0)
            nextPlayerPosition = {
                {currentPosition.first, 0},
                {currentPosition.second, 1}
            };
        else if (xDirection < 0)
            nextPlayerPosition = {
                {currentPosition.first, 0},
                {currentPosition.second, -1}
            };
        if (map.getMap()[currentPosition].obj != BOMB)
            map.getMap()[currentPosition].obj = GROUND;
        this->setPosition(nextPlayerPosition);
        this->setStatus(RUNNING);
        if (map.getMap()[nextPosition].obj == characterNextPosition && characterNextPosition == BOX)
            map.getMap()[nextPosition].obj = BOX;
    }
}

void Bomberman::Game::Player::putBomb(Bomberman::Game::Map &map)
{
    std::pair<float, float> nextPosition = this->getPosition();
    int yDirection = 0, xDirection = 0;

    if (getStatus() != STAND)
        return;
    for (auto &mapCase: map.getMap()) {
        map.getMap()[nextPosition].obj = BOMB;
        map.pushBomb(Bomberman::Game::Bomb(nextPosition, 4000, this));
        incBombCount();
        break;
    }
}

void Bomberman::Game::Player::applyEvent(enum Event event, Bomberman::Game::Map &map)
{
    if (getStatus() != STAND)
        return;
    switch (event) {
        case ACTION_UP:
            movePlayer(map, -1, 0);
            _playerOrientation = UP;
            break;
        case ACTION_DOWN:
            _playerOrientation = DOWN;
            movePlayer(map, 1, 0);
            break;
        case ACTION_RIGHT:
            _playerOrientation = RIGHT;
            movePlayer(map, 0, 1);
            break;
        case ACTION_LEFT:
            _playerOrientation = LEFT;
            movePlayer(map, 0, -1);
            break;
        case ACTION_ACTION:
            if (_placedBombCount >= getCurrentPowerUps().getBombCount())
                break;
            putBomb(map);
            _playerPutBombClock.reset();
            setStatus(PUT_THE_BOMB);
            break;
        case ACTION_STAND:
            break;
        default:
            break;
    }
}

std::pair<float, float> Bomberman::Game::Player::getPosition() const
{
    std::pair<float, float> res = {
        static_cast<float>(static_cast<float>( _position.first.first) + static_cast<float>( _position.first.second) / 10), 
        static_cast<float>(static_cast<float>( _position.second.first) + static_cast<float>( _position.second.second) / 10)
    };
    return res;
}
