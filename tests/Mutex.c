//
// Created by sajeenthiran on 2025-08-31.
//

#include "Mutex.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "Constants.h"


double runMutex(int threadCount, struct Config  config)
{
    /// validate config
    assert (config.mMember + config.mInsert + config.mDelete == 1.0);
    assert (config.n > 0);
    assert (config.m > 0);

    // printf( "Running with n = %d, m = %d, mMember = %f, mInsert = %f, mDelete = %f\n",
    //         config.n, config.m, config.mMember, config.mInsert, config.mDelete);
    long noOfOperations = config.m;
    int noOfElements = config.n;
    long MemberOps = config.mMember * noOfOperations;
    long InsertOps = config.mInsert* noOfOperations ;
    long DeleteOps =   config.mDelete * noOfOperations;


    srand(time(0));
    struct Node* head = NULL;

    long currentMemberOps = 0;
    long currentInsertOps = 0;
    long currentDeleteOps = 0;

    while (noOfElements > 0)
    {
        int randomValue = rand() % MAX_RANDOM;
        if (Insert(randomValue, &head) == 1)
        {
            noOfElements--;
        }
    }
    // printf( " Initial list populated with %d elements , now performing %ld member, %ld insert, and %ld delete operations.\n",
    //         config.n, MemberOps, InsertOps, DeleteOps);

    long totalOps = MemberOps + InsertOps + DeleteOps;

    pthread_t *thread_handles = malloc(threadCount * sizeof(pthread_t));


    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i=0 ; i< threadCount ; i++ )
    {
        struct ThreadData* threadData = malloc( sizeof(struct ThreadData) );
        threadData->totalOps = (i < totalOps % threadCount) ? (totalOps / threadCount + 1) : (totalOps / threadCount);
        threadData->MemberOps = (i < MemberOps % threadCount) ? (MemberOps / threadCount + 1) : (MemberOps / threadCount);
        threadData->InsertOps = (i < InsertOps % threadCount) ? (InsertOps / threadCount + 1) : (InsertOps / threadCount);
        threadData->DeleteOps = (i < DeleteOps % threadCount) ? (DeleteOps / threadCount + 1) : (DeleteOps / threadCount);
        threadData->head = &head;
        threadData->mutex = &mutex;
        threadData->threadID = i;
    pthread_create(&thread_handles[i], NULL, threadFunc, threadData); // ✅ correct signature
        }






        for (int i = 0; i < threadCount; i++) {
            pthread_join(thread_handles[i], NULL);
        }

        gettimeofday(&stop, NULL);


        double elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
        //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

        // printf("Elapsed time: %f seconds\n", elapsed);



        return elapsed;
    }


void *threadFunc(void *arg)
{
    struct ThreadData *threadData = (struct ThreadData *)arg;
    int currentMemberOps = 0;
    int currentInsertOps = 0;
    int currentDeleteOps = 0;

    // printf("Thread ID: %d\n", threadData->threadID);
    // printf("Member Ops: %d\n",threadData->MemberOps);
    // printf("Insert Ops: %d\n", threadData->InsertOps);
    // printf("Delete Ops: %d\n", threadData->DeleteOps);

    while (threadData->totalOps > 0)
    {
        int remainingMember = threadData->MemberOps - currentMemberOps;
        int remainingInsert = threadData->InsertOps - currentInsertOps;
        int remainingDelete = threadData->DeleteOps - currentDeleteOps;

        int totalRemaining = remainingMember + remainingInsert + remainingDelete;
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
        // printf("Thread %d performing %s operation with value %d\n",
        //              threadData->threadID,
        //              (chosenOperation == 0) ? "Member" : (chosenOperation == 1) ? "Insert" : "Delete",
        //              randomValue);
        pthread_mutex_lock(threadData->mutex);

        if (chosenOperation == 0) {
            Member(randomValue, *threadData->head);
            currentMemberOps++;
        } else if (chosenOperation == 1) {
            Insert(randomValue, threadData->head);
            currentInsertOps++;
        } else {
            Delete(randomValue, threadData->head);
            currentDeleteOps++;
        }

        pthread_mutex_unlock(threadData->mutex);

        threadData->totalOps--;
    }
    return NULL;

}
// test main
// int main() {
//     struct Config config = {1000, 10000, 0.99,
//                             0.005, 0.005}; // Example configuration
//     double runtime = runMutex(8, config); // Run with 4 threads
//     printf("Mutex runtime: %f microseconds\n", runtime);
//     return 0;
// }
