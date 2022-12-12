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

#ifndef CLINGSERV_SAFE_PTR_H
#define CLINGSERV_SAFE_PTR_H

#include "../bool.h"

typedef void *UnsafePtr;

typedef void (*FreType)(void *);

typedef struct {
    void *ptr;
    bool_t ok;
} SafePtr;

#define SafeNULL DefStruct(SafePtr, { .ok = false })

/**
 * newSafePtr 创建安全指针
 *
 * @param unsafeAllocPtr 堆空间指针
 * @return 安全指针
 */
SafePtr newSafePtr(UnsafePtr unsafeAllocPtr);

/**
 * FreSafePtr 释放安全指针
 *
 * @param safePtr 安全指针
 * @param free 释放函数
 */
void FreSafePtr(SafePtr *safePtr, FreType free);

/**
 * GetSafePtr 获取安全对象
 *
 * @param safePtr 安全指针
 * @return 指针
 */
UnsafePtr GetSafePtr(SafePtr safePtr);

bool_t IsOkSafePtr(SafePtr safePtr);

#endif //CLINGSERV_SAFE_PTR_H
