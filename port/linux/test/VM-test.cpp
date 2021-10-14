#include "gtest/gtest.h"
extern "C" {
#include "BaseObj.h"
#include "PikaParser.h"
#include "PikaStdLib_SysObj.h"
#include "PikaVM.h"
#include "dataMemory.h"
#include "dataStrs.h"
}

TEST(VM, a_1) {
    char* line = (char*)"a = 1";
    Args* buffs = New_strBuff();
    char* pikaAsm = pikaParseToAsm(buffs, line);
    printf("%s", pikaAsm);
    PikaObj* root = newRootObj((char*)"root", New_PikaStdLib_SysObj);

    int lineAddr = 0;
    int size = strGetSize(pikaAsm);
    while (lineAddr < size) {
        lineAddr = pikaVM_run(root, pikaAsm, lineAddr);
    }

    obj_deinit(root);
    args_deinit(buffs);
    EXPECT_EQ(pikaMemNow(), 0);
}