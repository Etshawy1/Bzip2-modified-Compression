#include "MTF_decode.h"

string MTFdecode(string enc)
{
  forward_list<char> symbolSet;
  for (size_t i = 0; i < 256; i++)
  {
    symbolSet.push_front(i);
  }

  vector<int> encoding(enc.size());
  for (size_t i = 0; i < enc.size(); i++)
  {
    encoding[i] = reinterpret_cast<unsigned char &>(enc[i]);
  }

  string source(encoding.size(), '.');
  int sourceIndex = 0;

  if (symbolSet.begin() != symbolSet.end())
  {
    for (auto index = encoding.begin(); index != encoding.end(); index++)
    {
      if (*index != 0)
      {
        auto symbol = next(symbolSet.begin(), (*index) - 1);
        auto nextSymbol = next(symbol, 1);

        //Append the symbol at index in the symbolSet to the source text
        source[sourceIndex++] = *nextSymbol;

        //Move the element at index to the front
        symbolSet.push_front(*nextSymbol);
        symbolSet.erase_after(symbol);
      }
      else
      {
        source[sourceIndex++] = *(symbolSet.begin());
      }
    }
  }

  return source;
}
