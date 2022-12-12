//
// Created by Lingling on 22-12-10 上午2:48.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/locker/mutexlock.h"
#include "../../lib/proxy/alloc.h"
#include "../../lib/io.h"

SafePtr newMutexLocker(const pthread_mutexattr_t *nullableAttr) {
    MutexLocker locker = lmalloc(sizeof(MutexLockerNode));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    locker->lock = mutex;
    int result = pthread_mutex_init(&locker->lock, nullableAttr);
    if (result != 0) {
        perror("互斥锁初始化失败");
    }
    return newSafePtr(locker);
}

void FreMutexLocker(MutexLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_mutex_destroy(&locker->lock);
    if (result != 0) {
        perror("互斥锁销毁失败");
    }
    lfree(locker);
}

bool_t tryLockMutexLocker(MutexLocker locker) {
    if (locker == NULL) {
        return false;
    }
    int result = pthread_mutex_trylock(&locker->lock);
    if (result != 0) {
        perror("互斥锁尝试加锁失败");
    }
    return result == 0;
}

void lockMutexLocker(MutexLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_mutex_lock(&locker->lock);
    if (result != 0) {
        perror("互斥锁加锁失败");
    }
}

bool_t lockTimeoutMutexLocker(MutexLocker locker, const struct timespec *abs_timeout) {
    if (locker == NULL || abs_timeout == NULL) {
        return false;
    }
    int result = pthread_mutex_timedlock(&locker->lock, abs_timeout);
    if (result != 0) {
        perror("互斥锁限时加锁失败");
    }
    return result == 0;
}

void unlockMutexLocker(MutexLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_mutex_unlock(&locker->lock);
    if (result != 0) {
        perror("互斥锁解锁失败");
    }
}