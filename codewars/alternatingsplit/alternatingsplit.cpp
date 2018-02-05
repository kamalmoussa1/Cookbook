#include "alternatingsplit.h"

#include <iostream>
#include <string>

#define log(x) (std::cout << x << std::endl)


std::string encrypt(std::string text, int n)
{
  if(text.empty())
    return NULL;

  if( n <= 0)
    return text;

  std::string evenText;
  std::string oddText;
  std::string encryptedText;


  for(int i = 0; i < text.length(); i++)
  {
    i%2 ? oddText.push_back(text[i]) : evenText.push_back(text[i]);
  }

  encryptedText = oddText + evenText;
  
  if(n != 1)
    encryptedText = encrypt(encryptedText, n-1);

  return encryptedText;
}


std::string decrypt(std::string encryptedText, int n )
{
  if(encryptedText.empty())
    return NULL;

  if( n <= 0)
    return encryptedText; 

  int len = encryptedText.length();
  int pivot =len/2;

  std::string decryptedText;
  
  for(int i=0, j = pivot; i < pivot ;)
  {
    decryptedText += encryptedText[j];
    decryptedText += encryptedText[i];
    i++;
    j++;

  }

  if(encryptedText.length()%2 != 0)
    decryptedText += encryptedText[len-1];

  if(n != 1)
    decryptedText = decrypt(decryptedText, n-1);

  return decryptedText;
}

