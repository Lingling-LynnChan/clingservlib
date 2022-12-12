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

#ifndef CLINGSERV_OBJ_LIST_H
#define CLINGSERV_OBJ_LIST_H

#include <stdint.h>
#include "../object/obj.h"
#include "../safe/safe_ptr.h"

#ifndef MAX_LIST_DEF_SIZE
#define MAX_LIST_DEF_SIZE 8
#endif

typedef struct {
    int64_t size;
    int64_t length;
    void **value;
    const ObjectMethod *method;
    SafePtr locker;//RWLocker
} LNode, *List;

SafePtr newList(const ObjectMethod *method);

void AddList(List list, const void *object);

bool_t AddListAsSet(List list, const void *object);

int64_t AddListAsSetSuper(List list, const void *object);

int64_t ExchangeAtIndexListSuper(List list, const void *object, int64_t index);

const void *GetList(List list, int64_t index);

int64_t GetIndexByValue(List list, const void *value);

int64_t DelByValueList(List list, const void *value);

void DelByIndexList(List list, int64_t index);

void *GetAndDelByIndexListWithMalloc(List list, int64_t index);

void ClrList(List list);

void FreList(List list);

void SortList(List list);

const void *SearchList(List list, const void *value);

typedef struct {
    List list;
    int64_t now;
} ListIteratorNode,*ListIterator;

SafePtr GetListIterator(List list);

void FreListIterator(ListIterator iterator);

bool_t HasNextListIterator(ListIterator iterator);

const void *NextListIterator(ListIterator iterator);

#endif //CLINGSERV_OBJ_LIST_H
