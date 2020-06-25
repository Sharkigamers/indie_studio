#include "Exception.hpp"

IndieException::IndieException(std::string const &message, 
            std::string const &componentName) {
                std::ostringstream ss;
                ss << componentName << ": " << message << "." << std::endl;
                _message = ss.str();
            }

const char *IndieException::what()
const
noexcept
{
    return (_message.c_str());
}

Example::NetworkException(
    std::string const &message, 
    std::string const &componentName): IndieException(message, componentName)
   
{}