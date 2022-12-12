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

#include "../../lib/map/obj_map.h"
#include "../../lib/def_struct.h"
#include "../../lib/proxy/lalloc.h"
#include "../../lib/locker/rwlock.h"

#define Locker(hashMap) ((RWLocker)GetSafePtr(hashMap->locker))
#define rlock(hashMap) lockRLocker(Locker(hashMap))
#define urlock(hashMap) unlockRLocker(Locker(hashMap))
#define wlock(hashMap) lockWLocker(Locker(hashMap))
#define uwlock(hashMap) unlockWLocker(Locker(hashMap))

#define KeyPtr(hashMap, index) ((SafePtr *) GetSafePtr(hashMap->keys))[index]
#define ValPtr(hashMap, index) ((SafePtr *) GetSafePtr(hashMap->vals))[index]

#define KeyList(hashMap, index) ((List)GetSafePtr(KeyPtr(hashMap,index)))
#define ValList(hashMap, index) ((List)GetSafePtr(ValPtr(hashMap,index)))

static SafePtr newHashMapList(uint64_t size) {
    SafePtr *lists = lmalloc(sizeof(SafePtr) * size);
    for (uint64_t i = 0; i < size; ++i) {
        lists[i] = SafeNULL;
    }
    return newSafePtr(lists);
}

static HashMap
newHashMapTools(const ObjectMethod *keyMethod, const ObjectMethod *valMethod, int64_t size, bool_t isLock) {
    HashMap hashMap = lmalloc(sizeof(HashMapNode));
    if (hashMap == NULL) {
        return NULL;
    }
    hashMap->keyMethod = keyMethod;
    hashMap->valMethod = valMethod;
    hashMap->loadFactor = HASHMAP_LOAD_FACTOR;
    hashMap->used = 0;
    hashMap->size = size;
    hashMap->keys = newHashMapList(hashMap->size);
    hashMap->vals = newHashMapList(hashMap->size);
    if (isLock) {
        hashMap->locker = newRWLocker(NULL);
    } else {
        hashMap->locker = SafeNULL;
    }
    return hashMap;
}

SafePtr newHashMap(const ObjectMethod *keyMethod, const ObjectMethod *valMethod) {
    if (keyMethod == NULL || valMethod == NULL) {
        return SafeNULL;
    }
    return newSafePtr(newHashMapTools(keyMethod, valMethod, MAX_HASHMAP_DEF_SIZE, true));
}

static bool_t isResize(HashMap hashMap) {
    if (hashMap == NULL) {
        return false;
    }
    double loader = (double) hashMap->used / (double) hashMap->size;
    return loader > hashMap->loadFactor;
}

//保证不会Resize的情况下使用
static void StaticPutHashMap(HashMap hashMap, const void *key, const void *val) {
    if (hashMap == NULL) {
        return;
    }
    uint64_t index = hashMap->keyMethod->hash(key) % hashMap->size;
    if (!IsOkSafePtr(KeyPtr(hashMap, index))) {
        KeyPtr(hashMap, index) = newList(hashMap->keyMethod);
        ValPtr(hashMap, index) = newList(hashMap->valMethod);
    }
    if (1 == ExchangeAtIndexListSuper(
            ValList(hashMap, index),
            val,
            AddListAsSetSuper(KeyList(hashMap, index), key))) {
        hashMap->used++;
    }
}

static void Resize(HashMap hashMap) {
    if (hashMap == NULL) {
        return;
    }
    int64_t newSize = hashMap->size * HASHMAP_RESIZE_COEFFICIENT;
    HashMap nHashMap = newHashMapTools(hashMap->keyMethod, hashMap->valMethod, newSize, false);
    for (int64_t i = 0; i < hashMap->size; ++i) {
        if (!IsOkSafePtr(KeyPtr(hashMap, i))) {
            continue;
        }
        for (int64_t j = 0; j < KeyList(hashMap, i)->length; ++j) {
            StaticPutHashMap(
                    nHashMap,
                    KeyList(hashMap, i)->value[j],
                    ValList(hashMap, i)->value[j]
            );
        }
        FreSafePtr(&KeyPtr(hashMap, i), (FreType) FreList);
        FreSafePtr(&ValPtr(hashMap, i), (FreType) FreList);
    }
    FreSafePtr(&hashMap->keys, lfree);
    FreSafePtr(&hashMap->vals, lfree);
    hashMap->keys = nHashMap->keys;
    hashMap->vals = nHashMap->vals;
    hashMap->size = nHashMap->size;
    hashMap->used = nHashMap->used;
}

void PutHashMap(HashMap hashMap, const void *key, const void *val) {
    if (hashMap==NULL){
        return;
    }
    wlock(hashMap);
    StaticPutHashMap(hashMap, key, val);
    if (isResize(hashMap)) {
        Resize(hashMap);
    }
    uwlock(hashMap);
}

const void *GetHashMap(HashMap hashMap, const void *key) {
    if (hashMap == NULL) {
        return NULL;
    }
    rlock(hashMap);
    uint64_t index = hashMap->keyMethod->hash(key) % hashMap->size;
    int64_t offset = GetIndexByValue(KeyList(hashMap, index), key);
    const void *result = GetList(ValList(hashMap, index), offset);
    urlock(hashMap);
    return result;
}

void DelHashMap(HashMap hashMap, const void *key) {
    if (hashMap == NULL) {
        return;
    }
    uint64_t index = hashMap->keyMethod->hash(key) % hashMap->size;
    if (!IsOkSafePtr(KeyPtr(hashMap, index))) {
        return;
    }
    wlock(hashMap);
    int64_t offset = GetIndexByValue(KeyList(hashMap, index), key);
    DelByIndexList(KeyList(hashMap, index), offset);
    DelByIndexList(ValList(hashMap, index), offset);
    if (IsOkSafePtr(KeyPtr(hashMap, index)) && KeyList(hashMap, index)->length == 0) {
        FreSafePtr(&KeyPtr(hashMap, index), (FreType) FreList);
        FreSafePtr(&ValPtr(hashMap, index), (FreType) FreList);
        KeyPtr(hashMap, index) = SafeNULL;
        ValPtr(hashMap, index) = SafeNULL;
    }
    uwlock(hashMap);
}

SafePtr GetKeysHashMapWithAlloc(HashMap hashMap) {
    SafePtr list = newList(hashMap->keyMethod);
    if (hashMap == NULL) {
        return list;
    }
    rlock(hashMap);
    for (int64_t i = 0; i < hashMap->size; ++i) {
        if (!IsOkSafePtr(KeyPtr(hashMap, i))) {
            continue;
        }
        if (KeyList(hashMap, i) == NULL) {
            continue;
        }
        for (int64_t j = 0; j < KeyList(hashMap, i)->length; ++j) {
            AddListAsSet(GetSafePtr(list), KeyList(hashMap, i)->value[j]);
        }
    }
    urlock(hashMap);
    return list;
}

void ClrHashMap(HashMap hashMap) {
    if (hashMap == NULL) {
        return;
    }
    wlock(hashMap);
    for (int64_t i = 0; i < hashMap->size; ++i) {
        if (IsOkSafePtr(KeyPtr(hashMap, i))) {
            FreSafePtr(&KeyPtr(hashMap, i), (FreType) FreList);
            FreSafePtr(&ValPtr(hashMap, i), (FreType) FreList);
        }
    }
    FreSafePtr(&hashMap->keys, lfree);
    FreSafePtr(&hashMap->vals, lfree);
    hashMap->keys = newHashMapList(MAX_HASHMAP_DEF_SIZE);
    hashMap->vals = newHashMapList(MAX_HASHMAP_DEF_SIZE);
    hashMap->size = MAX_HASHMAP_DEF_SIZE;
    hashMap->used = 0;
    uwlock(hashMap);
}

void FreHashMap(HashMap hashMap) {
    if (hashMap == NULL) {
        return;
    }
    wlock(hashMap);
    for (int64_t i = 0; i < hashMap->size; ++i) {
        if (IsOkSafePtr(KeyPtr(hashMap, i))) {
            FreSafePtr(&KeyPtr(hashMap, i), (FreType) FreList);
            FreSafePtr(&ValPtr(hashMap, i), (FreType) FreList);
        }
    }
    FreSafePtr(&hashMap->keys, lfree);
    FreSafePtr(&hashMap->vals, lfree);
    uwlock(hashMap);
    FreSafePtr(&hashMap->locker, (FreType) FreRWLocker);
    lfree(hashMap);
}