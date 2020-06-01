# Bzip2 modified algorithm

A file compression tool that implements BWT, MTF, LZW algorithms.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

you need to have `g++` compiler and `make` installed on your machine.

### Building the code

enter either of the following commands

    make

### Usage

    Encoding Usage: {Algorithm} -e infile outfile
    Decoding Usage: {Algorithm} -d infile outfile

    where Algorithms supported are {bwt, mft, lzw, combo}
    combo does (bwt then mft then lzw) for encoding and reverse order for decoding

### Example

    ./bin/main combo -e enwik8 encoded.bin

    ./bin/main combo -d encoded.bin decoded.txt

## License

Licensed under the [MIT License](./License).

## Acknowledgments

I used the help of this research paper:

`Kärkkäinen, Juha & Sanders, Peter & Burkhardt, Stefan. (2006). Linear work suffix array construction. J. ACM. 53. 918-936. 10.1145/1217856.1217858.`

to implement the suffix array for `BWT` in `O(n)` instead of other easier solutions like `O(nlogn)` as the algorithm is used for files around hudreds of megabytes which would take much time.
