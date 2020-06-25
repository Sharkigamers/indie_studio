#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
namespace Bomberman {
    namespace Graphics {
        class Music {
            sf::Music _music;
            public:
                Music(const std::string &path, float volume);
                ~Music() = default;
        };
    }
}

#endif