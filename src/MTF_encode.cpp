#include "MTF_encode.h"

string MTFencode(string &source)
{
  forward_list<char> alphabet;
  for (size_t i = 0; i < 256; i++)
  {
    alphabet.push_front(i);
  }
  vector<int> encoding;

  //Parameter checking
  if (alphabet.begin() != alphabet.end())
  {
    for (string::iterator c = source.begin(); c != source.end(); c++)
    {
      //Search the alphabet for the index of the letter in source
      int index = 0;
      bool found = false;
      forward_list<char>::iterator character = alphabet.begin();
      forward_list<char>::iterator next_character = next(alphabet.begin(), 1);

      if (*character != *c)
      {
        while (!found && next_character != alphabet.end())
        {
          index++;
          if (*next_character == *c)
          {
            found = true;
          }
          else
          {
            character++;
            next_character++;
          }
        }
        //Move the element at index to the front of the list
        alphabet.erase_after(character);
        alphabet.push_front(*c);
      }
      //Add the index to the integer sequence encoding
      encoding.push_back(index);
    }
  }
  string s(encoding.size(), '.');
  for (size_t i = 0; i < encoding.size(); i++)
  {
    s[i] = char(encoding[i]);
  }

  return s;
}
