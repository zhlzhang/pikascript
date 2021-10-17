#ifndef __PIKA__VM__H
#define __PIKA__VM__H
#include "PikaObj.h"

Args* pikaVM_run(PikaObj* self, char* pyLine);
Args* pikaVM_runAsm(PikaObj* self, char* pikaAsm);
int32_t pikaVM_runAsmLine(PikaObj* self,
                          char* pikaAsm,
                          int32_t lineAddr,
                          Args* sysRes);
int32_t __clearInvokeQueues(PikaObj* self);

#endif