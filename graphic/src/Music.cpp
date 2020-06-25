
#include "Music.hpp"

namespace Bomberman {
    namespace Graphics {
        Music::Music(const std::string &path, float volume) {
            _music.openFromFile(path);
            _music.setVolume(volume);
            _music.play();
        }
    }
}