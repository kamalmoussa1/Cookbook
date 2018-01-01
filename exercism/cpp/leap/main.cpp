#include <iostream>
#include "leap.h"

using namespace std;
int main(int argc, char* argv[])
{
  int year;
  cout << "What year?   ";

  while(cin >> year) // (not int or -1 = terminate )
  {
    if(year == -1) break;

    if (leap::is_leap_year(year))
        cout << "A leap year!" << endl;
    else
      cout << "Not a leap year!" << std::endl;
  }

  cout << "Bye!" << endl;

  return 0; 
}