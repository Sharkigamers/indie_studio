/*
** EPITECH PROJECT, 2020
** Music.hpp
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <SFML/Audio.hpp>
#include <string>

class Music {
    public:
        Music(const std::string &, float volume = 50);
        ~Music();

        std::string getPath() const {return (_path);}
        void setPath(const std::string &path) {_path = path;}
        void setVolume(float volume) {_volume = volume;}
        void playMusic() {_music.play();}
        void stopMusic() {_music.stop();}
    protected:
    private:
        std::string _path;
        sf::Music _music;
        float _volume;
};

#endif /* !MUSIC_HPP_ */
