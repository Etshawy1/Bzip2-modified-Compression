#include "MTF_decode.h"

string MTFdecode(string enc)
{

  cout << enc.size() << endl;
  forward_list<char> alphabet;
  for (size_t i = 0; i < 256; i++)
  {
    alphabet.push_front(i);
  }

  vector<int> encoding(enc.size());
  for (size_t i = 0; i < enc.size(); i++)
  {
    encoding[i] = reinterpret_cast<unsigned char &>(enc[i]);
  }

  string source(encoding.size(), '.');
  int source_index = 0;

  if (alphabet.begin() != alphabet.end())
  {
    for (vector<int>::iterator index = encoding.begin(); index != encoding.end(); index++)
    {
      if (*index != 0)
      {
        forward_list<char>::iterator character = next(alphabet.begin(), (*index) - 1);
        forward_list<char>::iterator next_character = next(character, 1);

        //Append the character at index in the alphabet to the source text
        source[source_index++] = *next_character;

        //Move the element at index to the front
        alphabet.push_front(*next_character);
        alphabet.erase_after(character);
      }
      else
      {
        source[source_index++] = *(alphabet.begin());
      }
    }
  }

  return source;
}
