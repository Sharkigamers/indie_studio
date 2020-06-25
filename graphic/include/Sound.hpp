#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>

namespace Bomberman {
    namespace Graphics {
        class Sound {
            sf::SoundBuffer _buff;
            sf::Sound _sound;
            sf::Time _time;
            public:
                Sound(const std::string &path, float volume);
                Sound(Sound &&cpy);
                Sound &operator=(const Sound &cpy);

                void play();
                void stop();
                bool soundIsDone();
                ~Sound() = default;
        };
    }
}

#endif