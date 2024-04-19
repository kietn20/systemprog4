// Kiet Nguyen
// CECS 325-02 Prog 3
// Prog 2 - Sorting Contest
// Due 3/12/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <stdlib.h> // for strtol
#include <fstream>

using namespace ::std;

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Error: Need 3 arguments\n";
        exit(1);
    }

    for (int i = 0; i < argc; i++)
    {
        cout << "argv[" << i << "]:" << argv[i] << endl;
    }

    fstream generateDatFile("numbers.dat", ios::out | ios::binary);
    if (!generateDatFile)
    {
        cerr << "Error: numbers.dat could not be created\n";
        exit(1);
    }

    int numbersToGenerate = strtol(argv[1], NULL, 10);
    int min = strtol(argv[2], NULL, 10);
    int max = strtol(argv[3], NULL, 10);

    srand(time(NULL));
    for (int i = 0; i < numbersToGenerate; i++)
    {
        int num = rand() % (max - min + 1) + min;
        generateDatFile << num << endl;
    }
}