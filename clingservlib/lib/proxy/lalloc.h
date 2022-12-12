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

#ifndef CLINGSERV_LALLOC_H
#define CLINGSERV_LALLOC_H

#include <stddef.h>

void *lmalloc(size_t size);

void *lcalloc(size_t nsize, size_t size);

void lfree(void *ptr);

void *lrealloc(void *ptr,size_t size);

#endif //CLINGSERV_LALLOC_H
