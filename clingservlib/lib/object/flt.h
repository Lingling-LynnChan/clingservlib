//
// Created by Lingling on 22-12-9 下午4:23.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_FLT_H
#define CLINGSERV_FLT_H

#include <stdint.h>
#include "obj.h"

typedef struct {
    float64_t val;
} FltNode, *Flt;

extern const ObjectMethod FltMethod;

Flt newFlt(float64_t val);

float64_t GetFlt(Flt flt);

void *SetFlt(Flt flt, float64_t value);

void FreFlt(Flt flt);

void *CpyFlt(const void *flt);

int CmpFlt(const void *a, const void *b);

uint64_t HashFlt(const void* vFlt);

#endif //CLINGSERV_FLT_H
