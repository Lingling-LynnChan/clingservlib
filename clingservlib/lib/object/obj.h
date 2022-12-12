//
// Created by Lingling on 22-12-9 下午10:53.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_OBJ_H
#define CLINGSERV_OBJ_H

#include <stdint.h>

typedef struct {
    int (*cmp)(const void *, const void *);

    void *(*cpy)(const void *);

    uint64_t (*hash)(const void *);

    void (*free)(void *);
} ObjectMethod;

#endif //CLINGSERV_OBJ_H
