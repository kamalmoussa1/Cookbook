#ifndef XMLREPORTER_H
#define XMLREPORTER_H

#include "reporter.h"

class XMLReporter : public Reporter
{
    public:
  
        XMLReporter(std::ostream & os);

        void reportHeader();
        void reportError( const std::string & word,
                        const std::string & context,
                        unsigned int line,
                        const std::string & filename );
        void reportFooter();


};

#endif