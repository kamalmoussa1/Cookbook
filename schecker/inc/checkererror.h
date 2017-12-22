#ifndef CHECKERERROR_H
#define CHECKERERROR_H

#include <stdexcept>
#include <string>

class CheckerError : public std::runtime_error
{

    public:
       CheckerError(const std::string & emsg) : std::runtime_error(emsg) {} //initialiser list

};







#endif