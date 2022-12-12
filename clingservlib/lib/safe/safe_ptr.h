//
// Created by Lingling on 22-12-9 下午2:15.
// Github https://github.com/Lingling-LynnChan.
//
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
