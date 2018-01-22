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
  return (c >= 'a' && c<= 'z') || (c>='A' && c<='Z')? true : false;
}

std::string reverse_alpha(std::string str) // O(n)
{
  std::string r_str;
  for(int i =0; i < str.length() ; i++)
  {
    if(check(str[i]))
    {
      r_str += str[i];
    }
  }

  r_str = reverse_str(r_str);

  int j =0;
  for(int i =0; i < str.length() ; i++)
  {
    if(check(str[i]))
    {
      str[i] = r_str[j];
      j++;
    }
  }
  return str;
}

// better- traverse n/2
std::string reverse_alpha_2(std::string  str)
{
  int i = 0;
  int j = str.length() -1;

  while(i<j)
  {
    if(!check(str[i]))
      i++;
    else if(!check(str[j]))
      j--;
    else
    {
      //std::swap(str[i], str[j]);
      // OR
      char t = str[i];
      str[i] = str[j];
      str[j] = t;
      i++;
      j--;
    }
  }
  return str;
}

using namespace std;

int main()
{
  string s1 = "abcdef^jhi*jk@lmno!pq&";
  string s2 = "lam#ak";
  string s3 = "Hello World";


  cout << reverse_alpha_2(s1) << endl;
  cout << reverse_alpha(s1)   << endl;
  cout << reverse_alpha_2(s2) << endl;
  cout << reverse_alpha(s2)   << endl;
  cout << reverse_alpha_2(s3) << endl;
  cout << reverse_alpha(s3)   << endl;

}

