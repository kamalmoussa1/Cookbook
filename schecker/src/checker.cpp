#include <iostream>

#include "checker.h"
#include "csvreporter.h"
#include "xmlreporter.h"
#include "parser.h"

using namespace std;

Checker::Checker()
{

}

Reporter * Checker::makeReporter(Settings::Report rt)
{
    if (rt == Settings::rtCSV)
    {
        return new CSVReporter(cout);
         //reporter = auto_ptr <Reporter> ( new CSVReporter( cout ) );
    }
    else 
    {
        return new XMLReporter(cout);
        //reporter = auto_ptr <Reporter> ( new XMLReporter( cout ) );

    }
}

void Checker::checkSubmission(const Dictionary & d, std::istream  & sub,
                              const std::string & subname, Reporter & rep)

{
    Parser textParser(sub);
    rep.reportHeader();

    string word;
    // until no-other-words
    while ((word = textParser.nextWord()) != "")    
    {
        if(!d.Check(word)) 
        {
            // cout << word << " is OK\n";
            rep.reportError(word,
                            textParser.context(),
                            textParser.lineNo(),
                            subname);     
        }
        else if(subname == "stdin")
        {
            cout << word << " is ok\n";
        }
    }
    rep.reportFooter();
}

Checker::~Checker(){}