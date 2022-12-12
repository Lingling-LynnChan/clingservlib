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

#include "../../lib/object/flt.h"
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/lalloc.h"

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
