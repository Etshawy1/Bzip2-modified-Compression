#include "MTF_encode.h"

string MTFencode(string source)
{
  forward_list<char> symbolSet;
  for (size_t i = 0; i < 256; i++)
  {
    symbolSet.push_front(i);
  }
  vector<int> encoding;

  if (symbolSet.begin() != symbolSet.end())
  {
    for (auto it = source.begin(); it != source.end(); it++)
    {
      //Search the symbolSet for the index of the character
      int index = 0;
      bool found = false;
      auto symbol = symbolSet.begin();
      auto nextSymbol = next(symbolSet.begin(), 1);

      if (*symbol != *it)
      {
        while (!found && nextSymbol != symbolSet.end())
        {
          index++;
          if (*nextSymbol == *it)
            found = true;
          else
          {
            symbol++;
            nextSymbol++;
          }
        }
        symbolSet.erase_after(symbol);
        symbolSet.push_front(*it);
      }
      encoding.push_back(index);
    }
  }

  // convert the output to string to be written in file
  string s(encoding.size(), '.');
  for (size_t i = 0; i < encoding.size(); i++)
  {
    s[i] = char(encoding[i]);
  }

  return s;
}
