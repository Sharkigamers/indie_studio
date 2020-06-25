#include "GameGraphic.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include <algorithm>
#include <utility>
#include "Bomb.hpp"

namespace Bomberman {
    namespace Graphics {
        GameGraphic::GameGraphic(irr::IrrlichtDevice *device, EventReceiver &receiver, std::map<std::pair<float, float>, Element> mapElement,
        std::map<enum PlayerIndex, Game::Player &> listPlayer, std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer, float volume)
                : _receiver(receiver), _action(STAY), _mapKeyPlayer(std::move(mapKeyPlayer)), _music("./assets/Music/music.wav", volume), _volume(volume)
        {
            _device = device;
            _driver = _device->getVideoDriver();
            _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));
            _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/Terrain/grass_bg4.png"), position2d<int>(550, 40));
            _smgr = _device->getSceneManager();

            for (const auto &elem : mapElement) {
                if (elem.second.obj == WALL)
                    _gameObjects.push_back(Wall(_device, elem.first));
                else if (elem.second.obj == BOX)
                    _gameObjects.push_back(Box(_device, elem.first));
                if (elem.second.obj == BOMB) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Bomb")
                        animation->second.refreshAnimation();
                    else
                        _animations[elem.first] = Bomb(_device, elem.first);
                }
                if (elem.second.obj == EXPLOSION) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Flame")
                        animation->second.refreshAnimation();
                    else
                        _animations[elem.first] = Flame(_device, elem.first);
                }
            }
            //stop animation
            for (auto it = _animations.begin(); it != _animations.end();)
                if (mapElement.find(it->first) == mapElement.end()) {
                    it = _animations.erase(it);
                    continue;
                } else
                    it++;
            for (const auto& elem : listPlayer)
                if (elem.second.isAlive())
                    _bombermans.push_back(Bomberman(_device, elem.second.getPosition(), elem.first, elem.second.getOrientation()));
//          _device->getSceneManager()->addCameraSceneNode(0, core::vector3df(-100, 0, -10), core::vector3df(0, 0, 0));
//          _device->getSceneManager()->addCameraSceneNode(0, core::vector3df(0, 0, -100), core::vector3df(0, 0, 0));
//          _device->getSceneManager()->addCameraSceneNode(0, core::vector3df(15, 0, -25), core::vector3df(20, 20, 0));
//          _device->getSceneManager()->addCameraSceneNode(0, core::vector3df(25, 30, -80), core::vector3df(25, 80, 180));
            _device->getSceneManager()->addCameraSceneNode(0, core::vector3df(55, 50, -100), core::vector3df(55, 65, 180));
            _device->getCursorControl()->setVisible(true);
        }
        enum MenuPauseStatus GameGraphic::getAction()
        {
            if (_action == SAVE_ID) {
                _action = STAY;
                return SAVE_ID;
            }
            return _action;
        }


        GameGraphic::~GameGraphic()
        {
            _animations.clear();
            _bombermans.clear();
            _gameObjects.clear();
        }

        void GameGraphic::loop(std::map<std::pair<float, float>, Element> mapElement, std::map<PlayerIndex, Game::Player&> listPlayer)
        {
            if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
                _action = QUIT_ID;
                return;
            }
            if (_receiver.IsKeyDown(irr::KEY_F12)) {
                std::cout << "pause" << std::endl;
                {
                    _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));
                    for (auto &player : listPlayer)
                        this->drawScore(player.first, player.second.getScore(), player.second.getCurrentPowerUps());
                    MenuPause m(_device);

                    enum MenuPauseStatus ret = m.loop();
                    if (ret == SAVE_ID) {
                        _action = SAVE_ID;
                    }
                    if (ret == MENU_ID) {
                        _action = MENU_ID;
                        _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));
                    }
                    if (ret == QUIT_ID) {
                        _action = QUIT_ID;
                    }
                }
                // _device->setEventReceiver(&_receiver);
                std::cout << "new map" << std::endl;
                this->getNewMap(mapElement, listPlayer);
                _receiver.resetKey(irr::KEY_F12);
            }
            _driver->beginScene(true, true, video::SColor(255, 113, 113, 133));
            this->refreshMap(std::move(mapElement), listPlayer);
            _device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
            _smgr->drawAll(); // draw the 3d scene
            for (auto &player : listPlayer)
                this->drawScore(player.first, player.second.getScore(), player.second.getCurrentPowerUps());
            _driver->endScene();
            this->removeFinishedSound();
        }

        void GameGraphic::drawScore(enum PlayerIndex id, int value, Game::PowerUps powerUps)
        {
            IGUIEnvironment* env = _device->getGUIEnvironment();
            IGUIFont* font = env->getFont("./assets/Font/Score/Score.xml");
            core::stringw score = L": ";
            score += value;

            if (font)
                env->getSkin()->setFont(font);
            if (id == PLAYER1_INDEX) {
                env->addImage(_driver->getTexture("./assets/Menu/PlayerSelect/PlayerOneButton.png"), position2d<int>(0, 0));
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(175, -35, 0, 0), 0);
                this->drawBonus(0, 90, powerUps);
            } else if (id == PLAYER2_INDEX) {
                env->addImage(_driver->getTexture("./assets/Menu/PlayerSelect/PlayerTwoButton.png"), position2d<int>(0, 150));
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(175, 115, 0, 0), 0);
                this->drawBonus(0, 240, powerUps);
            } else if (id == PLAYER3_INDEX) {
                env->addImage(_driver->getTexture("./assets/Menu/PlayerSelect/PlayerThreeButton.png"), position2d<int>(1580, 0));
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(1755, -35, 0, 0), 0);
                this->drawBonus(1580, 90, powerUps);
            } else if (id == PLAYER4_INDEX) {
                env->addImage(_driver->getTexture("./assets/Menu/PlayerSelect/PlayerFourButton.png"), position2d<int>(1580, 150));
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(1755, 115, 0, 0), 0);
                this->drawBonus(1580, 240, powerUps);
            }
        }

        void GameGraphic::drawBonus(int x, int y, Game::PowerUps powerUps)
        {
            IGUIEnvironment* env = _device->getGUIEnvironment();
            core::stringw score = L":";
            int value = 0;
            IGUIFont* font = env->getFont("./assets/font/font.xml");

            if (font)
                env->getSkin()->setFont(font);
            if ((value = powerUps.getFirePower())) {
                env->addImage(_driver->getTexture("./assets/textures/little_Fire.png"), position2d<int>(x + 0, y));
                if (font)
                    font->draw((score += value).c_str(), core::rect<s32>(x + 32, y - 15, 0, 0), 0);
            }
            if ((value = powerUps.getBombCount())) {
                score = L":";
                env->addImage(_driver->getTexture("./assets/textures/little_bomb_Up.png"), position2d<int>(x + 102, y));
                if (font)
                    font->draw((score += value).c_str(), core::rect<s32>(x + 135, y - 15, 0, 0), 0);
            }
            if ((value = powerUps.getSpeed())) {
                score = L":";
                env->addImage(_driver->getTexture("./assets/textures/little_Skate.png"), position2d<int>(x + 205, y));
                if (font)
                    font->draw((score += value).c_str(), core::rect<s32>(x + 238, y - 15, 0, 0), 0);
            }
            if ((value = powerUps.canWallPass())) {
                score = L":";
                env->addImage(_driver->getTexture("./assets/textures/little_Soft_Block_Pass.png"), position2d<int>(x + 308, y));
            }
        }

        std::map<PlayerIndex, std::vector<enum Event>> GameGraphic::getEvent()
        {
            std::map<PlayerIndex, std::vector<enum Event>> inputs;
            std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer;

            for (auto& elem : _mapKeyPlayer)
                for (auto& player : elem.second)
                    if (_receiver.IsKeyDown((irr::EKEY_CODE) player.second))
                        inputs[elem.first].push_back(player.first);
            return (inputs);
        }

        bool GameGraphic::isRunning()
        {
            return _action != MENU_ID && _action != QUIT_ID  && _device->run() ? true : false;
        }

        void GameGraphic::refreshMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerIndex, Game::Player&> listPlayer)
        {
            for (auto it = _gameObjects.begin(); it != _gameObjects.end();)
                if (mapElement.find(it->getPositionInMap()) != mapElement.end() && mapElement[it->getPositionInMap()].obj == it->getTypeChar()) {
                    mapElement.erase(mapElement.find(it->getPositionInMap()));
                    ++it;
                } else
                    it = _gameObjects.erase(it);

            for (const auto &elem : mapElement) {
                 if (elem.second.obj == WALL)
                     _gameObjects.push_back(Wall(_device, elem.first));
                 else if (elem.second.obj == BOX)
                     _gameObjects.push_back(Box(_device, elem.first));
                if (elem.second.obj == BOMB) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Bomb") {
                        animation->second.refreshAnimation();
                    } else
                        _animations[elem.first] = Bomb(_device, elem.first);
                }
                if (elem.second.obj == EXPLOSION) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Flame") {
                        animation->second.refreshAnimation();
                    }
                    else {
                        if (animation != _animations.end() && animation->second.getType() == "Bomb")
                            _sounds.emplace_back("assets/Sounds/Explosion+9.wav", _volume);
                        _animations[elem.first] = Flame(_device, elem.first);
                    }
                }
            }
            //stop animation
            for (auto it = _animations.begin(); it != _animations.end();)  {
                if (mapElement.find(it->first)->second.obj != BOMB && mapElement.find(it->first)->second.obj != EXPLOSION) {
                    std::cout << it->second.getType() << std::endl;
                    it = _animations.erase(it);
                    continue;
                } else
                    it++;
            }
            for (const auto& elem : listPlayer) {
                if (elem.second.isAlive()) {
                    for (auto &_bomberman : _bombermans)
                        if (_bomberman.getId() == (elem.first - 49))
                            _bomberman.refreshPlayer(elem.second);
                } else {
                   for (auto it = _bombermans.begin(); it != _bombermans.end();) {
                       if (it->getId() == (elem.first - 49))
                           it = _bombermans.erase(it);
                       else
                           it++;
                   }
               }
            }
        }

        void GameGraphic::getNewMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerIndex, Game::Player&> listPlayer)
        {
            _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));
            _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/Terrain/grass_bg4.png"), position2d<int>(550, 40));
            _bombermans.clear();
            _gameObjects.clear();
            _animations.clear();

            for (const auto &elem : mapElement) {
                if (elem.second.obj == WALL)
                    _gameObjects.push_back(Wall(_device, elem.first));
                else if (elem.second.obj == BOX)
                    _gameObjects.push_back(Box(_device, elem.first));
                if (elem.second.obj == BOMB) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Bomb")
                        animation->second.refreshAnimation();
                    else
                        _animations[elem.first] = Bomb(_device, elem.first);
                }
                if (elem.second.obj == EXPLOSION) {
                    auto animation = _animations.find(elem.first);
                    if (animation != _animations.end() && animation->second.getType() == "Flame")
                        animation->second.refreshAnimation();
                    else
                        _animations[elem.first] = Flame(_device, elem.first);
                }
            }
            //stop animation
            for (auto it = _animations.begin(); it != _animations.end();)
                if (mapElement.find(it->first) == mapElement.end()) {
                    it = _animations.erase(it);
                    continue;
                } else
                    it++;

            for (const auto& elem : listPlayer)
                if (elem.second.isAlive())
                    _bombermans.push_back(Bomberman(_device, elem.second.getPosition(), elem.first, elem.second.getOrientation()));
        }

        //TODO exemple for the next function
//        std::map<std::string, int> mapScore = {
//                {"PLAYER 1", 100},
//                {"PLAYER 2", 1500},
//                {"PLAYER 3", 50},
//                {"PLAYER 4", 150}
//        };
//        if (this->displayEndScore(mapScore) == 1);//stop calling the function
        int GameGraphic::displayEndScore(std::map<std::string, int> mapScore)
        {
            if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
                _action = QUIT_ID;
                return (-1);
            } else if (_receiver.IsKeyDown(irr::KEY_RETURN)) {// go to next game/menu
                return (1);
            }
            _device->getGUIEnvironment()->addImage(_driver->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));

            auto cmp = [](std::pair<std::string, int> const & a, std::pair<std::string, int> const & b)
            {
                return a.second > b.second;
            };
            std::vector<std::pair<std::string, int>> vec;
            vec.reserve(mapScore.size());
            for (auto & it2 : mapScore)
                vec.emplace_back(it2.first, it2.second);
            sort(vec.begin(), vec.end(), cmp);

            _driver->beginScene(true, true, video::SColor(255, 113, 113, 133));
            _device->getGUIEnvironment()->drawAll();
            int i = 0;
            for (auto &score : vec) {
                this->drawEndScore(++i, score.first, score.second);
            }
            _driver->endScene();
            return (0);
        }

        void GameGraphic::drawEndScore(int id, const std::string& player, int value) {
            IGUIEnvironment *env = _device->getGUIEnvironment();
            IGUIFont *font = env->getFont("./assets/Font/test/score.xml");
            core::stringw score = core::stringw(player.c_str());
            score += ":";
            score += value;

            if (font) {
                env->getSkin()->setFont(font);
                font->setKerningWidth(-15);
            }
            if (id == 1) {
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(700, 150, 0, 0), 0);
            } else if (id == 2) {
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(700, 300, 0, 0), 0);
            } else if (id == 3) {
                if (font)
                    font->draw(score.c_str(), core::rect<s32>(700, 450, 0, 0), 0);
            } else if (id == 4) {
                if (font) {
                    font->draw(score.c_str(), core::rect<s32>(700, 600, 0, 0), 0);
                    font->draw((core::stringw(L"press enter to continue")).c_str(), core::rect<s32>(500, 900, 0, 0), 0);
                }
            }
        }

        void GameGraphic::removeFinishedSound() {
            for (auto it = _sounds.begin(); it != _sounds.end();) {
                if (it->soundIsDone()) {
                    _sounds.erase(it);
                } else {
                    it++;
                }
            }
        }
    }
}


