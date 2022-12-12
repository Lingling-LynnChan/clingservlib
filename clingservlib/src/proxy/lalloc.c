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

#include "../../lib/proxy/lalloc.h"
#include "../../lib/proxy/output.h"

#include <malloc.h>

static void AllocHandler(const void *ptr, size_t size, bool_t isRealloc) {
#ifdef PROXY_ALLOC_DEBUG
    static size_t count = 0;
    if(isRealloc){
        if(ptr!=NULL){
            printf("i [LIB_ALLOC_DEBUG] 调整了 %p 处的内存大小为 %lu byte(s)\n", ptr, size);
        }else{
            Error("w [LIB_ALLOC_DEBUG] 试图调整空指针的大小","代理工具未处理");
        }
    }else if (size == 0) {
        if (ptr != NULL) {
            count--;
            printf("i [LIB_ALLOC_DEBUG] 释放了 %p 处的内存, 现有 %lu 块内存未释放\n", ptr, count);
        } else {
            Error("e [LIB_ALLOC_DEBUG] 捕获到释放空指针","代理工具未处理");
        }
    } else {
        if (ptr != NULL) {
            count++;
            printf("i [LIB_ALLOC_DEBUG] 申请了 %p (%lu byte(s)) 内存, 现有 %lu 块内存未释放\n", ptr, size, count);
        } else {
            perror("e [LIB_ALLOC_DEBUG] 申请内存失败");
        }
    }
#endif
}

void *lmalloc(size_t size) {
    void *ptr = malloc(size);
    AllocHandler(ptr, size, false);
    return ptr;
}

void *lcalloc(size_t nsize, size_t size) {
    void *ptr = calloc(nsize, size);
    AllocHandler(ptr, size * nsize, false);
    return ptr;
}

void lfree(void *ptr) {
    AllocHandler(ptr, 0, false);
    free(ptr);
}

void *lrealloc(void *ptr, size_t size) {
    AllocHandler(ptr, size, true);
    return realloc(ptr, size);
}