#include "LZW_decode.h"

string decoding(vector<unsigned int> inputIndeces)
{
  unordered_map<unsigned int, string> dictionary;
  for (int i = 0; i <= 255; i++)
    dictionary[i] = string(1, char(i));

  int old = inputIndeces[0];
  int currentIndex;
  string s = dictionary[old];
  string c = "";
  string decodedOutput = "";
  c += s[0];
  decodedOutput += s;
  int count = 256;
  for (int i = 0; i < inputIndeces.size() - 1; i++)
  {
    currentIndex = inputIndeces[i + 1];
    if (dictionary.find(currentIndex) == dictionary.end())
    {
      s = dictionary[old];
      s += c;
    }
    else
    {
      s = dictionary[currentIndex];
    }
    decodedOutput += s;
    c = "";
    c += s[0];
    dictionary[count] = dictionary[old] + c;
    count++;
    old = currentIndex;
  }
  return decodedOutput;
}

string LZWdecode(string s)
{

  vector<unsigned int> indeces(s.size() / BYTES_PER_INDEX);
  unsigned int newIndex = 0;
  for (size_t i = 0; i < s.size(); i += BYTES_PER_INDEX)
  {
    newIndex = 0;
    for (size_t j = 0; j < BYTES_PER_INDEX; j++)
    {
      newIndex <<= 8;
      newIndex += reinterpret_cast<unsigned char &>(s[i + 2 - j]);
    }
    indeces[i / BYTES_PER_INDEX] = (newIndex);
  }
  return decoding(indeces);
}
