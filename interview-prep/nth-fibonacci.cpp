#include <iostream>

using namespace std;

 // recursion will limit this at larger numbers
int find_nth(int n)
{
  if( n == 0 )
    return 0;
  else if(n == 1)
    return 1;
  else
    return find_nth(n-1) + find_nth(n-2); 
}

// traditional 
int find_nth_2(int n)
{
  /* Initial values */
    int a = 1;
    int b = 0;
    int c;
    
    /* Calculate the sequence untill the Nth number */
    for (int i = 0; i <n; i++)
    {
        c = a + b;        
        a = b;
        b = c;
    }
    return c; // return the desired number 
}

// DP
int find_nth_3(int n)
{
  int fib[n];

  fib[0] = 0;
  fib[1] = 1;

  for(int i= 2 ; i < n+1 ; i++)
  {
    fib[i] = fib[i-1] + fib[i-2];
  }

  return fib[n];

}

int main()
{
  cout<<"what number? " << endl;
  int n;
  
  while(cin >> n) // -1 terminates 
  {
    if(n==-1) break;
    cout << find_nth_3(n) << " ";

  }

  return 0;
}
