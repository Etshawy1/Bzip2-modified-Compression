#include "BWT_decode.h"

string invert(string &BWTArray, long long index)
{
  int BWTLength = BWTArray.size();
  vector<unsigned char> BWTSortedArray(BWTLength);
  for (size_t i = 0; i < BWTLength; i++)
    BWTSortedArray[i] = (reinterpret_cast<unsigned char &>(BWTArray[i]));

  vector<int> shift;

  // Index at which the terminating character occurs
  unsigned int x = index;

  // Sorts the characters of BWTArray[] alphabetically
  sort(BWTSortedArray.begin(), BWTSortedArray.end());

  // vector of vectors created to compute shift[]
  vector<vector<int>> arr(256);
  vector<int> pos(256, 0);

  for (size_t i = 0; i < BWTLength; i++)
    arr[reinterpret_cast<unsigned char &>(BWTArray[i])].push_back(i);

  // Takes each distinct character of sorted_arr[] as head
  // of a vector and finds shift[]
  for (size_t i = 0; i < BWTLength; i++)
  {
    unsigned char currentChar = BWTSortedArray[i];
    shift.push_back(arr[currentChar][pos[currentChar]++]);
  }

  // Decodes the bwt
  string s(BWTLength, '.');
  for (size_t i = 0; i < BWTLength; i++)
  {
    x = shift[x];
    s[i] = BWTArray[x];
  }
  s.pop_back();
  return s;
}

string BWTdecode(string t)
{
  int indexTerminatingChar = t.find("\n");
  string s_index = t.substr(0, indexTerminatingChar);
  int index = stoi(s_index, nullptr, 10);
  t = t.substr(indexTerminatingChar + 1);
  return invert(t, index);
}
