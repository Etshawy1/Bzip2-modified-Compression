#include "LZW_encode.h"

vector<unsigned int> encoding(string &s)
{
  unordered_map<string, unsigned int> dictionary;
  vector<unsigned int> output_code;
  for (int i = 0; i <= 255; i++)
    dictionary[string(1, char(i))] = i;

  string oldChars = "";
  string newChars = "";
  oldChars += s[0];
  unsigned int code = 256;
  for (int i = 0; i < s.length(); i++)
  {
    if (i != s.length() - 1)
      newChars += s[i + 1];
    if (dictionary.find(oldChars + newChars) != dictionary.end())
    {
      oldChars += newChars;
    }
    else
    {
      output_code.push_back(dictionary[oldChars]);
      dictionary[oldChars + newChars] = code;
      oldChars = newChars;
      code++;
    }
    newChars.clear();
  }
  output_code.push_back(dictionary[oldChars]);
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
