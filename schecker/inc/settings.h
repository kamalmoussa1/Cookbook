#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "cmdline.h"


class Settings 
{
    public:
        
        Settings (CmdLine & cl);
       
        enum Report { rtCSV, rtXML };
        Report ReportType() const; // return even rtCSV or rtXML
        std::string DictName() const;       

        ~Settings();
    private:

        Report mRepType;
        std::string mDictName;

};


#endif