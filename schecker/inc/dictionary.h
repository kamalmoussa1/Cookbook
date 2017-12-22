#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <set>

class Dictionary
{
    private:
        std::set <std::string> wordSet;

    public:
        // Passing by reference to avoid copying overhead
        
        Dictionary(const std::string & fname);
        bool Check(const std::string & word) const;    

        virtual ~Dictionary();
};

#endif  