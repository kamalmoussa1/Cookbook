#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "checkererror.h"

Dictionary::Dictionary(const std::string & fname)
{
    // variables    
    std::string word;


    // read data
    ifstream wList(fname.c_str()); // stream constructor must be char*, so c_str comes in
    // check
    if (!wList.is_open())
    {
        // report an error
        // cout << "It's weird, something is wrong with this file" << endl;
        throw CheckerError("Coudn't open dictionary file: " + fname);
    }
    if(wList.peek() == ifstream::traits_type::eof())
    {
        throw CheckerError("Dictionary fil is empyty, checking terminated! \n");
    }
    cout << "Reading from the dictionary.. \n";

    //EOF triggering terminates the loop, otherwise report an error
    while (getline(wList, word)) 
    {
        //insert words into a set of unique words
        wordSet.insert(word);
        cout <<"\t" << " Adding to the list: " << word << "\n";
    }

    // check
    if (!wList.eof())
    {
        // report read error
        throw CheckerError("Error reading dictionary file: " + fname);
    }
    cout << "---------------------------------------------------- \n\n";
}

bool Dictionary::Check(const std::string & word)const    
{
    // If the word is not found, the find() function returns an iterator
    // which points to the end() of the set, which is a special, unused value.
    return wordSet.find(word) != wordSet.end();

}

Dictionary::~Dictionary(){}