#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Structure to store info of a node of
// linked list
struct node
{
  int data;
  node *next;
  node(int d, node *n) : data(d), next(n) {}
  node()
  {
    next = nullptr;
  }
};

void addAtLast(node **head, node **tail, node *nn);
void computeLShift(node **head, int index, int *l_shift);
string invert(string &bwt_arr, long long index);
string BWTdecode(string t);
