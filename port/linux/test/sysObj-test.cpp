#include "gtest/gtest.h"
extern "C" {
#include "BaseObj.h"
#include "PikaStdLib_SysObj.h"
#include "TinyObj.h"
}

TEST(sysObj, print) {
    PikaObj* obj = newRootObj((char*)"test", New_PikaStdLib_SysObj);
    VM_Parameters* globals = obj_runDirect(obj, (char*)"print('hello world')");
    char* sysOut = args_getSysOut(globals->list);
    int errCode = args_getErrorCode(globals->list);
    printf("sysout = %s\r\n", sysOut);
    // ASSERT_STREQ((char*)"hello world", sysOut);
    ASSERT_EQ(0, errCode);
    // obj_deinit(globals);
    obj_deinit(obj);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(sysObj, noMethod) {
    PikaObj* obj = newRootObj((char*)"test", New_PikaStdLib_SysObj);
    VM_Parameters* globals = obj_runDirect(obj, (char*)"printttt('hello world')");
    char* sysOut = args_getSysOut(globals->list);
    int errCode = args_getErrorCode(globals->list);
    printf("sysout = %s\r\n", sysOut);
    ASSERT_EQ(1, strEqu((char*)"[error] runner: method no found.", sysOut));
    ASSERT_EQ(2, errCode);
    // obj_deinit(globals);
    obj_deinit(obj);
    EXPECT_EQ(pikaMemNow(), 0);
}
