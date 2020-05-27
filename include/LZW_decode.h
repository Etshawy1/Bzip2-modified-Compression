#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <math.h>

#define BYTES_PER_INDEX 3

using namespace std;

vector<unsigned int> decoding(string &s);
string LZWdecode(string &s);
