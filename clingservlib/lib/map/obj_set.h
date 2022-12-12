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

#ifndef CLINGSERV_OBJ_SET_H
#define CLINGSERV_OBJ_SET_H

#include "obj_map.h"

typedef HashMap HashSet;

SafePtr newHashSet(const ObjectMethod *method);

void AddHashSet(HashSet hashSet, const void *val);

bool_t GetTargetHashSet(HashSet hashSet, const void *val);

void DelHashSet(HashSet hashSet, const void *val);

SafePtr GetValsHashSetWithAlloc(HashSet hashSet);

void ClrHashSet(HashSet hashSet);

void FreHashSet(HashSet hashSet);

#endif //CLINGSERV_OBJ_SET_H
