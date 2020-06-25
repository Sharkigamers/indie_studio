#ifndef GAME_GRAPHIC_HPP
#define GAME_GRAPHIC_HPP

#include <irrlicht.h>
#include "EventReceiver.hpp"
#include "Bomberman.hpp"
#include "GameObject.hpp"
#include "Bomb.hpp"
#include "Flame.hpp"
#include <map>
#include <vector>
#include "helpers.hpp"
#include "MeshContainer.hpp"
#include "DataType.hpp"
#include "Sound.hpp"
#include "Music.hpp"
#include "MenuPause.hpp"

namespace Bomberman {
    namespace Graphics {
        class GameGraphic {
            irr::IrrlichtDevice *_device;
            video::IVideoDriver *_driver;
            scene::ISceneManager *_smgr;
            EventReceiver &_receiver;
            
            // bool _quit;
            MenuPauseStatus _action;
            
            std::map<PlayerIndex, std::map<enum Event, int>> _mapKeyPlayer;
            
            std::vector<Bomberman> _bombermans;
            std::vector<AGameObject> _gameObjects;
            
            std::map<pos_t, MeshContainer> _animations;
            
            std::vector<Sound> _sounds;
            Music _music;
            float _volume;

        public:
            GameGraphic(irr::IrrlichtDevice *device, EventReceiver &receiver, std::map<std::pair<float, float>, Element> map,
                       std::map<PlayerIndex, Game::Player&> listPlayer, std::map<PlayerIndex, std::map<enum Event, int>> mapKeyPlayer, float volume);
            ~GameGraphic();
//            void loop(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerID, Game::Player> listPlayer);
//            void refreshMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerID, Game::Player> listPlayer);
//            void getNewMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerID, Game::Player> listPlayer);//when going to the next level
            void loop(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerIndex, Game::Player&> listPlayer);
            void refreshMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerIndex, Game::Player&> listPlayer);
            void getNewMap(std::map<std::pair<float, float>, Element> mapElement, std::map<enum PlayerIndex, Game::Player&> listPlayer);//when going to the next level
            bool isRunning();
            std::map<PlayerIndex, std::vector<enum Event>> getEvent();
            void drawScore(enum PlayerIndex id, int value, Game::PowerUps powerUps);
            void drawBonus(int x, int y, Game::PowerUps powerUps);
            int displayEndScore(std::map<std::string, int> mapScore);
            void drawEndScore(int id, const std::string& player, int score);
            void removeFinishedSound();
            enum MenuPauseStatus getAction();
            // event
            // quit()
        };
    }
}

#endif