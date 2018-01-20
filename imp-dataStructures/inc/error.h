#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

class CError : public std::runtime_error
{

public:
  CError(const std::string & emsg) : std::runtime_error("ERROR: " + emsg) {}

};

#endif