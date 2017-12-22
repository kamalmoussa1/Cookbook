#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <string>

class Parser
{

    public: 

        Parser(std::istream & is);
        std::string nextWord();
        std::string context() const;
        unsigned int lineNo() const;


    private:
        // need a reference, because stream objects cannot be copied
        std::istream & mSubmission; 
        std::istringstream mIStr;
        std::string mLine;
        unsigned int mLineNo, mPos;
        enum State { stInSpace, stInWord, stInNum };
        State mState;
        char nextChar();
        bool readLine();



};




#endif