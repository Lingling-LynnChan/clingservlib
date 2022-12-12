//
// Created by Lingling on 22-12-9 下午4:31.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/object/str.h"
#include "../../lib/safe/safe_ptr.h"
#include "../../lib/proxy/alloc.h"

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