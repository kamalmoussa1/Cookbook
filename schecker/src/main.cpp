#include <iostream>
#include <fstream>
#include <memory>

#include "checkererror.h"
#include "cmdline.h"
#include "settings.h"
#include "checker.h"

#include "minitest.h"
using namespace std;


int main(int argc, char *argv[])
{
    MINI_MAIN();
    cout << "------------------------------------ \n";
    cout << "Hello to my awesome CHECKER \n";
    cout << "------------------------------------ \n";

    
    try 
    {
        CmdLine cl(argc, argv);
        Settings s(cl);
        Checker ch;
        
        auto_ptr<Reporter> rep(ch.makeReporter(s.ReportType()));

        // costruct and load dictionary
        Dictionary dict(s.DictName());

        if(cl.Argc() == 1) //standard input 
        {
            ch.checkSubmission(dict, cin, "stdin", *rep);
        }
        else
        {
            for(int i = 1; i < cl.Argc(); i++)
            {
                // load submissions 
                ifstream sub(cl.Argv(i).c_str());
                // check
                if(!sub.is_open())
                {
                    throw CheckerError("Can't open this file: " + cl.Argv(i));    
                }

                ch.checkSubmission(dict, sub, cl.Argv(i), *rep);
                cout << "-------------------------------------\n";
            }
        }       
    }
    catch(const CheckerError & e) // my custom exception
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    catch(...) // any other exceptions
    {
        cerr << "Error: Unknown exception." << endl;
        return 2;
    }


}