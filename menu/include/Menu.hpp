/*
** EPITECH PROJECT, 2020
** mymenu
** File description:
** MyMenu
*/

#ifndef MYMENU_HPP_
#define MYMENU_HPP_

#include <array>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <irrlicht.h>
#include <SFML/Audio.hpp>
#include "driverChoice.h"
#include "DataType.hpp"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

struct elems
{
	std::array<IGUIEditBox *, 4>playerEditBox;
	std::array<IGUICheckBox *, 4>playerCheckBox;
	IGUIWindow *window;
	IGUIImage *img;
	bool toDisplay = true;
};

struct SAppContext
{
	IrrlichtDevice *device;
	s32	counter;
	struct elems elem;
};

// enum PlayerIndex {
// 	PLAYER1_INDEX = 1,
// 	PLAYER2_INDEX = 2,
// 	PLAYER3_INDEX = 3,
// 	PLAYER4_INDEX = 4
// };

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_SELECT_PLAYER_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_PLAY_BUTTON,
	GUI_ID_SAVE_BUTTON,
	GUI_ID_SOUND_SCROLL_BAR,
	GUI_ID_STORY_BUTTON
};

typedef enum state {
	PLAY = 1,
	LOAD = 2,
	NONE = 0,
	QUIT_MENU = 3
} state_t;

class MyEventReceiver : public IEventReceiver 
{
    public:
		MyEventReceiver(struct SAppContext & context) : Context(context) { }
		MyEventReceiver(const MyEventReceiver &other);
		~MyEventReceiver() = default;

		MyEventReceiver &operator=(MyEventReceiver &other);
		virtual bool OnEvent(const SEvent& event);
		std::vector<std::wstring>getKeyMap() const;
		state_t getState() const;
		std::vector<int>getPlayables() const;
		std::wstring getFileName() const;
		uint64_t getSoundLevel() const;
		void setSoundLevel(uint64_t);
		std::vector<int>getAi() const;
	private:
		struct SAppContext &Context;
		state_t _state = NONE;
		std::vector<std::wstring>_keymap;
		std::vector<int>_playables;
		std::wstring _fileName;
		uint64_t _soundLevel;
		std::vector<int>_ai;
};

using movement_t = std::map<enum Event, int>;
using playerKeys_t = std::map<enum PlayerIndex, movement_t>;

class MyMenu
{
	public:
		MyMenu() { }
		~MyMenu() = default;
		int menu(IrrlichtDevice * device);
		void setupEnv(IrrlichtDevice *device, IGUIEnvironment *env) const;
		void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin) const;
		std::unique_ptr<MyEventReceiver> event;
		std::vector<std::wstring>getKeyMap() const;
		state_t getState() const;
		movement_t createMapKey(std::wstring &keys) const;
		playerKeys_t bindPlayerKeys();
		std::wstring getFileName() const;
		std::vector<int>getPlayables() const;
		uint64_t getSoundLevel() const;
		playerKeys_t getMapkeyPlayer() const;
		PlayerIndex intToIndex(int) const;
		std::vector<enum PlayerIndex> getPlayers() const;
		void checkKeys();
	private:
		playerKeys_t _mapKeyPlayer;
		uint64_t _soundLevel;
		state_t _state = NONE;
		std::wstring _fileName;
		std::vector<int>_playables;
		std::vector<std::wstring>_keymap;
		sf::Music _music;
		std::vector<int>_ai;
		std::vector<std::wstring>_defaultKeys = {
			L"zqsde", L"fcvbn", L"yghju", L"oklmp"
		};
};
#endif /* !MYMENU_HPP_ */
