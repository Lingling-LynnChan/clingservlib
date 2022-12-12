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
