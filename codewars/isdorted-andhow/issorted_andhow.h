#ifndef ISSORTEDANDHOW_H
#define ISSORTEDANDHOW_H

#include <vector>
#include <string>

namespace WARS
{
  std::string isSortedAndHow(std::vector<int> array)
  {
    if(array.empty())
      return "";

    int asCount  = 0;
    int desCount = 0;

    for(int i = 0; i < array.size() -1; i++)
    {
      if( array[i] <= array[i+1])
        asCount++;
      else
        desCount++;

      if(asCount && desCount) // both condetions are met, so it's not sorted, return no
        return "no";    
    }
    if(asCount)
      return "yes, ascending";
    else 
      return "yes, descending";
  }
}

#endif