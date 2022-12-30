/* Project6: generate a random number in the range 0 ~ 10 for each process and display them while managing the process workload optimally (Lecture7, p.21) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mpi.h>



int main()
{
    //declare variables//
    int comm_sz, my_rank;
    int x, p;
    int sum = 0;


    //declare MPI assets//
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    //come up with a random number between 0 to 10
    srand(time(0) + my_rank);  //<-- CAUTION: if you don't seed by your rank, all process would have same random numbers
    x = rand() % 11;


    //if there is only one process, consider this run serial - only need to display current value and exit.
    //(TODO: confirm the process size?)
    if (comm_sz == 1)
    {
        printf("\nALL ENTRIES: \n%d\n", x);
        printf("\nSUM: %d\n", x);

        MPI_Finalize();
        return 0;
    }


    int MAX_STRING = (comm_sz * 3) + 1;
    char entriesView[MAX_STRING];


    //put each process to task
    int destination;
    int locator = comm_sz / 2;


    //NOTE: I originally had this section as a nested if-else but if I do that, garbage values were passed down to to string variable for unknown reason.
    //      Hence the current structure of if-else if-else.
    if(my_rank >= locator)
    {

        //if your rank is upper half of total processes, just send out string and send sum
        sprintf(entriesView, "%d", x);
        sum = sum + x;

        destination = my_rank - (comm_sz / 2);

        //printf("DEBUG: Top process %d sending away sum=%d to %d\n", my_rank, sum, destination);
        //printf("DEBUG: Top process %d sending away string=%s to %d\n", my_rank, entriesView, destination);

        MPI_Send(entriesView, strlen(entriesView)+1, MPI_CHAR, destination, 0, MPI_COMM_WORLD);
        MPI_Send(&sum, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);


    }
    else if (my_rank != 0)
    {

        char concatView[MAX_STRING];
        int newSum = x;

        sprintf(concatView, "%d", x);

        for(locator; locator > my_rank; locator = (locator / 2))
        {
            MPI_Recv(entriesView, MAX_STRING, MPI_CHAR, (locator + my_rank), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&sum, 1, MPI_INT, (locator + my_rank), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            sprintf(concatView, "%s,%s", concatView, entriesView);
            newSum = newSum + sum;

            //printf("DEBUG: Low process %d RECEIVED sum=%d\n", my_rank, sum);
            //printf("DEBUG: Low process %d RECEIVED string=%s (concatView=%s)\n", my_rank, entriesView, concatView);

        }

        sprintf(entriesView, "%s", concatView);
        sum = newSum;

        destination = my_rank - locator;

        //printf("DEBUG: Low process %d sending away sum=%d to %d\n", my_rank, sum, destination);
        //printf("DEBUG: Low process %d sending away string=%s to %d\n", my_rank, entriesView, destination);


        MPI_Send(entriesView, strlen(entriesView)+1, MPI_CHAR, destination, 0, MPI_COMM_WORLD);
        MPI_Send(&sum, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);

    }
    else
    {
        char finalString[MAX_STRING];
        int totalSum = x;

        sprintf(finalString, "%d", x);

        //printf("DEBUG: Process 0 currently has %s; locator value = %d\n", finalString, locator);


        for(locator; locator >= 1; locator = (locator / 2))
        {
            MPI_Recv(entriesView, MAX_STRING, MPI_CHAR, locator, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&sum, 1, MPI_INT, locator, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //printf("DEBUG: Process 0 received string from %d: %s\n", locator, entriesView);
            //printf("DEBUG: Process 0 received sum from %d: %d\n", locator, sum);

            sprintf(finalString, "%s,%s", finalString, entriesView);
            totalSum = totalSum + sum;

            //printf("DEBUG: locator=%d, sum=%d, totalsum=%d\n", locator, sum, totalSum);

        }

        printf("\nALL ENTRIES: \n%s\n", finalString);
        printf("\nSUM: %d\n", totalSum);


    }


    MPI_Finalize();
    return 0;

}

