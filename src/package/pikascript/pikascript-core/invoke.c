#include "PikaObj.h"
#include "dataArgs.h"
#include "dataMemory.h"
#include "dataString.h"
#include "dataStrs.h"
#include <stdarg.h>

void *getNewObjFunByClass(PikaObj *obj, char *classPath)
{
    PikaObj *classLoader = args_getPtr(obj->attributeList, "__classLoader");
    if (NULL == classLoader)
    {
        return NULL;
    }
    void *(*newObjFun)(Args * initArgs) = args_getPtr(classLoader->attributeList, classPath);
    return newObjFun;
}

char *getDirectStr(Args *buffs, char *argPath)
{
    char *directStr = NULL;
    directStr = strsCut(buffs, argPath, '"', '"');
    if (NULL != directStr)
    {
        return directStr;
    }
    directStr = strsCut(buffs, argPath, '\'', '\'');
    if (NULL != directStr)
    {
        return directStr;
    }
    return NULL;
}

static int32_t loadArgByType(PikaObj *self,
                             char *definedName,
                             char *definedType,
                             char *argPath,
                             Args *args)
{
    if (strEqu(definedType, "any"))
    {
        char *directStr = getDirectStr(args, argPath);
        if (NULL != directStr)
        {
            /* direct string value */
            args_setStr(args, definedName, directStr);
            /* ok */
            return 0;
        }
        if ((argPath[0] >= '0') && (argPath[0] <= '9'))
        {
            /* direct number value */
            char *argName = argPath;
            if (strIsContain(argName, '.'))
            {
                args_setFloat(args, definedName, 0);
                args_set(args, definedName, argPath);
                /* succeed */
                return 0;
            }
            args_setInt(args, definedName, 0);
            args_set(args, definedName, argPath);
            /* succeed */
            return 0;
        }
        /* get reference arg */
        Arg *arg = obj_getArg(self, argPath);
        if (arg == NULL)
        {
            /* can not get arg */
            return 3;
        }
        Arg *argCopied = arg_copy(arg);
        argCopied = arg_setName(argCopied, definedName);
        args_setArg(args, argCopied);
        return 0;
    }
    if (strEqu(definedType, "str"))
    {
        /* solve the string type */
        char *directStr = getDirectStr(args, argPath);
        if (NULL != directStr)
        {
            /* direct value */
            args_setStr(args, definedName, directStr);
            /* ok */
            return 0;
        }
        /* reference value */
        char *refStr = obj_getStr(self, argPath);
        if (NULL == refStr)
        {
            /* faild */
            return 1;
        }
        args_setStr(args, definedName, refStr);
        /* succeed */
        return 0;
    }
    if (strEqu(definedType, "int"))
    {
        /* solve the int32_t type */
        args_setInt(args, definedName, 0);
        if ((argPath[0] >= '0') && (argPath[0] <= '9'))
        {
            /* direct value */
            args_set(args, definedName, argPath);
            /* succeed */
            return 0;
        }
        /* reference value */
        if (!obj_isArgExist(self, argPath))
        {
            /* can not get reference */
            return 3;
        }
        int32_t referenceVal = obj_getInt(self, argPath);
        args_setInt(args, definedName, referenceVal);
        /* succeed */
        return 0;
    }
    if (strEqu(definedType, "float"))
    {
        /* solve the float type */
        args_setFloat(args, definedName, 0);
        if ((argPath[0] >= '0') && (argPath[0] <= '9'))
        {
            /* direct value */
            args_set(args, definedName, argPath);
            /* succeed */
            return 0;
        }
        /* reference value */
        if (!obj_isArgExist(self, argPath))
        {
            /* can not get reference */
            return 3;
        }
        float referenceVal = obj_getFloat(self, argPath);
        args_setFloat(args, definedName, referenceVal);
        /* succeed */
        return 0;
    }
    if (strEqu(definedType, "pointer"))
    {
        /* only support reference value */
        if (!obj_isArgExist(self, argPath))
        {
            /* can not get reference */
            return 3;
        }
        void *ptr = obj_getPtr(self, argPath);
        args_setPtr(args, definedName, ptr);
        return 0;
    }
    /* type match faild */
    return 2;
}

char *getTypeVal(Args *buffs, char *typeToken)
{
    if (!strIsContain(typeToken, ':'))
    {
        return strsCopy(buffs, "");
    }
    return strsGetLastToken(buffs, typeToken, ':');
}




static void transferReturnVal(PikaObj *self, char *returnType, char *returnName, Args *args)
{
    if (strEqu("->int", returnType))
    {
        int returnVal = args_getInt(args, "return");
        obj_setInt(self, returnName, returnVal);
    }
    if (strEqu("->float", returnType))
    {
        float returnVal = args_getFloat(args, "return");
        obj_setFloat(self, returnName, returnVal);
    }
    if (strEqu("->str", returnType))
    {
        char *returnVal = args_getStr(args, "return");
        obj_setStr(self, returnName, returnVal);
    }
}


static Args *getArgsByNameMatch(PikaObj *self, char *typeList, char *argList)
{
    Args *buffs = New_strBuff();
    char *typeListBuff = strsCopy(buffs, typeList);
    Args *args = New_args(NULL);
    while (1)
    {
        char *typeToken = strsPopToken(buffs, typeListBuff, ',');
        /* poped all type from typeList */
        if (0 == typeToken[0])
        {
            break;
        }

        char *typeName = strsGetFirstToken(buffs, typeToken, ':');
        char *typeVal = getTypeVal(buffs, typeToken);

        char *argListBuff = strsCopy(buffs, argList);
        while (1)
        {
            char *argToken = strsPopToken(buffs, argListBuff, ',');
            char *argName = strsGetFirstToken(buffs, argToken, '=');
            char *argVal = strsGetLastToken(buffs, argToken, '=');

            if (0 == argToken[0])
            {
                /* arg poped finised */
                break;
            }

            if (!strEqu(typeName, argName))
            {
                /* name not match */
                continue;
            }

            if (0 != loadArgByType(self,
                                   typeName,
                                   typeVal,
                                   argVal,
                                   args))
            {
                args_deinit(args);
                args_deinit(buffs);
                return NULL;
            }
        }
    }
    args_deinit(buffs);
    return args;
}

static Args *getArgsBySort(PikaObj *self, char *typeList, char *argList)
{
    Args *buffs = New_strBuff();
    char *typeListBuff = strsCopy(buffs, typeList);
    char *argListBuff = strsCopy(buffs, argList);
    Args *args = New_args(NULL);
    while (1)
    {
        char *typeToken = strsPopToken(buffs, typeListBuff, ',');
        char *argToken = strsPopToken(buffs, argListBuff, ',');
        if ((0 == argToken[0]) || (0 == typeToken[0]))
        {
            /* arg or type poped finised */
            break;
        }

        char *typeName = strsGetFirstToken(buffs, typeToken, ':');
        char *typeVal = getTypeVal(buffs, typeToken);
        char *argPath = argToken;

        if (0 != loadArgByType(self,
                               typeName,
                               typeVal,
                               argPath,
                               args))
        {
            args_deinit(args);
            args_deinit(buffs);
            return NULL;
        }
    }
    args_deinit(buffs);
    return args;
}



static Args *getArgsBySentence(PikaObj *self, char *typeList, char *argList)
{
    if (strIsContain(argList, '='))
    {
        return getArgsByNameMatch(self, typeList, argList);
    }
    return getArgsBySort(self, typeList, argList);
}

static char *getMethodDeclearation(PikaObj *obj, char *methodName)
{
    Args *buffs = New_strBuff();
    char *methodDeclearationPath = strsAppend(buffs, "[methodDec]", methodName);
    char *res = obj_getStr(obj, methodDeclearationPath);
    args_deinit(buffs);
    return res;
}

static void *getMethodPtr(PikaObj *methodHost, char *methodName)
{
    Args *buffs = New_strBuff();
    char *methodPtrPath = strsAppend(buffs, "[methodPtr]", methodName);
    void *res = obj_getPtr(methodHost, methodPtrPath);
    args_deinit(buffs);
    return res;
}

static char *getCleanCmd(Args *buffs, char *cmd)
{
    int32_t size = strGetSize(cmd);
    char *strOut = args_getBuff(buffs, size);
    int32_t iOut = 0;
    char delChar = ' ';
    int32_t isInStr = 0;
    for (int32_t i = 0; i < strGetSize(cmd); i++)
    {
        if ('\'' == cmd[i] || '\"' == cmd[i])
        {
            isInStr = !isInStr;
        }
        if ((delChar == cmd[i]) && (!isInStr))
        {
            /* do not load char */
            continue;
        }
        strOut[iOut] = cmd[i];
        iOut++;
    }
    /* add \0 */
    strOut[iOut] = 0;
    return strOut;
}


char *getMethodPath(Args *buffs, char *methodToken)
{
    if (strIsContain(methodToken, '='))
    {
        return strsGetLastToken(buffs, methodToken, '=');
    }
    else
    {
        return methodToken;
    }
}

Args *obj_invoke(PikaObj *self, char *cmd)
{
    /* the Args returned need to be deinit */
    Args *res = New_args(NULL);
    args_setErrorCode(res, 0);
    Args *buffs = New_strBuff();
    char *cleanCmd = getCleanCmd(buffs, cmd);
    char *methodToken = strsGetFirstToken(buffs, cleanCmd, '(');
    char *methodPath = getMethodPath(buffs, methodToken);
    Args *args = NULL;

    PikaObj *methodHostObj = obj_getObj(self, methodPath, 1);
    PikaObj *methodHostClass = NULL;
    if (NULL == methodHostObj)
    {
        /* error, not found object */
        args_setErrorCode(res, 1);
        args_setSysOut(res, "[error] runner: object no found.");
        goto exit;
    }
    char *methodName = strsGetLastToken(buffs, methodPath, '.');

    void *classPtr = obj_getPtr(methodHostObj, "__classPtr");
    char *methodHostClassName = strsAppend(buffs, "classObj-", methodHostObj->name);
    methodHostClass = obj_getClassObjByNewFun(methodHostObj, methodHostClassName, classPtr);
    /* get method Ptr */
    void (*methodPtr)(PikaObj * self, Args * args) = getMethodPtr(methodHostClass, methodName);
    char *methodDecInClass = getMethodDeclearation(methodHostClass, methodName);
    /* assert method*/
    if ((NULL == methodDecInClass) || (NULL == methodPtr))
    {
        /* error, method no found */
        args_setErrorCode(res, 2);
        args_setSysOut(res, "[error] runner: method no found.");
        goto exit;
    }
    char *methodDec = strsCopy(buffs, methodDecInClass);
    /* free method host class to save memory */
    obj_deinit(methodHostClass);
    methodHostClass = NULL;

    /* get type list */
    char *typeList = strsCut(buffs, methodDec, '(', ')');
    if (typeList == NULL)
    {
        /* typeList no found */
        args_setErrorCode(res, 3);
        args_setSysOut(res, "[error] runner: type list no found.");
        goto exit;
    }

    /* get arg list */
    char *argList = strsCut(buffs, cleanCmd, '(', ')');
    {
        if (argList == NULL)
        {
            /* argL List no found */
            args_setErrorCode(res, 4);
            args_setSysOut(res, "[error] runner: arg list no found.");
            goto exit;
        }
    }

    /* get return type */
    char *returnType = strsGetLastToken(buffs, methodDec, ')');
    /* get args */
    args = getArgsBySentence(self, typeList, argList);
    if (NULL == args)
    {
        /* get args faild */
        args_setErrorCode(res, 5);
        args_setSysOut(res, "[error] runner: solve arg faild.");
        goto exit;
    }
    obj_setErrorCode(methodHostObj, 0);
    obj_setSysOut(methodHostObj, "");
    /* run method */
    methodPtr(methodHostObj, args);

    /* transfer return */
    if (strIsContain(methodToken, '='))
    {
        char *returnName = strsGetFirstToken(buffs, methodToken, '=');
        transferReturnVal(self, returnType, returnName, args);
    }
    /* transfer sysOut */
    char *sysOut = obj_getSysOut(methodHostObj);
    if (NULL != sysOut)
    {
        args_setSysOut(res, sysOut);
    }
    /* transfer errCode */
    if (0 != obj_getErrorCode(methodHostObj))
    {
        /* method error */
        args_setErrorCode(res, 6);
    }
    goto exit;
exit:
    if (NULL != buffs)
    {
        args_deinit(buffs);
    }
    if (NULL != methodHostClass)
    {
        obj_deinit(methodHostClass);
    }
    if (NULL != args)
    {
        args_deinit(args);
    }
    return res;
}
