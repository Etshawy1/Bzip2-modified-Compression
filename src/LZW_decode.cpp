#include "LZW_decode.h"

string decoding(vector<unsigned int> op)
{
  unordered_map<unsigned int, string> table;
  for (int i = 0; i <= 255; i++)
  {
    string ch = "";
    ch += char(i);
    table[i] = ch;
  }
  int old = op[0], n;
  string s = table[old];
  string c = "";
  string decodedOutput;
  c += s[0];
  decodedOutput += s;
  int count = 256;
  for (int i = 0; i < op.size() - 1; i++)
  {
    n = op[i + 1];
    if (table.find(n) == table.end())
    {
      s = table[old];
      s = s + c;
    }
    else
    {
      s = table[n];
    }
    decodedOutput += s;
    c = "";
    c += s[0];
    table[count] = table[old] + c;
    count++;
    old = n;
  }
  return decodedOutput;
}

string LZWdecode(string &s)
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
