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
