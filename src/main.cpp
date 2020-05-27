#include "BWT_encode.h"
#include "BWT_decode.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

struct operation
{
  string algorithm;
  string inputFile;
  string outputFile;
  bool encoding;
};

void usage();
void copyright();
operation arg_validations(int argc, char *argv[]);

int main(int argc, char *argv[])
{

  operation o = arg_validations(argc, argv);
  string inputText = "";
  string line;
  ifstream infile;
  infile.open(o.inputFile, ios::in | ios::binary);
  if (!infile.is_open())
  {
    cout << "couldn't open input file\n";
    return -1;
  }
  while (getline(infile, line))
    inputText += (line + "\n");
  inputText.pop_back();

  string outputText;
  if (o.encoding)
  {
    if (o.algorithm == "bwt")
      outputText = BWTencode(inputText);
  }
  else
  {
    if (o.algorithm == "bwt")
      outputText = BWTdecode(inputText);
  }

  ofstream ofile;
  ofile.open(o.outputFile, ios::out | ios::binary);
  if (!ofile.is_open())
  {
    cout << "couldn't open output file\n";
    return -1;
  }
  ofile << outputText;
  ofile.close();
  if (o.algorithm == "lzw")
    cout << "Compression Ratio = " << inputText.size() * 1.0 / outputText.size() << endl;
  return 0;
}

void usage()
{
  cerr << "\nEncoding Usage: Algorithm -e infile outfile\n";
  cerr << "Decoding Usage: Algorithm -d infile outfile\n";
  cerr << "where Algorithms supported are {bwt, mft, lzw}\n";
}

void copyright()
{
  cerr << "\n :: modified Bzip2 file compressor, Muhammad Ahmad Hesham, 2020\n";
}

operation arg_validations(int argc, char *argv[])
{
  if (argc != 5)
  {
    usage();
    copyright();
    exit(0);
  }

  if (strcmp(argv[1], "bwt") && strcmp(argv[1], "mft") && strcmp(argv[1], "lzw"))
  {
    usage();
    copyright();
    exit(0);
  }

  if (strcmp(argv[2], "-e") && strcmp(argv[2], "-d"))
  {
    usage();
    copyright();
    exit(0);
  }

  return operation{argv[1], argv[3], argv[4], argv[2][1] == 'e'};
}
