//
// Created by Lingling on 22-12-10 上午2:48.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_MUTEXLOCK_H
#define CLINGSERV_MUTEXLOCK_H

#include "../bool.h"
#include "../safe/safe_ptr.h"

#include <pthread.h>

//互斥锁
typedef struct {
    pthread_mutex_t lock;
} MutexLockerNode, *MutexLocker;

SafePtr newMutexLocker(const pthread_mutexattr_t *nullableAttr);

bool_t tryLockMutexLocker(MutexLocker locker);

void lockMutexLocker(MutexLocker locker);

bool_t lockTimeoutMutexLocker(MutexLocker locker, const struct timespec *abs_timeout);

void unlockMutexLocker(MutexLocker locker);

void FreMutexLocker(MutexLocker locker);

#endif //CLINGSERV_MUTEXLOCK_H
