//
// Created by Lingling on 22-12-9 下午4:06.
// Github https://github.com/Lingling-LynnChan.
//
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
