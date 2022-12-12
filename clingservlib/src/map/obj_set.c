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