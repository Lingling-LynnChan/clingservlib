//
// Created by Lingling on 22-12-9 下午4:08.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_INT_H
#define CLINGSERV_INT_H

#include "obj.h"

typedef struct {
    int64_t val;
} IntNode, *Int;

extern const ObjectMethod IntMethod;

Int newInt(int64_t val);

int64_t GetInt(Int int64);

void *SetInt(Int int64, int64_t value);

void FreInt(Int int64);

void *CpyInt(const void *int64);

int CmpInt(const void *a, const void *b);

uint64_t HashInt(const void *vInt);

#endif //CLINGSERV_INT_H
