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

#include "../../lib/proxy/output.h"

#include <stdio.h>

void Error(const char *msg, const char *subMsg) {
    if (subMsg == NULL) {
        perror(msg);
    } else if (msg == NULL/*subMsg!=NULL*/) {
        fprintf(stderr, "%s\n", subMsg);
    } else {
        fprintf(stderr, "%s: %s\n", msg, subMsg);
    }
}

void Debug(const char *msg, const char *subMsg, char type) {
    if (subMsg == NULL) {
        printf("%c %s\n", type, msg);
    } else if (msg == NULL/*subMsg!=NULL*/) {
        printf("%c %s\n", type, subMsg);
    } else {
        printf("%c %s: %s\n", type, msg, subMsg);
    }
}
void std_init(){
#ifdef STD_LOG
    freopen("./output/stdout.log","w",stdout);
    freopen("./output/stdout.log","w",stderr);
#endif
    printf("d 输出流配置完成\n");
}