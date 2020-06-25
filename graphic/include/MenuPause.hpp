#ifndef MENU_PAUSE_HPP
#define MENU_PAUSE_HPP

#include "Menu.hpp"


namespace Bomberman {
    namespace Graphics {
        enum MenuPauseStatus {
            MENU_ID = 101,
            SAVE_ID,
            QUIT_ID,
            REMOVE_PAUSE,
            STAY,
        };
        class MenuPauseEvtRcv: public irr::IEventReceiver {
            
            enum MenuPauseStatus _status;
            bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

            public:
                MenuPauseEvtRcv();
                ~MenuPauseEvtRcv() = default;
                enum MenuPauseStatus getStatus() {
                    return _status;
                }
                virtual bool OnEvent(const SEvent& event);
                virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

        };

        class MenuPause {
            irr::IEventReceiver *_formerEvtRcv;
            irr::IrrlichtDevice *_device;
            video::IVideoDriver *_driver;
            irr::gui::IGUIEnvironment* _env;
            irr::gui::IGUIWindow *_window;
            MenuPauseEvtRcv _evt;

            public:
                MenuPause(irr::IrrlichtDevice *device);
                enum MenuPauseStatus loop();
                enum MenuPauseStatus getAction();

                ~MenuPause();
        };

    }


}



#endif