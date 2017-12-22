

#include <iostream>
#include <string>


#include "parser.h"
#include "checkererror.h"

using namespace std;


// in this case such an initialiser list must be used, as you cannot assign istreams
Parser::Parser(istream & is) : mSubmission(is), mState( stInSpace )
{
    mLineNo = 0;    
}

std::string Parser::nextWord()
{
    string word;
    while(char c = nextChar()) 
    {
        switch(mState)
        {
            case stInSpace:
                if (std::isalpha(c)) 
                {
                    word += c;
                    mState = stInWord;
                }
                else if (std::isdigit(c))
                {
                    mState = stInNum;
                }
                break;
            case stInWord:
                if (std::isalpha(c) || c == '\'' )
                {
                    word += c;
                }
                else if (std::isdigit(c))
                {
                    mState = stInNum;
                }
                else 
                {
                    mState = stInSpace;
                    return word;
                }
                break;
            case stInNum:
                if (std::isalnum(c) || c == '\'' )
                {
                    word += c;
                }
                else
                {
                    mState = stInSpace;
                    word = "";
                }
                break;
            default:
                throw CheckerError( "bad state" );
        }
    }
    return word;
}


bool Parser::readLine()
{
    if(getline(mSubmission, mLine))
    {
        // if line exists, reload the istringstream
        // mIStr.clear();
        // mIStr.str(mLine); // add the new line

        mPos = 0; //reset position
        mLineNo++; // increment line no.
        mLine += ' '; 

        return true;

    }
    else if(mSubmission.eof())
    {
        return false;
    }
    else
        throw CheckerError("Read Error");
}

char Parser::nextChar()
{ 
    if(mPos >= mLine.size())
    {
        if(!readLine()) // is there a new line?
        { 
            return 0;  //zero byte indicator 
        }
    } 
    return mLine[mPos++]; 
} 

std::string Parser::context() const
{
    return mLine.substr( 0, mLine.size() - 1 );
}

unsigned int Parser::lineNo() const
{
    return mLineNo;
}