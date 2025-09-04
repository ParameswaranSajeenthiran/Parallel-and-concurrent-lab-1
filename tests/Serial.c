//
// Created by sajeenthiran on 2025-08-31.
//

#include "Serial.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "Constants.h"


double run_serial(struct Config config)
{
    assert(config.mMember + config.mInsert + config.mDelete == 1.0);
    assert(config.n > 0);
    assert(config.m > 0);

    long noOfOperations = config.m;
    int noOfElements = config.n;
    long MemberOps = config.mMember * noOfOperations;
    long InsertOps = config.mInsert * noOfOperations;
    long DeleteOps = config.mDelete * noOfOperations;

    srand(time(0));
    struct Node* head = NULL;

    // Faster initial population: sequential values
    while (noOfElements > 0)
    {
        int randomValue = rand() % MAX_RANDOM;
        if (Insert(randomValue, &head) == 1)
        {
            noOfElements--;
        }
    }

    long currentMemberOps = 0;
    long currentInsertOps = 0;
    long currentDeleteOps = 0;
    long totalOps = MemberOps + InsertOps + DeleteOps;

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    while (totalOps > 0)
    {
        long remainingMember = MemberOps - currentMemberOps;
        long remainingInsert = InsertOps - currentInsertOps;
        long remainingDelete = DeleteOps - currentDeleteOps;
        long totalRemaining = remainingMember + remainingInsert + remainingDelete;

        if (totalRemaining == 0) break;

        int r = rand() % totalRemaining;
        int chosenOperation;
        if (r < remainingMember)
            chosenOperation = 0;
        else if (r < remainingMember + remainingInsert)
            chosenOperation = 1;
        else
            chosenOperation = 2;

        int randomValue = rand() % MAX_RANDOM;
        // printf(" performing %s operation with value %d\n",
        //              (chosenOperation == 0) ? "Member" : (chosenOperation == 1) ? "Insert" : "Delete",
        //              randomValue);
        if (chosenOperation == 0) {
            Member(randomValue, head);
            currentMemberOps++;
        } else if (chosenOperation == 1) {
            Insert(randomValue, &head);
            currentInsertOps++;
        } else {
            Delete(randomValue, &head);
            currentDeleteOps++;
        }

        totalOps--;
    }

    gettimeofday(&stop, NULL);
    double elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

    return elapsed;
}
/// test main function
// int main()
// {
//     struct Config config = {1000, 10000, 0.99,
//                             0.005, 0.005};
//     double time_taken = run_serial(config);
//     printf("Time taken: %f microseconds\n", time_taken);
//     return 0;
// }

