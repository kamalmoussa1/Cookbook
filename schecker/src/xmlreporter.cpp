#include "xmlreporter.h"

XMLReporter::XMLReporter(std::ostream & os) 
              : Reporter(os)
  {
      
  }

  void XMLReporter::reportHeader()
  {

  }

  void XMLReporter::reportError(const std::string & word,
                  const std::string & context,
                  unsigned int line,
                  const std::string & filename)
  {

  }

  void XMLReporter::reportFooter()
  {

  }