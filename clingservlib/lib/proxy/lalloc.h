//
// Created by Lingling on 22-12-11 下午12:37.
// Github https://github.com/Lingling-LynnChan.
//
#ifndef CLINGSERV_LALLOC_H
#define CLINGSERV_LALLOC_H

#include <stddef.h>

void *lmalloc(size_t size);

void *lcalloc(size_t nsize, size_t size);

void lfree(void *ptr);

void *lrealloc(void *ptr,size_t size);

#endif //CLINGSERV_LALLOC_H
