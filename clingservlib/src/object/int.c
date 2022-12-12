//
// Created by Lingling on 22-12-9 下午4:08.
// Github https://github.com/Lingling-LynnChan.
//
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
