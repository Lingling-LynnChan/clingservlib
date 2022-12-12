//
// Created by Lingling on 22-12-12 上午4:20.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/locker/rwlock.h"
#include "../../lib/proxy/lalloc.h"
#include "../../lib/io.h"

SafePtr newRWLocker(const pthread_rwlockattr_t *nullableAttr) {
    RWLocker locker = lmalloc(sizeof(RWLockerNode));
    pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
    locker->lock = rwlock;
    int result = pthread_rwlock_init(&locker->lock, nullableAttr);
    if (result != 0) {
        perror("读写锁初始化失败");
    }
    return newSafePtr(locker);
}

bool_t tryLockRLocker(RWLocker locker) {
    if (locker == NULL) {
        return false;
    }
    int result = pthread_rwlock_tryrdlock(&locker->lock);
    if (result != 0) {
        perror("读锁尝试加锁失败");
    }
    return result == 0;
}

bool_t tryLockWLocker(RWLocker locker) {
    if (locker == NULL) {
        return false;
    }
    int result = pthread_rwlock_trywrlock(&locker->lock);
    if (result != 0) {
        perror("写锁尝试加锁失败");
    }
    return result == 0;
}

void lockRLocker(RWLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_rwlock_rdlock(&locker->lock);
    if (result != 0) {
        perror("读锁加锁失败");
    }
}

void lockWLocker(RWLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_rwlock_wrlock(&locker->lock);
    if (result != 0) {
        perror("写锁加锁失败");
    }
}

void unlockRLocker(RWLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_rwlock_unlock(&locker->lock);
    if (result != 0) {
        perror("读锁解锁失败");
    }
}

void unlockWLocker(RWLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_rwlock_unlock(&locker->lock);
    if (result != 0) {
        perror("写锁解锁失败");
    }
}

void FreRWLocker(RWLocker locker) {
    if (locker == NULL) {
        return;
    }
    int result = pthread_rwlock_destroy(&locker->lock);
    if (result != 0) {
        perror("读写锁销毁失败");
    }
    lfree(locker);
}

#define pthread_rwlock_timedXXLock(rwlock, abs, type) pthread_rwlock_timed##type##lock(rwlock,abs)

bool_t lockTimeoutRLocker(RWLocker locker, const struct timespec *abs_timeout) {
    if (locker == NULL || abs_timeout == NULL) {
        return false;
    }
    int result = pthread_rwlock_timedXXLock(&locker->lock, abs_timeout, rd);
    if (result != 0) {
        perror("读锁限时加锁失败");
    }
    return result == 0;
}

bool_t lockTimeoutWLocker(RWLocker locker, const struct timespec *abs_timeout) {
    if (locker == NULL || abs_timeout == NULL) {
        return false;
    }
    int result = pthread_rwlock_timedXXLock(&locker->lock, abs_timeout, wr);
    if (result != 0) {
        perror("写锁限时加锁失败");
    }
    return result == 0;
}