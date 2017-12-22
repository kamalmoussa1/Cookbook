#include "csvreporter.h"

using std::string;

// you do not want it to be used outside of this specific .cpp file.
// it's not necassery to be a class member as it doesn't use any of its members
static string ToCSV(const string & s) 
{
    string csv;
    for (unsigned int i = 0; i < s.size(); ++i) 
    {
        if (s[i] == '"') 
        {
            csv += '"';
        }
        csv += s[i];
    }
    return '"' + csv + '"';
}

CSVReporter::CSVReporter(std::ostream & os) 
      : Reporter( os ) {
}

void CSVReporter::reportHeader() {
     Out() << "word,context,line,file\n";
}

void CSVReporter::reportError( const string & word,
                                 const string & context,
                                 unsigned int line,
                                 const string & filename ) {
    Out() << ToCSV( word ) << ","
	  << ToCSV( context ) << ","
          << '"' << line << '"' << ","
          << ToCSV( filename ) << "\n";
}

void CSVReporter::reportFooter() {
   // nothing to do
}

CSVReporter::~CSVReporter(){}