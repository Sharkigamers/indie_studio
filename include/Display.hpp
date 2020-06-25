#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "DataType.hpp"

namespace Bomberman {
    class Display {

        public:
            struct ActionMouse getUserMouseInput();
            enum Action getInput();
            void displayGame(std::unordered_map<std::pair<int, int>, struct Element> map);
    };
};
#endif