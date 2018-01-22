/*
  sum integers from file, one integer per line
*/
#include <iostream>
#include <fstream>
#include <string>

int fsum(char* filename)
{
  std::fstream f(filename);
  int sum = 0;

  std::string line;
  if(f.is_open())
  {
    while(getline(f,line))
    {
      sum += std::stoi(line);
    }
    return sum;
  }
  else // throw exception next time to-do
  {
    std::cout << "File not found or empty" <<'\n';
    return 0;
  }
}

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    cout << "Usage: sum-filenums <filename>" << endl;
    return -1;
  }
  else
  {
    char* filename = argv[1];

    cout <<"Sum = " << fsum(filename) << endl;
    return 0;
  }
}