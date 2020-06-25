#ifndef CORE_HPP_
#define CORE_HPP_

#include "Menu.hpp"
// #include "Display.hpp"
#include "GameClass.hpp"
#include "MenuPause.hpp"
#include "Saver.hpp"
// #include "DataType.hpp"
#include "GameGraphic.hpp"
#include "EventReceiver.hpp"
#include "DataType.hpp"

typedef enum status {
    MENU,
    GAME,
    QUIT,
    LOAD_GAME,
} status_t;

namespace Bomberman {
    class Core
    {
        // Menu menu;
        // Display disp;

        public:
            Core();
            ~Core() = default;
            void generalLoop(irr::IrrlichtDevice *device, Bomberman::Graphics::EventReceiver &);
            status_t menuLoop(irr::IrrlichtDevice *device, Bomberman::Graphics::EventReceiver &);

            status_t gameLoop(
            irr::IrrlichtDevice *device, 
            Graphics::EventReceiver &receiver, 
            std::map<PlayerIndex, 
            std::map<enum Event, int>> mapKeyPlayer,
            std::vector<enum PlayerIndex> playerIA, 
            int mapId, float volume
            );
            status_t 
            loadedGameLoop(
                irr::IrrlichtDevice *device, 
                Graphics::EventReceiver &receiver, 
                std::map<PlayerIndex, 
                std::map<enum Event, int>> mapKeyPlayer,
                std::vector<enum PlayerIndex> playerIA,
                const std::string &path
            );
        private:
            status_t status = MENU;
            std::vector<enum PlayerIndex> _playerIA;
            playerKeys_t _keyBinding;
            float _volume;
            std::string _filePath;
    };
};

#endif