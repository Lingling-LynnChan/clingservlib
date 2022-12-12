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
