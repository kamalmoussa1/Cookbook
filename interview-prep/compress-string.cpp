//Given a string for example "aabbbddf" write a function to compress that string to "a2b3d2f1"

#include <iostream>
#include <string>
using namespace std;


string compress_str(string str)
{
  string out_str;
  int count = 1;
 
  if (str.size() < 2)
    return str + to_string(1);

  int i = 0;
  while(i < str.size())
  {
    int j = i;
    while(str[i] == str[j+1] && j < str.size())
    {
      count++;
      j++;
    }
    out_str += str[i] + to_string(count);
    i += count;
    count = 1;
  }  
  return out_str;
}


int main() 
{
  string a = "aaaa";
  string b = "ahhakkaaa";
  string c = "abcd";

  cout << compress_str(a) << endl;
  cout << compress_str(b) << endl;
  cout << compress_str(c) << endl;

  return 0;
}
