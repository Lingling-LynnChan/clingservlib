/*
Copyright 2022 Lingling-LynnChan, 陈子扬

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */

#include "../../ccmanager.h"

#include "../../lib/locker/mutexlock.h"
#include "../../lib/proxy/lalloc.h"
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