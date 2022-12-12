//
// Created by Lingling on 22-12-9 下午2:15.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/output.h"

static int64_t PtrAllocCount = 0;

static void log_debug(bool_t b) {
    printf("i [SAFE_PTR_ALLOC_COUNT] %s成功, 现有 %ld 块内存未释放\n", b ? "代理内存绑定" : "代理内存释放", PtrAllocCount);
}

SafePtr newSafePtr(UnsafePtr unsafeAllocPtr) {
#ifdef SAFE_PTR_ALLOC_COUNT
    if (unsafeAllocPtr != NULL) {
        PtrAllocCount++;
        log_debug(true);
    }
#endif
    SafePtr safePtr = {.ptr=unsafeAllocPtr, .ok=true};
    return safePtr;
}

void FreSafePtr(SafePtr *safePtr, FreType free) {
    if (safePtr == NULL) {
        return;
    }
    if (safePtr->ok) {
        free(safePtr->ptr);
#ifdef SAFE_PTR_ALLOC_COUNT
        PtrAllocCount--;
        log_debug(false);
#endif
    }
    safePtr->ok = false;
}

UnsafePtr GetSafePtr(SafePtr safePtr) {
    if (IsOkSafePtr(safePtr)) {
        return safePtr.ptr;
    }
    Debug("获取失败","已释放的指针",'e');
    return NULL;
}

bool_t IsOkSafePtr(SafePtr safePtr) {
    return safePtr.ok;
}