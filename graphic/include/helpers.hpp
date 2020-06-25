#ifndef HELPER_HPP
#define HELPER_HPP

#include "object.hpp"
#include "DataType.hpp"
#include <map>
#include <iostream>
#include <fstream>

std::map<std::pair<float, float>, Element> 
initializeMap(const std::string path);


#endif