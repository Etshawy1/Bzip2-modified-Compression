#include "LZW_encode.h"

vector<unsigned int> encoding(string &s)
{
  unordered_map<string, unsigned int> table;
  vector<unsigned int> output_code;
  for (int i = 0; i <= 255; i++)
  {
    string ch = "";
    ch += char(i);
    table[ch] = i;
  }

  string p = "", c = "";
  p += s[0];
  unsigned int code = 256;
  for (int i = 0; i < s.length(); i++)
  {
    if (i != s.length() - 1)
      c += s[i + 1];
    if (table.find(p + c) != table.end())
    {
      p = p + c;
    }
    else
    {
      output_code.push_back(table[p]);
      table[p + c] = code;
      code++;
      p = c;
    }
    c = "";
  }
  output_code.push_back(table[p]);
  return output_code;
}

string LZWencode(string s)
{
  vector<unsigned int> indeces = encoding(s);
  string outputString(BYTES_PER_INDEX * indeces.size(), '.');

  for (size_t i = 0; i < indeces.size(); i++)
  {
    unsigned int index = indeces[i];
    for (uint8_t j = 0; j < BYTES_PER_INDEX; j++) // 3 bytes for all indeces
    {
      char outChar = index % 256;
      index >>= 8;
      outputString[i * BYTES_PER_INDEX + j] = outChar;
    }
  }

  return outputString;
}
