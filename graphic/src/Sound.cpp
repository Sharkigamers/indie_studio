#include "Sound.hpp"

namespace Bomberman {
    namespace Graphics {
        Sound::Sound(const std::string &path, float volume) {
            _buff.loadFromFile(path);
            _sound.setBuffer(_buff);
            _sound.setVolume(volume);
            _sound.play();
            _time = _sound.getPlayingOffset();
        }
        Sound::Sound(Sound &&cpy) {
            _buff = cpy._buff;
            _sound = cpy._sound;
            _time = cpy._time;
        }
        Sound &Sound::operator=(const Sound &cpy) {
            _buff = cpy._buff;
            _sound = cpy._sound;
            _time = cpy._time;
            return (*this);
        }
        void Sound::play() {
            _sound.play();
        }
        void Sound::stop() {
            _sound.stop();
        }
        bool Sound::soundIsDone() {
            sf::Time current = _sound.getPlayingOffset();
            if (_time == current) {
                return true;
            }
            _time = current;
            return false;
        }

    }
}