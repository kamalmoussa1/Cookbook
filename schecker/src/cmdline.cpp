#include <string>

#include "cmdline.h"

using namespace std;

CmdLine::CmdLine (int argc, char *argv[]) 
{
    for(int i = 0; i < argc; i++)
    {
        mArgs.push_back(argv[i]); // add arg into the vector 
    }
}

bool CmdLine::HasOpt(const string & opt) const
{
    for(int i = 0; i < Argc(); i++)
    {
        if(opt == Argv(i))
        {
            return true;
        }
    }
    
    return false;
}

CmdLine::Iter CmdLine::FindOpt(const string & opt)
{
    for(int i = 1; i< Argc(); i++) // 0 is the program name 
    {
        if(opt == Argv(i))
        {
            return mArgs.begin() + i;
        }
    }
    
    return mArgs.end();
}

 // options like -xml
bool CmdLine::ExtractOpt(const string & opt)
{
    Iter pos = FindOpt(opt);

    if(pos != mArgs.end())
    {
        mArgs.erase(pos, pos+1);
        return true;
    }
    else
    {
        return false;
    }
} 
// options like -d mydict.dat
bool CmdLine::ExtractOpt(const string & opt, string & val) 
{
    Iter pos = FindOpt(opt);

    if (pos != mArgs.end() && pos != mArgs.end() - 1) 
    {
        val = *(pos + 1);
        mArgs.erase(pos, pos + 2 );
        return true;
    }
    else {
        return false;
    }
}

bool CmdLine::MoreOpts() const
{
    // if(Argc() != 1)
    // {
    //     return true;
    // }
    
    // return false;
}


int CmdLine::Argc() const
{
    return mArgs.size();
}

std:: string CmdLine::Argv(unsigned int i) const
{
    return mArgs[i];
}