#ifndef CSVREPORTER_H
#define CSVREPORTER_H

#include "reporter.h"

class CSVReporter : public Reporter
{

  public:

    CSVReporter( std::ostream & os );

    void reportHeader();
    void reportError( const std::string & word,
                      const std::string & context,
                      unsigned int line,
                      const std::string & filename );
    void reportFooter();

    ~CSVReporter();


};

#endif