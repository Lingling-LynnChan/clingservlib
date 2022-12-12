//
// Created by Lingling on 22-12-9 下午4:23.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/object/flt.h"
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/alloc.h"

const ObjectMethod FltMethod = {
        .hash=HashFlt,
        .cmp=CmpFlt,
        .cpy=CpyFlt,
        .free=(FreType) FreFlt,
};

Flt newFlt(float64_t val) {
    Flt flt = lmalloc(sizeof(FltNode));
    flt->val = val;
    return flt;
}

float64_t GetFlt(Flt flt) {
    if (flt == NULL) {
        return 0;
    }
    return flt->val;
}

void *SetFlt(Flt flt, float64_t value) {
    if (flt == NULL) {
        return NULL;
    }
    flt->val = value;
    return flt;
}

void FreFlt(Flt flt) {
    if (flt == NULL) {
        return;
    }
    lfree(flt);
}

void *CpyFlt(const void *flt) {
    if (flt == NULL) {
        return NULL;
    }
    return newFlt(GetFlt((Flt) flt));
}

int CmpFlt(const void *a, const void *b) {
    float64_t f = GetFlt((Flt) b) - GetFlt((Flt) a);
    return f < 0 ? -1 : (f == 0 ? 0 : 1);
}

//& 0x7FFFFFFF
uint64_t HashFlt(const void *vFlt) {
    Flt flt = (Flt) vFlt;
    uint64_t code = *(uint64_t *) &flt->val;
    return code & 0x7FFFFFFF;
}
