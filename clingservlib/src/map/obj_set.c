//
// Created by Lingling on 22-12-10 上午3:25.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/map/obj_set.h"
#include "../../lib/object/int.h"

SafePtr newHashSet(const ObjectMethod *method) {
    return newHashMap(method, &IntMethod);
}

void AddHashSet(HashSet hashSet, const void *val) {
    PutHashMap(hashSet, val, newInt(0));
}

bool_t GetTargetHashSet(HashSet hashSet, const void *val) {
    return GetHashMap(hashSet, val) != NULL;
}

void DelHashSet(HashSet hashSet, const void *val) {
    DelHashMap(hashSet, val);
}

SafePtr GetValsHashSetWithAlloc(HashSet hashSet) {
    return GetKeysHashMapWithAlloc(hashSet);
}

void ClrHashSet(HashSet hashSet) {
    ClrHashMap(hashSet);
}

void FreHashSet(HashSet hashSet) {
    FreHashMap(hashSet);
}