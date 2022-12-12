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

#include "../../lib/object/int.h"
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/lalloc.h"

const ObjectMethod IntMethod = {
        .hash=HashInt,
        .cmp=CmpInt,
        .cpy=CpyInt,
        .free=(FreType)FreInt,
};

Int newInt(int64_t val) {
    Int int64 = lmalloc(sizeof(IntNode));
    int64->val = val;
    return int64;
}

int64_t GetInt(Int int64) {
    if (int64 == NULL) {
        return 0;
    }
    return int64->val;
}

void *SetInt(Int int64, int64_t value) {
    if (int64 == NULL) {
        return NULL;
    }
    int64->val = value;
    return int64;
}

void FreInt(Int int64) {
    if (int64 == NULL) {
        return;
    }
    lfree(int64);
}

void *CpyInt(const void *int64) {
    if (int64 == NULL) {
        return NULL;
    }
    return newInt(GetInt((Int) int64));
}

int CmpInt(const void *a, const void *b) {
    int64_t i = GetInt((Int) b) - GetInt((Int) a);
    return i < 0 ? -1 : (i == 0 ? 0 : 1);
}

uint64_t HashInt(const void *vInt) {
    Int int64 = (Int) vInt;
    uint64_t code = *(uint64_t *) &int64->val;
    return (code & 0x7FFFFFFF);
}
