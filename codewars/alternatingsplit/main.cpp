#include "alternatingsplit.h"

#include <iostream>
#include  <string>

using namespace std;


int main()
{

  cout << decrypt(encrypt("This is a test!", 1), 1) << endl; //, Equals("This is a test!")
  cout << decrypt(encrypt("This is a test!", 4), 4) << endl; //, Equals("This is a test!")
  cout << decrypt(encrypt("This is a test",  3), 3) << endl; //, Equals("This is a test!")

  return 0;
}