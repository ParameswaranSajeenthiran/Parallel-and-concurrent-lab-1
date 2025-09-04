//
// Created by sajeenthiran on 2025-08-31.
//

#ifndef LAB_READ_WRITE_LOCK_H
#define LAB_READ_WRITE_LOCK_H

#include <pthread.h>
#include "Config.h"
#include "../linkedList.h"

struct ThreadDataReadWriteLock
{
    int currentInsertOps;
    int totalOps;
    int MemberOps;
    int InsertOps;
    int DeleteOps;
    pthread_rwlock_t * rwlock;
    struct Node **head;                // <— pointer to shared head
    int threadID;

};


double runReadWriteLock(int threadCount, struct Config config);
void *threadFuncReadWriteLock(void* arg);
#endif //LAB_READ_WRITE_LOCK_H