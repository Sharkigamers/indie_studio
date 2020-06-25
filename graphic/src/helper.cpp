
#include "helpers.hpp"

std::map<std::pair<float, float>, Element> initializeMap(const std::string path)
{
    int i = 0;
    int j = 0;
    std::ifstream mapContent;
    std::string line;
    std::string mapCharged;
    std::pair<int, int> elementPosition;
    Element elementFromMap;
    std::map<std::pair<float, float>, Element> map;
    char c;

    mapContent.open(path);
    if (!mapContent) {
        std::cerr << "Error: Can't open map: " << path << std::endl;
        exit(84);
    }
    while (getline(mapContent, line))
        mapCharged += line + "\n";
    for (char &character: mapCharged) {
        if (character != '\n') {
            elementPosition = std::make_pair(i, j);
            elementFromMap.obj = static_cast<Object>(character);
            elementFromMap.animation = 0;
            map.insert({elementPosition, elementFromMap});
            ++j;
        } else {
            ++i;
            j = 0;
        }
    }
    return map;
}
