//
// Created by Lingling on 22-12-9 下午4:06.
// Github https://github.com/Lingling-LynnChan.
//
#include "../../ccmanager.h"

#include "../../lib/list/obj_list.h"
#include "../../lib/object/str.h"
#include "../../lib/locker/rwlock.h"
#include "../../lib/io.h"
#include "../../lib/proxy/lalloc.h"

#define Locker(list) ((RWLocker)GetSafePtr(list->locker))
#define rlock(list) lockRLocker(Locker(list))
#define urlock(list) unlockRLocker(Locker(list))
#define wlock(list) lockWLocker(Locker(list))
#define uwlock(list) unlockWLocker(Locker(list))

static List newListTools(const ObjectMethod *method, bool_t isLock) {
    if (method == NULL) {
        return NULL;
    }
    List list = lmalloc(sizeof(LNode));
    if (list == NULL) {
        perror("内存申请失败");
        return NULL;
    }
    list->value = lmalloc(sizeof(void *) * MAX_LIST_DEF_SIZE);
    list->size = MAX_LIST_DEF_SIZE;
    list->length = 0;
    list->method = method;
    if (isLock) {
        list->locker = newRWLocker(NULL);
    }
    return list;
}

SafePtr newList(const ObjectMethod *method) {
    return newSafePtr(newListTools(method, true));
}

void AddList(List list, const void *object) {
    if (list == NULL) {
        return;
    }
    wlock(list);
    if (list->length == list->size) {
        int64_t newSize = list->size * 2;
        void **newAlloc = lrealloc(list->value, newSize * sizeof(void *));
        list->value = newAlloc;
        list->size = newSize;
    }
    list->value[list->length++] = list->method->cpy(object);
    uwlock(list);
}

bool_t AddListAsSet(List list, const void *object) {
    if (list == NULL) {
        return false;
    }
    if (GetIndexByValue(list, object) != -1) {
        return false;
    }
    AddList(list, object);
    return true;
}

int64_t AddListAsSetSuper(List list, const void *object) {
    if (list == NULL) {
        return -1;
    }
    for (int64_t i = 0; i < list->length; ++i) {
        if (list->method->cmp(object, list->value[i]) != 0) {
            continue;
        }
        list->method->free(list->value[i]);
        list->value[i] = list->method->cpy(object);
        return i;
    }
    AddList(list, object);
    return list->length - 1;
}

int64_t ExchangeAtIndexListSuper(List list, const void *object, int64_t index) {
    if (list == NULL || index > list->length || index < 0) {
        //出错
        return -1;
    }
    //追加到末尾: 增加元素
    if (index == list->length) {
        AddList(list, object);
        return 1;
    }
    list->method->free(list->value[index]);
    list->value[index] = list->method->cpy(object);
    //替换元素
    return 0;
}

const void *GetList(List list, int64_t index) {
    if (list == NULL || index >= list->length || index < 0) {
        return NULL;
    }
    return list->value[index];
}

int64_t GetIndexByValue(List list, const void *value) {
    if (list == NULL) {
        return -1;
    }
    int64_t result = -1;
    rlock(list);
    for (int64_t i = 0; i < list->length; ++i) {
        if (list->method->cmp(value, list->value[i]) != 0) {
            continue;
        }
        result = i;
        break;
    }
    urlock(list);
    return result;
}

static void ListResetAlloc(List list) {
    if (list == NULL) {
        return;
    }
    int64_t newSize = list->size;
    while (newSize >= list->length * 2 && newSize > MAX_LIST_DEF_SIZE) {
        newSize /= 2;
    }
    if (newSize == list->size) {
        return;
    }
    void **newAlloc = lrealloc(list->value, newSize * sizeof(void *));
    list->value = newAlloc;
    list->size = newSize;
}

static void DelListTool(List list, int64_t index, bool_t reset) {
    if (list == NULL || index >= list->length || index < 0) {
        return;
    }
    list->method->free(list->value[index]);
    for (int64_t i = index + 1; i < list->length; ++i) {
        list->value[i - 1] = list->value[i];
    }
    list->length--;
    if (reset) {
        ListResetAlloc(list);
    }
}

int64_t DelByValueList(List list, const void *value) {
    if (list == NULL) {
        return 0;
    }
    int64_t temp = 0;
    wlock(list);
    for (int64_t i = (int64_t) list->length - 1; i >= 0; --i) {
        if (list->method->cmp(value, list->value[i]) != 0) {
            continue;
        }
        temp++;
        DelListTool(list, i, false);
    }
    ListResetAlloc(list);
    uwlock(list);
    return temp;
}

void DelByIndexList(List list, int64_t index) {
    wlock(list);
    DelListTool(list, index, true);
    uwlock(list);
}

void *GetAndDelByIndexListWithMalloc(List list, int64_t index) {
    if (list == NULL || index >= list->length || list < 0) {
        return NULL;
    }
    uwlock(list);
    void *object = list->method->cpy(list->value[index]);
    DelListTool(list, index, true);
    uwlock(list);
    return object;
}

static void ListClrTool(List list) {
    for (int64_t i = 0; i < list->length; ++i) {
        if (list->value[i] == NULL) {
            continue;
        }
        list->method->free(list->value[i]);
    }
    lfree(list->value);
}

void ClrList(List list) {
    if (list == NULL) {
        return;
    }
    wlock(list);
    ListClrTool(list);
    List nList = newListTools(list->method, false);
    list->value = nList->value;
    list->length = nList->length;
    list->size = nList->size;
    lfree(nList);
    uwlock(list);
}

void FreList(List list) {
    if (list == NULL) {
        return;
    }
    wlock(list);
    ListClrTool(list);
    FreSafePtr(&list->locker, (FreType) FreRWLocker);
    lfree(list);
}

extern void qsort(void *, size_t nsize, size_t size, int (*cmp)(const void *, const void *));

void SortList(List list) {
    if (list == NULL) {
        return;
    }
    wlock(list);
    qsort(list->value, (size_t) list->length, sizeof(void *), list->method->cmp);
    uwlock(list);
}

extern void *bsearch(const void *key, const void *base, size_t n, size_t size, int (*cmp)(const void *, const void *));

const void *SearchList(List list, const void *value) {
    if (list == NULL) {
        return NULL;
    }
    rlock(list);
    const void *result = bsearch(value, list->value, list->length, sizeof(void *), list->method->cmp);
    urlock(list);
    return result;
}

SafePtr GetListIterator(List list) {
    int64_t now = INT64_MAX;
    if (list != NULL) {
        now = 0;
        rlock(list);
    }
    ListIterator iterator = lmalloc(sizeof(ListIteratorNode));
    iterator->list = list;
    iterator->now = now;
    return newSafePtr(iterator);
}

void FreListIterator(ListIterator iterator) {
    if(iterator==NULL){
        return;
    }
    if (iterator->list != NULL) {
        urlock(iterator->list);
    }
    lfree(iterator);
}

bool_t HasNextListIterator(ListIterator iterator) {
    return iterator->list == NULL ? false : (iterator->now < iterator->list->length);
}

const void *NextListIterator(ListIterator iterator) {
    return GetList(iterator->list, iterator->now++);
}