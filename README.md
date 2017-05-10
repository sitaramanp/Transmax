Solution to the grade sorting problem in C++

A unit test generator program, that would generate random names and grades is also submitted.

program is compiled using: 
g++ -pipe -O2 -std=c++11 unitTestGenerator.cpp . Output of this this is used for generating testcases. One original file and a shuffled file is generated. Shuffled file is given to the gradeSorter program which should give
output similar to the one in original. It can be compared using something like diff utility.

g++ -pipe -O2 -std=c++11 gradeSorter.cpp . Output of this is the grade sorter executable

