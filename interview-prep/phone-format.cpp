/*
  This program checks the format of phone numbers set from txt file. It checks against two 
  different formats: (xxx) xxx-xxxx or xxx-xxx-xxxx. (x means a digit)

*/

#include <iostream>
#include <string>
#include <fstream>

bool is_digit(std::string line)
{
  int count = 0;
  for(char c : line)
  {
    if(std::isdigit(c))
        count++;
  }

  if(count == 10)
    return true;
  else
    return false;
}


void check_format(char* filename)
{
  std::fstream f(filename);

  if(f.is_open())
  {

    std::ofstream phones("data/valid-contacts.txt",std::ios::out); // create a file to store vaild numbers 
    std::string line;

    while(getline(f,line))
    {
        // 1st check: leading or trailing white spaces.
      if( ( *line.begin() == ' ' ) || ( *(line.end()-1) == ' ') )
      {
        // std::cout <<"white space\n"; 
        continue;
      } 
        // 2nd check: length of string 

      else if (line.length() == 12) // format 1
      {
        if(line[3] == '-' && line[7] == '-')
          if(is_digit(line))
             phones << line << std::endl;
      }

      else if (line.length() == 14) // format 2
      {
        if(line[0] == '(' && line[4] == ')' && line[9] == '-')
          if(is_digit(line))
            phones << line << std::endl;  
      }
      else
        continue;
    }

  }
  else
    std::cerr << "Can't open " << filename << std::endl;

}


using namespace std;

int main(int argc, char* argv[])
{

 if(argc < 2)
  {
    cout << "Usage: phone-format <filename>" << endl;
    return -1;
  }
  else
  {
    char* filename = argv[1];

    check_format(filename);
    return 0;
  }
}


