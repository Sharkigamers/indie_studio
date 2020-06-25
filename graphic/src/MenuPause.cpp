#include "MenuPause.hpp"


namespace Bomberman {
    namespace Graphics {
        MenuPauseEvtRcv::MenuPauseEvtRcv(): _status(STAY) {
                for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
        }
        
        bool MenuPauseEvtRcv::OnEvent(const SEvent& event) {
            if (event.EventType != EET_GUI_EVENT) {
                return false;
            }
            
            irr::s32 id = event.GUIEvent.Caller->getID();
         
            if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
                if (id == MENU_ID) {
                    _status = MENU_ID;
                    return true;
                }
                if (id == SAVE_ID) {
                    _status = SAVE_ID;
                    return true;
                }
                if (id == QUIT_ID) {
                    _status = QUIT_ID;
                    return true;
                }
            }
            if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
                if (event.KeyInput.Key == irr::KEY_F12)
                    _status = REMOVE_PAUSE;
                KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                return true;
            }
            return false;
        }
        bool MenuPauseEvtRcv::IsKeyDown(irr::EKEY_CODE keyCode) const {
            return KeyIsDown[keyCode];
        }

        MenuPause::MenuPause(irr::IrrlichtDevice *device) {
            _device = device;
            _formerEvtRcv = _device->getEventReceiver();
            _driver = _device->getVideoDriver();
            _env = _device->getGUIEnvironment();
            _device->setEventReceiver(&_evt);
            IGUISkin *skin = _env->getSkin();
            IGUIFont *font = _env->getFont("assets/Menu/fonthaettenschweiler.bmp");

            if (font)
                skin->setFont(font);

            skin->setFont(_env->getBuiltInFont(), EGDF_TOOLTIP);
            _window = _env->addWindow(rect<s32>(700, 200, 1100, 700), true, L"Pause");
            _env->addButton(rect<s32>(150, 100, 250, 150), _window, MENU_ID, L"Go back to Menu", L"back to menu");
            _env->addButton(rect<s32>(150, 250, 250, 300), _window, SAVE_ID, L"Save Game", L"save party");
            _env->addButton(rect<s32>(150, 400, 250, 450), _window, QUIT_ID, L"Quit", L"quit");
        }
        MenuPause::~MenuPause() {
            std::cout << "die" << std::endl;
            _window->remove();
            _env->clear();
            _device->setEventReceiver(_formerEvtRcv);
        }

        enum MenuPauseStatus MenuPause::loop()
         {
            while (_evt.getStatus() == STAY && _device->run()) {
                if (_device->isWindowActive()) {
                    _driver->beginScene(true, true, SColor(0,200,200,200));
                    
                    _env->drawAll();

                    _driver->endScene();
                }
                if (_window->getCloseButton()->isPressed()) {
                    return REMOVE_PAUSE;
                }
            }
            return _evt.getStatus();
        }

    }
}