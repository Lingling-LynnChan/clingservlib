//
// Created by Lingling on 22-12-12 上午5:54.
// Github https://github.com/Lingling-LynnChan.
//
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