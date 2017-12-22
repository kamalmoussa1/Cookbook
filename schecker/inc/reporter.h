#ifndef REPORTER_H
#define REPORTER_H

#include <iostream>

// abstract class 

class Reporter {

    public:
        
        Reporter( std::ostream & os ) : mOut( os ) {}
        
        /*
            These functions are declared as virtual, which means that they will behave polymorphically
            and as pure (using the somewhat strange =0 syntax)  which means that derived classes must provide implementations.
            Any class that has one or more pure virtual functions is said to be an abstract base class.
        */
        
        virtual void reportHeader() = 0;
        virtual void reportError( const std::string & word,
                                  const std::string & context,
                                  unsigned int line,
                                  const std::string & filename ) = 0;
        virtual void reportFooter() = 0;

        virtual ~Reporter() {}

    // gives access to the derived classes 
    protected:
    
        std::ostream & Out()
        {
            return mOut;
        }

    private:

        std::ostream & mOut;

};

#endif