#include "BWT_encode.h"
#include "BWT_decode.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;
using namespace std::chrono;
ifstream inputFile;
ofstream ofile;

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
string readInput(string filename);
string execute(bool encoding, string algorithm, string &inputText);
void writeOutput(string filename, string &outputText);

int main(int argc, char *argv[])
{

  operation o = arg_validations(argc, argv);
  string inputText = readInput(o.inputFile);
  string outputText = execute(o.encoding, o.algorithm, inputText);
  writeOutput(o.outputFile, outputText);

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
    exit(-2);
  }
  if (strcmp(argv[1], "bwt") && strcmp(argv[1], "mft") && strcmp(argv[1], "lzw"))
  {
    usage();
    copyright();
    exit(-2);
  }
  if (strcmp(argv[2], "-e") && strcmp(argv[2], "-d"))
  {
    usage();
    copyright();
    exit(-2);
  }
  return operation{argv[1], argv[3], argv[4], argv[2][1] == 'e'};
}

string readInput(string filename)
{
  string inputText = "";
  string line = "";
  inputFile.open(filename, ios::in | ios::binary);
  if (!inputFile.is_open())
  {
    cout << "couldn't open input file\n";
    exit(-1);
  }
  cout << "reading input from file...\n";
  while (getline(inputFile, line))
    inputText += (line + "\n");
  inputText.pop_back();
  inputFile.close();
  return inputText;
}

string execute(bool encoding, string algorithm, string &input)
{
  // Get starting timepoint
  auto start = high_resolution_clock::now();
  string outputText = "";
  cout << "executing algorithm...\n";
  if (encoding)
  {
    if (algorithm == "bwt")
      outputText = BWTencode(input);
  }
  else
  {
    if (algorithm == "bwt")
      outputText = BWTdecode(input);
  }
  // Get ending timepoint
  auto stop = high_resolution_clock::now();
  // Get duration. Substart timepoints to
  // get durarion. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<milliseconds>(stop - start);

  cout << "Time taken by algorithm: "
       << duration.count() << " milliseconds" << endl;

  return outputText;
}

void writeOutput(string filename, string &outputText)
{
  ofile.open(filename, ios::out | ios::binary);
  if (!ofile.is_open())
  {
    cout << "couldn't open output file\n";
    exit(-1);
  }
  cout << "writing output to file...\n";
  ofile << outputText;
  ofile.close();
}
