//
// Created by sajeenthiran on 2025-08-31.
//

#include "ReadWriteLock.h"
#include <pthread.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "Constants.h"
double runReadWriteLock(int threadCount, struct Config  config)
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
            // config.n, MemberOps, InsertOps, DeleteOps);

    long totalOps = MemberOps + InsertOps + DeleteOps;

    pthread_t *thread_handles = malloc(threadCount * sizeof(pthread_t));


    pthread_rwlock_t rwlock;

    pthread_rwlock_init(&rwlock, NULL);


    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i=0 ; i< threadCount ; i++ )
    {
        struct ThreadDataReadWriteLock* threadData = malloc( sizeof(struct ThreadDataReadWriteLock) );
        threadData->totalOps = (i < totalOps % threadCount) ? (totalOps / threadCount + 1) : (totalOps / threadCount);
        threadData->MemberOps = (i < MemberOps % threadCount) ? (MemberOps / threadCount + 1) : (MemberOps / threadCount);
        threadData->InsertOps = (i < InsertOps % threadCount) ? (InsertOps / threadCount + 1) : (InsertOps / threadCount);
        threadData->DeleteOps = (i < DeleteOps % threadCount) ? (DeleteOps / threadCount + 1) : (DeleteOps / threadCount);
    threadData->head      = &head;              // <— share the same head
        threadData->rwlock = &rwlock;
        threadData->threadID = i;
        pthread_create(&thread_handles[i], NULL, threadFuncReadWriteLock, threadData);
        }



        for (int i = 0; i < threadCount; i++) {
            pthread_join(thread_handles[i], NULL);
        }

    free(thread_handles);


        gettimeofday(&stop, NULL);


        double elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
        //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

        // printf("Elapsed time: %f seconds\n", elapsed);



        return elapsed;
    }


void *threadFuncReadWriteLock(void *arg)


{
    struct ThreadDataReadWriteLock* threadData = (struct ThreadDataReadWriteLock*) arg;

    int currentMemberOps = 0;
    int currentInsertOps = 0;
    int currentDeleteOps = 0;

    while (threadData->totalOps > 0)
    {
        int totalRemaining = (threadData->MemberOps - currentMemberOps) +
                             (threadData->InsertOps - currentInsertOps) +
                             (threadData->DeleteOps - currentDeleteOps);

        if (totalRemaining == 0) break;

        int r = rand() % totalRemaining;

        int chosenOperation;
        if (r < (threadData->MemberOps - currentMemberOps)) {
            chosenOperation = 0;
        } else if (r < (threadData->MemberOps - currentMemberOps) + (threadData->InsertOps - currentInsertOps)) {
            chosenOperation = 1;
        } else {
            chosenOperation = 2;
        }

        int randomValue = rand() % MAX_RANDOM;

        //
        // printf("Thread %d performing %s operation with value %d\n",
        //        threadData->threadID,
        //        (chosenOperation == 0) ? "Member" : (chosenOperation == 1) ? "Insert" : "Delete",
        //        randomValue);
        if (chosenOperation == 0) {
            pthread_rwlock_rdlock(threadData->rwlock);
            Member(randomValue, *threadData->head);
            pthread_rwlock_unlock(threadData->rwlock);
            currentMemberOps++;
        } else if (chosenOperation == 1) {
            pthread_rwlock_wrlock(threadData->rwlock);
            Insert(randomValue, threadData->head);
            pthread_rwlock_unlock(threadData->rwlock);
            currentInsertOps++;
        } else {
            pthread_rwlock_wrlock(threadData->rwlock);
            Delete(randomValue, threadData->head);
            pthread_rwlock_unlock(threadData->rwlock);
            currentDeleteOps++;
        }

        threadData->totalOps--;
    }
    return NULL;
}