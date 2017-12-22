
#include <string>

#include "settings.h"
#include "checkererror.h"

const char * const DEF_DICT = "data/dictionary.dat";
const char * const DICT_OPT = "-d";
const char * const CSV_OPT =  "-csv";
const char * const XML_OPT =  "-xml";

Settings::Settings(CmdLine & cl) :  mRepType(rtCSV), mDictName(DEF_DICT)
{
    if (cl.HasOpt(CSV_OPT) && cl.HasOpt(XML_OPT))
    {
        throw CheckerError("Only one type of outputs can be selected");
    }

    // check for xML
    if (cl.ExtractOpt(XML_OPT))
    {
        mRepType = rtXML;
    }

    // check for CSV [extra]
    if (cl.ExtractOpt(CSV_OPT))
    {
        mRepType = rtCSV;
    }

    // check for dicts 
    cl.ExtractOpt(DICT_OPT, mDictName);

    // if (cl.MoreOpts()) 
    // {
    //     throw CheckerError( "Invalid command line" );
    // }
}


Settings::Report Settings::ReportType() const
{
    return mRepType;
}
                            

std::string Settings::DictName() const
{
    return mDictName;
}


Settings::~Settings(){}