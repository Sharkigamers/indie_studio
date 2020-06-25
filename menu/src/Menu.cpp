/*
** EPITECH PROJECT, 2020
** main
** File description:
** main
*/

#include "Menu.hpp"
#include <unistd.h>

MyEventReceiver::MyEventReceiver(const MyEventReceiver &other) : Context(other.Context)
{
	if (&other != this) {
		this->Context = other.Context;
		this->_keymap = other._keymap;
		this->_state = other._state;
	}
}

MyEventReceiver &MyEventReceiver::operator=(MyEventReceiver &other)
{
	if (&other != this) {
		this->Context = other.Context;
		this->_keymap = other._keymap;
		this->_state = other._state;
	}
	return (*this);
}

std::vector<int> MyEventReceiver::getAi() const
{
	return (_ai);
}

state_t MyEventReceiver::getState() const
{
	return (_state);
}

void MyEventReceiver::setSoundLevel(uint64_t volume) 
{
	_soundLevel = volume;
}

std::vector<std::wstring>MyEventReceiver::getKeyMap() const
{
	return (_keymap);
}

std::vector<int>MyEventReceiver::getPlayables() const
{
	return (_playables);
}

std::wstring MyEventReceiver::getFileName() const
{
	return (_fileName);
}

uint64_t MyEventReceiver::getSoundLevel() const
{
	return (_soundLevel);
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = Context.device->getGUIEnvironment();

		switch(event.GUIEvent.EventType) {
			case EGET_BUTTON_CLICKED:
				switch(id) {
					case GUI_ID_PLAY_BUTTON:
						_state = PLAY;
						return true;

					case GUI_ID_QUIT_BUTTON:
						// Context.device->closeDevice();
						// Context.device->drop();
						_state = QUIT_MENU;
						return true;

					case GUI_ID_STORY_BUTTON:
					{
						if (Context.elem.toDisplay) {
							Context.elem.img = env->addImage(Context.device->getVideoDriver()->getTexture("./assets/pd.png"), position2d<int>(-10, -15));
						}
						else {
							Context.elem.img->setVisible(false);
							Context.elem.toDisplay = true;
						}
						return true;
					}

					case GUI_ID_SELECT_PLAYER_BUTTON:
						{
						Context.counter += 30;
						if (Context.counter > 200)
							Context.counter = 0;

						IGUIWindow* window = env->addWindow(
							rect<s32>(200 + Context.counter, 200 + Context.counter, 600 + Context.counter, 400 + Context.counter),
							true,
							L"Select player");
						Context.elem.window = window;
						env->addStaticText(L"player1",
							rect<s32>(35,35,140,50),
							false,
							true,
							window);
						Context.elem.playerCheckBox[0] = env->addCheckBox(false, rect<s32>(85,35,140,50), window);
						Context.elem.playerEditBox[0] = env->addEditBox(L"zqsde", rect<s32>(115, 35, 200, 50), true, window);
						
						env->addStaticText(L"player2",
							rect<s32>(35,55,140,70),
							false,
							true,
							window);
						Context.elem.playerCheckBox[1] = env->addCheckBox(false, rect<s32>(85,55,140,70), window);
						Context.elem.playerEditBox[1] = env->addEditBox(L"fcvbn", rect<s32>(115, 55, 200, 70), true, window);
						
						env->addStaticText(L"player3",
							rect<s32>(35,75,140,90),
							false,
							true,
							window);
						Context.elem.playerCheckBox[2] = env->addCheckBox(false, rect<s32>(85,75,140,90), window);
						Context.elem.playerEditBox[2] = env->addEditBox(L"yghju", rect<s32>(115, 75, 200, 90), true, window);

						env->addStaticText(L"player4",
							rect<s32>(35,95,140,115),
							false,
							true,
							window);
						Context.elem.playerCheckBox[3] = env->addCheckBox(false, rect<s32>(85,95,140,115), window);
						Context.elem.playerEditBox[3] = env->addEditBox(L"oklmp", rect<s32>(115, 95, 200, 110), true, window);
						env->addButton(rect<s32>(115, 115, 200, 135), window, GUI_ID_SAVE_BUTTON,
						L"Save", L"Saves settings");
						}
						return true;
					
						case GUI_ID_SAVE_BUTTON:
							for (int i = 0; i <= 3; ++i) {
								if (Context.elem.playerCheckBox[i]->isChecked()) {
									_playables.push_back(i);
									_keymap.push_back(Context.elem.playerEditBox[i]->getText());
								}
								else if (!Context.elem.playerCheckBox[i]->isChecked())
									_ai.push_back(i);
							}
							Context.elem.window->remove();
							return true;
					
					case GUI_ID_FILE_OPEN_BUTTON:
						env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
						return true;

					default:
						return false;
			}
			break;

		case EGET_FILE_SELECTED:
			{
				IGUIFileOpenDialog* dialog =
					(IGUIFileOpenDialog*)event.GUIEvent.Caller;
				_fileName = dialog->getFileName();
				_state = LOAD;
				return 1;
			}
			break;
		
		case EGET_SCROLL_BAR_CHANGED:
			if (id == GUI_ID_SOUND_SCROLL_BAR)
			{
				s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
				_soundLevel = pos;
			}
			break;

		default:
			break;
		}
	} else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		if (event.KeyInput.Key == KEY_RETURN && Context.elem.img) {
			Context.elem.toDisplay = false;
		}
	}

	return false;
}

void MyMenu::setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin) const
{
    for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}

void MyMenu::setupEnv(IrrlichtDevice *device, IGUIEnvironment *env) const
{
	env->addButton(rect<s32>(200,200,510,200 + 32), 0, GUI_ID_PLAY_BUTTON,
			L"Play", L"Launch thes game");
	env->addButton(rect<s32>(200,240,510,240 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
			L"Load", L"Loads a game");
	env->addButton(rect<s32>(200,280,510,280 + 32), 0, GUI_ID_SELECT_PLAYER_BUTTON,
			L"Select Player", L"Select wich player will play");
	env->addButton(rect<s32>(200,320,510,320 + 32), 0,GUI_ID_QUIT_BUTTON,
			L"Quit", L"Exit Program");
	env->addStaticText(L"Sound Volume:", rect<s32>(200,400, 510, 400 + 32), false, true);
    IGUIScrollBar* scrollbar = env->addScrollBar(true,
            rect<s32>(200, 420,510, 420 + 32), 0, GUI_ID_SOUND_SCROLL_BAR);
	env->addButton(rect<s32>(200,520,510,520 + 32), 0,GUI_ID_STORY_BUTTON,
			L"Story", L"Explain story");
    scrollbar->setMax(100);
    scrollbar->setPos(50);
}

int MyMenu::menu(irr::IrrlichtDevice *device)
{
    device->getGUIEnvironment()->addImage(device->getVideoDriver()->getTexture("./assets/small_bg.png"), position2d<int>(0, 0));
	SAppContext context;
	// IrrlichtDevice * device = createDevice(irr::video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480));

	char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
	if (device == 0)
		return 1;

	if (!_music.openFromFile("assets/Menu/menu.wav"))
    	return -1;
	device->setWindowCaption(L"Bomberman Menu");
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();
	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("assets/Menu/fonthaettenschweiler.bmp");

	if (font)
		skin->setFont(font);
	skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
	setSkinTransparency(255, env->getSkin());
	setupEnv(device, env);
	context.device = device;
	context.counter = 0;
	MyEventReceiver receiver(context);
	device->setEventReceiver(&receiver);
	receiver.setSoundLevel(50);
	_music.play();

	while(device->run() && driver && receiver.getState() != PLAY && receiver.getState() != QUIT_MENU && receiver.getState() != LOAD) {
		if (device->isWindowActive()) {
			driver->beginScene(true, true, SColor(50, 40, 80, 160));
			env->drawAll();
			_music.setVolume(receiver.getSoundLevel());
			driver->endScene();
		}
	}
	_state = receiver.getState();
	_keymap = receiver.getKeyMap();
	_playables = receiver.getPlayables();
	_mapKeyPlayer = bindPlayerKeys();
	_fileName = receiver.getFileName();
	_soundLevel = receiver.getSoundLevel();
	_ai = receiver.getAi();
	chdir(cwd);
	return 1;
}

state_t MyMenu::getState() const
{
	return _state;
}

std::vector<std::wstring> MyMenu::getKeyMap() const
{
	return _keymap;
}

std::vector<int>MyMenu::getPlayables() const
{
	return (_playables);
}

playerKeys_t MyMenu::getMapkeyPlayer() const
{
	return (_mapKeyPlayer);
}

std::wstring MyMenu::getFileName() const
{
	return (_fileName);
}

uint64_t MyMenu::getSoundLevel() const
{
	return (_soundLevel);
}

std::vector<enum PlayerIndex> MyMenu::getPlayers() const
{
	std::vector<enum PlayerIndex> players;

	for (size_t i = 0; i != _ai.size(); ++i) {
		players.push_back(intToIndex(_ai[i]));
	}
	return (players);
}

// int main()
// {
// 	MyMenu lopes;
// 	lopes.menu();
	
// 	playerKeys_t test = lopes.getMapkeyPlayer();
// 	std::cout << test[PLAYER1_INDEX][UP] << std::endl;
// 	std::wcout << lopes.getFileName() << std::endl;
// 	std::cout << lopes.getSoundLevel() << std::endl;
// }
	