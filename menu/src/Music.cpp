/*
** EPITECH PROJECT, 2020
** Music
** File description:
** Music
*/

#include "Music.hpp"

Music::Music(const std::string &filePath, float volume)
{
    _path = filePath;
    _volume = volume;
    if (!_music.openFromFile(_path))
        return;
    _music.setVolume(_volume);
}

Music::~Music()
{
}
