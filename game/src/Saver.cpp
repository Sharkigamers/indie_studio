/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Saver
*/

#include <iostream>
#include <fstream>

#include <vector>

#include "Saver.hpp"
#include "MapCreation.hpp"

Bomberman::Game::Saver::Saver()
{
}

Bomberman::Game::Saver::Saver::~Saver()
{
}

void Bomberman::Game::Saver::save(std::map<std::pair<float, float>, Element> &map,
std::map<PlayerIndex, Bomberman::Game::Player&> player)
{
    std::string fileContent = "map:\n";
    std::ofstream myFile(SAVE_PATH);

    for (const auto &elem: map) {
        if (elem.second.obj == BOMB)
            fileContent += GROUND;
        else
            fileContent += elem.second.obj;
    }
    fileContent += "endmap\ncharacter:\n";
    for (const auto &eachPlayer: player) {
        fileContent += std::to_string(eachPlayer.first);
        fileContent += ":";
        if (eachPlayer.second.isIA())
            fileContent += "ai";
        else
            fileContent += eachPlayer.second.getName();
        fileContent += ",";
        if (eachPlayer.second.getStatus())
            fileContent += "alive";
        else
            fileContent += "mylopezisdead";
        fileContent += ",[";
        fileContent += std::to_string(eachPlayer.second.getCurrentPowerUps().getFirePower());
        fileContent += ";";
        fileContent += std::to_string(eachPlayer.second.getCurrentPowerUps().getBombCount());
        fileContent += ";";
        fileContent += std::to_string(eachPlayer.second.getCurrentPowerUps().getSpeed());
        fileContent += ";";
        fileContent += std::to_string(eachPlayer.second.getCurrentPowerUps().canWallPass());
        fileContent += "],";
        fileContent += std::to_string(eachPlayer.second.getScore());
        fileContent += "\n";
    }
    fileContent += "endcharacter\n";
    myFile << fileContent;
    myFile.close();
}

std::tuple<std::string, bool, std::vector<int>, int>
Bomberman::Game::Saver::parseString(std::string line)
{
    std::string name;
    bool isAlive;
    std::vector<int> powerUp;
    int score;
    std::string inLine;
    std::string inList;
    int i = 0;
    int j = 0;

    while (line.find(",") != -1) {
        inLine = line.substr(0, line.find(","));
        switch (i)
        {
        case 0:
            name = inLine;
            break;
        case 1:
            if (inLine.compare("alive") == 0)
                isAlive = true;
            else
                isAlive = false;
            break;
        case 2:
            inList = inLine;
            j = 0;
            while (inList.find(";") != -1) {
                j == 0 ? powerUp.push_back(stoi(inList.substr(1, inList.find(";"))))
                : powerUp.push_back(stoi(inList.substr(0, inList.find(";"))));
                inList = inList.substr(inList.find(";") + 1);
                ++j;
            }
            if (inList.at(0) != '[')
                powerUp.push_back(stoi(inList.substr(0, inList.length() - 1)));
            else if (inList.length() != 2)
                powerUp.push_back(stoi(inList.substr(1, inList.length() - 2)));
            break;
        default:
            break;
        }
        line = line.substr(line.find(",") + 1, line.length());
        ++i;
    }
    score = stoi(line);
    return std::make_tuple(name, isAlive, powerUp, score);
}

void Bomberman::Game::Saver::setCharacterFromLoad(std::vector<std::string> &myCharacter)
{
    int player;
    std::tuple<std::string, bool, std::vector<int>, int> characterTuple;
    std::string endOfLine;

    for (auto &line: myCharacter) {
        player = stoi(line.substr(0, line.find(":")));
        endOfLine = line.substr(line.find(":") + 1);
        characterTuple = parseString(endOfLine);
        _character.insert({player, characterTuple});
    }
}

void Bomberman::Game::Saver::load(const std::string path)
{
    bool loadingMap = false;
    bool loadingCharacter = false;
    std::ifstream myfile(path);
    std::string line = "";
    std::vector<std::string> myCharacter;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.compare("endmap") == 0)
                loadingMap = false;
            if (line.compare("endcharacter") == 0)
                loadingCharacter = false;
            if (loadingCharacter)
                myCharacter.push_back(line);
            else if (loadingMap)
                _map += line + "\n";
            if (line.compare("map:") == 0)
                loadingMap = true;
            if (line.compare("character:") == 0)
                loadingCharacter = true;
        }
    }
    setCharacterFromLoad(myCharacter);
}

// int main(void)
// {
//     Bomberman::Game::Saver saver;
    
//     saver.load("../../save/save_game");
// }
