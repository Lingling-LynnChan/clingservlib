//
// Created by Lingling on 22-12-9 下午4:31.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_STR_H
#define CLINGSERV_STR_H

#include <stdint.h>
#include "obj.h"

typedef struct {
    const char *val;
} StrNode, *Str;

extern const ObjectMethod StrMethod;

Str newStr(const char *val);

const char *GetStr(Str str);

void *SetStr(Str str, const char *val);

void FreStr(Str str);

void *CpyStr(const void *str);

int CmpStr(const void *a, const void *b);

uint64_t HashStr(const void *str);

#endif //CLINGSERV_STR_H
