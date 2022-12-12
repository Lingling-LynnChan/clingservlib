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

#ifndef CLINGSERV_OBJ_MAP_H
#define CLINGSERV_OBJ_MAP_H

#include <stddef.h>
#include <stdint.h>

#include "../object/obj.h"
#include "../list/obj_list.h"
#include "../safe/safe_ptr.h"

#ifndef MAX_HASHMAP_DEF
#define MAX_HASHMAP_DEF_SIZE (16)
#define HASHMAP_LOAD_FACTOR (0.75f)
#define HASHMAP_RESIZE_COEFFICIENT (2)
#endif

typedef struct {
    int64_t used;
    int64_t size;
    double loadFactor;
    SafePtr keys;//(SafePtr(List *) *)
    SafePtr vals;//(SafePtr(List *) *)
    const ObjectMethod *keyMethod;
    const ObjectMethod *valMethod;
    SafePtr locker;//RWLocker
} HashMapNode, *HashMap;

SafePtr newHashMap(const ObjectMethod *keyMethod, const ObjectMethod *valMethod);

void PutHashMap(HashMap hashMap, const void *key, const void *val);

const void *GetHashMap(HashMap hashMap, const void *key);

void DelHashMap(HashMap hashMap, const void *key);

SafePtr GetKeysHashMapWithAlloc(HashMap hashMap);

void ClrHashMap(HashMap hashMap);

void FreHashMap(HashMap hashMap);

#endif //CLINGSERV_OBJ_MAP_H
