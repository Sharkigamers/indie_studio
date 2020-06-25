#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <iostream>
#include <sstream>

class IndieException: public std::exception
{
    public:
        IndieException(std::string const &message, 
        std::string const &componentName = "Unknown");
        const char *what() const noexcept override;
    protected:
        std::string _message;
};

class ExampleException: public ExampleException
{
    public:
        ExampleException(std::string const &message, 
        std::string const &componentName = "ExampleException");
};


#endif