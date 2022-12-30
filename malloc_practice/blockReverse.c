/* Project5: Create a list of integers, devides the list into a number of segments, and display each segment in reverse order */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printBackward(int* x, int givenLength)
{
    //for length of array, print content of array from end to 0 index - on same line
    int i;
    for(i = ( givenLength - 1); i >= 0; i--) { printf("%d, ", x[i]); }

    //do println to push the cursor to next line
    printf("\n");

}


void printForward(int* x, int givenLength)
{
    //for length of array, print content of array from 0 to end index - on same line
    int i;
    for(i = 0; i < givenLength; i++) { printf("%d, ", x[i]); }

    //do println to push the cursor to next line
    printf("\n\n");

}


int main()
{

    //pointers for int storages//
    int* a;
    int* b;

    //int storage length values//
    int a_length, b_length;


    //prepare a randomizer (with seed)
    srand(time(0));


    //obtain possible lenth value for a: pick a random number between 0~9 and add 90
    //do same for b: pick a random number between 0~9 and add 10
    a_length = ( rand() % 10 ) + 90;
    b_length = ( rand() % 10 ) + 10;


    //increase the size of size of a until the size of a is divisible by b
    while ( (a_length % b_length) != 0) { a_length++; }


    //allocate memory for a and b by using the numbers obtained above
    a = (int*)malloc(a_length * sizeof(int));
    b = (int*)malloc(b_length * sizeof(int));


    //fill up a with random numbers between 0~9
    int i1;
    for(i1 = 0; i1 < a_length; i1++){ a[i1] = rand() % 10; }


    //printforward()
    printForward(a, a_length);


    //for the length of a
    //  1) copy a portion of data from a to b, starting from 0 index
    //  2) feed b to printbackward()
    //  3) increase index of a to the length of b

    int i2, i3;
    for(i2 = 0; i2 < a_length; i2 += b_length)
    {
        for (i3 = 0; i3 < b_length; i3++) { b[i3] = a[i2 + i3]; }

        printBackward(b, b_length);
    }


    //end program
    return 0;

}

