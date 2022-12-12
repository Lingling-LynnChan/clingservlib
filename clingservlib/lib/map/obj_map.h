//
// Created by Lingling on 22-12-9 下午3:56.
// Github https://github.com/Lingling-LynnChan.
//
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
