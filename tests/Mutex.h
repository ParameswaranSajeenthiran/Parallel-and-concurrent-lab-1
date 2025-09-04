//
// Created by sajeenthiran on 2025-08-31.
//

#ifndef LAB_MUTEX_H
#define LAB_MUTEX_H

#include <pthread.h>
#include "Config.h"
#include "../linkedList.h"

struct ThreadData
{
    int currentInsertOps;
    int totalOps;
    int MemberOps;
    int InsertOps;
    int DeleteOps;
    pthread_mutex_t* mutex;
    struct Node** head;
    int threadID;

};


double runMutex(int threadCount, struct Config config);

void *threadFunc(void *arg);
#endif //LAB_MUTEX_H