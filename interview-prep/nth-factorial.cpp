/*
  Find factorial of N
*/

#include <iostream>

int factorial(int n)
{
  if(n == 0) 
    return 1;
  else
    return n*factorial(n-1);
}

using namespace std;


int main()
{

  cout << "Enter a number: " << endl;
  int n;

  while(cin >> n)
  {
    if(n >= 0)
      cout << factorial(n) << " ";
    else
    break;
  }

  return 0;

}