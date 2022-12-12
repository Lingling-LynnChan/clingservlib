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

#include "../../lib/object/str.h"
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/lalloc.h"

#include <string.h>

const ObjectMethod StrMethod = {
        .hash=HashStr,
        .cmp=CmpStr,
        .cpy=CpyStr,
        .free=(FreType) FreStr,
};

static const char *newCstr(const char *string) {
    char *newString = lmalloc(sizeof(char) * (strlen(string) + 1));
    strcpy(newString, string);
    return newString;
}

Str newStr(const char *val) {
    Str str = lmalloc(sizeof(StrNode));
    str->val = newCstr(val);
    return str;
}

const char *GetStr(Str str) {
    return str == NULL ? "" : str->val;
}

void *SetStr(Str str, const char *val) {
    if (str == NULL) {
        return NULL;
    }
    if (val == NULL) {
        val = "";
    }
    lfree((char *) str->val);
    str->val = newCstr(val);
    return str;
}

void FreStr(Str str) {
    if (str == NULL) {
        return;
    }
    lfree((char *) str->val);
    lfree(str);
}

void *CpyStr(const void *str) {
    if (str == NULL) {
        return NULL;
    }
    return newStr(GetStr((Str) str));
}

int CmpStr(const void *a, const void *b) {
    const char *ca = GetStr((Str) a);
    const char *cb = GetStr((Str) b);
    return strcmp(ca == NULL ? "" : ca, cb == NULL ? "" : cb);
}

//BKDRHash
uint64_t HashStr(const void *vStr) {
    const char *str = GetStr((Str) vStr);
    if (str == NULL) {
        str = "";
    }
    static size_t s = 131;
    uint64_t code = 0;
    while (*str) {
        code = code * s + (*str++);
    }
    return (uint64_t) (code & 0x7FFFFFFF);
}