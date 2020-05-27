#pragma once

#include <string>

using namespace std;

inline bool leq(int a1, int a2, int b1, int b2); // lexicographic order
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3);
static void radixPass(int *a, int *b, int *r, int n, int K);
void suffixArray(int *T, int *SA, int n, int K);
string BWTencode(string &t);
