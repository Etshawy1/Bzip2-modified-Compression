#include "BWT_decode.h"

string invert(string &bwt_arr, long long index)
{
  int len_bwt = bwt_arr.size();
  vector<unsigned char> sorted_bwt(len_bwt);
  for (size_t i = 0; i < len_bwt; i++)
    sorted_bwt[i] = (reinterpret_cast<unsigned char &>(bwt_arr[i]));

  vector<int> l_shift;

  // Index at which original string appears
  // in the sorted rotations list
  unsigned int x = index;

  // Sorts the characters of bwt_arr[] alphabetically
  sort(sorted_bwt.begin(), sorted_bwt.end());

  // vector of vectors created to compute l_shift[]
  vector<vector<int>> arr(256);
  vector<int> pos(256, 0);

  // Takes each distinct character of bwt_arr[] as head
  // of a vector and appends to it the index at which
  // character occurs in bwt_arr[]
  for (size_t i = 0; i < len_bwt; i++)
  {
    arr[reinterpret_cast<unsigned char &>(bwt_arr[i])].push_back(i);
  }

  // Takes each distinct character of sorted_arr[] as head
  // of a vector and finds l_shift[]
  for (size_t i = 0; i < len_bwt; i++)
  {
    unsigned char currentChar = reinterpret_cast<unsigned char &>(sorted_bwt[i]);
    l_shift.push_back(arr[currentChar][pos[currentChar]++]);
  }

  // Decodes the bwt

  string s(len_bwt, '.');
  for (size_t i = 0; i < len_bwt; i++)
  {
    x = l_shift[x];
    s[i] = bwt_arr[x];
  }
  s.pop_back();
  return s;
}

string BWTdecode(string &t)
{
  int indexTerminatingChar = t.find("\n");
  string s_index = t.substr(0, indexTerminatingChar);
  int index = stoi(s_index, nullptr, 10);
  t = t.substr(indexTerminatingChar + 1);
  return invert(t, index);
}
