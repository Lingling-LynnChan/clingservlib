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
