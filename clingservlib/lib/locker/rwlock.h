//
// Created by Lingling on 22-12-12 上午4:20.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_RWLOCK_H
#define CLINGSERV_RWLOCK_H

#include <pthread.h>
#include "../safe/safe_ptr.h"

typedef struct {
    pthread_rwlock_t lock;
}RWLockerNode,*RWLocker;

SafePtr newRWLocker(const pthread_rwlockattr_t *nullableAttr);

bool_t tryLockRLocker(RWLocker locker);

bool_t tryLockWLocker(RWLocker locker);

void lockRLocker(RWLocker locker);

void lockWLocker(RWLocker locker);

void unlockRLocker(RWLocker locker);

void unlockWLocker(RWLocker locker);

void FreRWLocker(RWLocker locker);

#endif //CLINGSERV_RWLOCK_H
