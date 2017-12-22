#ifndef CMDLINE_H
#define CMDLINE_H

#include <string>
#include <vector>
#include <iterator>

class CmdLine {
  public:

    CmdLine(int argc, char *argv[]);
    bool HasOpt(const std::string & opt) const;
    bool ExtractOpt(const std::string & opt);
    bool ExtractOpt(const std::string & opt, std::string & val);
    bool MoreOpts() const;

    int Argc() const; // retuen current's cmdline size 
    std::string Argv(unsigned int i) const; // current cmdline value at index i


  private:


    typedef std::vector<std::string> ArgVec;  
    typedef ArgVec::iterator Iter;
    
    Iter FindOpt(const std::string & opt);
    ArgVec mArgs; // vector of strings 

    // const int mArgc;
};



#endif
