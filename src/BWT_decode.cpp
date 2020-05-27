#include "BWT_decode.h"

// Does insertion at end in the linked list
void addAtLast(node **head, node **tail, node *nn)
{
  if (*head == nullptr)
  {
    *head = nn;
    *tail = nn;
    return;
  }

  /*node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    */
  (*tail)->next = nn;
  (*tail) = nn;
}

// Computes l_shift[]
void computeLShift(node **head, int index, int *l_shift)
{
  l_shift[index] = (*head)->data;
  (*head) = (*head)->next;
}

string invert(string &bwt_arr, long long index)
{
  int len_bwt = bwt_arr.size();
  vector<unsigned char> sorted_bwt;
  for (size_t i = 0; i < bwt_arr.size(); i++)
  {
    sorted_bwt.push_back(reinterpret_cast<unsigned char &>(bwt_arr[i]));
  }

  int *l_shift = new int[len_bwt];
  // Index at which original string appears
  // in the sorted rotations list
  long long x = index;

  // Sorts the characters of bwt_arr[] alphabetically
  sort(sorted_bwt.begin(), sorted_bwt.end());

  // Array of pointers that act as head nodes
  // to linked lists created to compute l_shift[]
  node **arr = new node *[256];
  node **tails = new node *[256];

  for (size_t i = 0; i < 256; i++)
  {
    arr[i] = nullptr;
  }
  // Takes each distinct character of bwt_arr[] as head
  // of a linked list and appends to it the new node
  // whose data part contains index at which
  // character occurs in bwt_arr[]
  for (size_t i = 0; i < len_bwt; i++)
  {
    node *nn = new node(i, nullptr);
    addAtLast(&arr[reinterpret_cast<unsigned char &>(bwt_arr[i])], &tails[reinterpret_cast<unsigned char &>(bwt_arr[i])], nn);
  }
  // Takes each distinct character of sorted_arr[] as head
  // of a linked list and finds l_shift[]
  for (size_t i = 0; i < len_bwt; i++)
    computeLShift(&arr[reinterpret_cast<unsigned char &>(sorted_bwt[i])], i, l_shift);

  // Decodes the bwt

  string s = "";
  for (size_t i = 0; i < len_bwt; i++)
  {
    x = l_shift[x];
    s += bwt_arr[x];
  }
  delete[] l_shift;
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
