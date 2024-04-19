// Kiet Nguyen
// CECS 325-02
// Prog 4 - Sorting Contest using pThreads
// Due 3/12/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace ::std;

struct bucket
{
    int *start;
    int size;
};

// Function Declarations
void bubble(int A[], int size);
void *bridge(void *ptr);
void merge(int a1[], int s1, int a2[], int s2);

int main(int argc, char **argv)
{
    if (argc != 3) // Checking for three command line arguments
    {
        cout << "Error: Please enter a input.txt file & an output.txt file.\n";
        exit(1);
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);
    if (!inputFile.is_open())
    {
        cout << "ERROR: Unable to open input file.\n";
        exit(1);
    }
    else if (!outputFile.is_open())
    {
        cout << "ERROR: Unable to open output file.\n";
        exit(1);
    }

    int *array = new int[1000000]; // Dynamic Array
    int n = 0;
    int num;
    while (inputFile >> num)
    {
        array[n++] = num;
    }
    // i--;

    // Creating Buckets
    struct bucket buckets[8];
    int bucketStartIndex = 0;
    for (int i = 0; i < 8; i++)
    {
        buckets[i].start = &array[bucketStartIndex];
        buckets[i].size = 125000;
        bucketStartIndex += 125000;
    }

    // Creating Threads
    pthread_t threads[8];
    for (int i = 0; i < 8; i++)
    {
        pthread_create(&threads[i], NULL, bridge, (void *)&buckets[i]);
    }

    // Join threads
    for (int i = 0; i < 8; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Merge Buckets
    int *ptr1 = array;
    int *ptr2 = array + 125000;
    merge(ptr1, 125000, ptr2, 125000);
    // cout << "---- finished merging bucket 1&2 ----\n";

    ptr1 = array + 250000;
    ptr2 = array + 375000;
    merge(ptr1, 125000, ptr2, 125000);
    // cout << "---- finished merging bucket 3&4 ----\n";

    ptr1 = array + 500000;
    ptr2 = array + 625000;
    merge(ptr1, 125000, ptr2, 125000);
    // cout << "---- finished merging bucket 5&6 ----\n";

    ptr1 = array + 750000;
    ptr2 = array + 875000;
    merge(ptr1, 125000, ptr2, 125000);
    // cout << "---- finished merging bucket 7&8 ----\n";

    // Merging 4 Buckets
    ptr1 = array;
    ptr2 = array + 250000;
    merge(ptr1, 250000, ptr2, 250000);
    // cout << "---- finished merging bucket 1&2 ----\n";

    ptr1 = array + 500000;
    ptr2 = array + 750000;
    merge(ptr1, 250000, ptr2, 250000);
    // cout << "---- finished merging bucket 3&4 ----\n";

    // Merging 2 Buckets
    ptr1 = array;
    ptr2 = array + 500000;
    merge(ptr1, 500000, ptr2, 500000);
    // cout << "---- finished merging bucket ALL ----\n";

    for (int k = 0; k < 1000000; k++)
    {
        outputFile << array[k] << endl;
    }

    inputFile.close();
    outputFile.close();
    delete[] array; // Deallocating dynamic array from heap
    return 0;
}

void bubble(int A[], int size)
{
    for (int i = 0; i < size-1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size-i-1; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
}

void *bridge(void *ptr)
{
    bucket *arg = (bucket *)ptr;
    bubble(arg->start, arg->size);
    return 0;
}

void merge(int *a1, int s1, int *a2, int s2)
{
    int temp[s1 + s2];

    int i = 0;
    int a1Index = 0;
    int a2Index = 0;
    while (a1Index < s1 && a2Index < s2) // Merging one by one
    {
        if (a1[a1Index] <= a2[a2Index])
        {
            temp[i] = a1[a1Index];
            a1Index++;
        }
        else if (a2[a2Index] < a1[a1Index])
        {
            temp[i] = a2[a2Index];
            a2Index++;
        }
        i++;
    }

    while (a1Index < s1)
    {
        temp[i] = a1[a1Index];
        a1Index++;
        i++;
    }

    while (a2Index < s2)
    {
        temp[i] = a2[a2Index];
        a2Index++;
        i++;
    }

    // Copies the merged temporary array back to original
    for (int j = 0; j < s1 + s2; j++)
    {
        a1[j] = temp[j];
    }
}