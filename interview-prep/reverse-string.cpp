/*
  Reverse a given string 
*/ 
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

// using a stack - O(n)
std::string reverse_str(std::string str)
{
  std::stack<char> st;

  for(int i=0; i< str.length(); i++)
  {
    st.push(str[i]);
  }

  std::string r_str;
  while(!st.empty())
  {
    r_str += st.top();
    st.pop();
  }
  return r_str;
}

// copy backword into another string- O(n)
std::string reverse_str_2(std::string str)
{
  std::string r_str; 
  for(int i = str.length(); i >= 0; i--)
  {
    r_str += str[i];
  }

  return r_str;
}

// copy forward into another string - O(n)
std::string reverse_str_3(std::string str)
{
  std::string r_str; 
  for(int i =0; i < str.length() ; i++)
  {
    r_str = str[i] + r_str;
  }

  return r_str;
}

// using built-in reverse  - O(n)
std::string reverse_str_4(std::string str)
{
  std::reverse(str.begin(), str.end());
  return str;
}

// traverse half of the string - n/2 
std::string reverse_str_5(std::string str)
{
  int i = 0;
  int j = str.length() -1;

  while(i<=j)
  {
    //std::swap(str[i], str[j]);
    // OR
    char t = str[i];
    str[i] = str[j];
    str[j] = t;
    i++;
    j--;
  }
  return str;
}

using namespace std;
int main()
{
  string ss = "Hello world";

  cout << reverse_str(ss)   << endl;
  cout << reverse_str_2(ss) << endl;
  cout << reverse_str_3(ss) << endl;
  cout << reverse_str_4(ss) << endl;
  cout << reverse_str_5(ss) << endl;

  return 0;
}