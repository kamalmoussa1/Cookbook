/*
  To reverse only alphabet through a string 
*/
#include <iostream>
#include <string>

std::string reverse_str(std::string str)
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

bool check(char c)
{
  return (c >= 'a' && c<= 'z') || (c>='A' && c<='Z') || (c == ' ')? true : false;
}

std::string reverse_alpha(std::string str) // O(n^2)
{
  std::string r_str;
  std::string word; 
  for(int i =0; i < str.length() ; i++)
  {
    if(check(str[i]))
    {
      word += str[i];
    }
    else 
    {   
      r_str += reverse_str(word) + str[i];
      word = "";
    }
  }
  r_str += reverse_str(word);
  return r_str;
}

using namespace std;

int main()
{
  string s1 = "abcdef^jhi*jk@lmno!pq&";
  string s2 = "lam#ak";
  string s3 = "Hello World";


  cout << reverse_alpha(s1) << endl;
  cout << reverse_alpha(s2) << endl;
  cout << reverse_alpha(s3) << endl;
}

