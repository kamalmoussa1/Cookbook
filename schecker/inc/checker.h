#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <iostream>
#include <sstream>
#include  "dictionary.h"
#include  "settings.h"
#include  "reporter.h"

class Checker
{
    public:
        Checker();

        Reporter *makeReporter(Settings::Report rt);
        void checkSubmission( const Dictionary & d, std::istream  & sub,
                              const std::string & subname, Reporter & rep);
        
        ~Checker();

};




#endif