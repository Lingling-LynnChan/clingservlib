//
// Created by Lingling on 22-12-10 上午3:25.
// Github https://github.com/Lingling-LynnChan.
//
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
