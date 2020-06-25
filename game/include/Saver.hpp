/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Saver
*/

#ifndef SAVER_HPP_
#define SAVER_HPP_

#include <string>
#include <map>

#include "object.hpp"
#include "Player.hpp"

#define SAVE_PATH "save/game_save"

namespace Bomberman {
    namespace Game {
        class Saver {
            public:
                Saver();
                ~Saver();

                void load(const std::string path = "save/game_save");
                void save(std::map<std::pair<float, float>, Element> &map, std::map<PlayerIndex, Bomberman::Game::Player&> player);

                std::tuple<std::string, bool, std::vector<int>, int> parseString(std::string line);
                void setCharacterFromLoad(std::vector<std::string> &myCharacter);

                std::string getMap() { return _map; }
                std::map<int, std::tuple<std::string, bool, std::vector<int>, int>> getCharacter() { return _character; }

            protected:
            private:
                std::string _map;
                std::map<int, std::tuple<std::string, bool, std::vector<int>, int>> _character;
        };
    }
}

#endif /* !SAVER_HPP_ */
