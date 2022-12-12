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