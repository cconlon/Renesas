/* unit.c API unit tests driver
 *
 * Copyright (C) 2006-2021 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef CyaSSL_UNIT_H
#define CyaSSL_UNIT_H

#include <wolfssl/ssl.h>
#include <wolfssl/test.h>    /* thread and tcp stuff */

#ifdef WOLFSSL_FORCE_MALLOC_FAIL_TEST
#define XABORT()
#else
#define XABORT() abort()
#endif

#ifndef WOLFSSL_PASSTHRU_ERR
#define Fail(description, result) do {                                         \
    printf("\nERROR - %s line %d failed with:", __FILE__, __LINE__);           \
    printf("\n    expected: "); printf description;                            \
    printf("\n    result:   "); printf result; printf("\n\n");                 \
    XABORT();                                                                  \
} while(0)
#else
#define Fail(description, result) do {                               \
    printf("\nERROR - %s line %d failed with:", __FILE__, __LINE__); \
    printf("\n    expected: ");printf description;                   \
    printf("\n    result:   "); printf result; printf("\n\n");       \
} while (0)
#endif

#define Assert(test, description, result) if (!(test)) Fail(description, result)

#define AssertTrue(x)    Assert( (x), ("%s is true",     #x), (#x " => FALSE"))
#define AssertFalse(x)   Assert(!(x), ("%s is false",    #x), (#x " => TRUE"))
#define AssertNotNull(x) Assert( (x), ("%s is not null", #x), (#x " => NULL"))

#define AssertNull(x) do {                              \
    PEDANTIC_EXTENSION void* _x = (void *) (x);         \
                                                        \
    Assert(!_x, ("%s is null", #x), (#x " => %p", _x)); \
} while(0)

#define AssertInt(x, y, op, er) do {                                           \
    int _x = (int)(x);                                                         \
    int _y = (int)(y);                                                         \
                                                                               \
    Assert(_x op _y, ("%s " #op " %s", #x, #y), ("%d " #er " %d", _x, _y));    \
} while(0)

#define AssertIntEQ(x, y) AssertInt(x, y, ==, !=)
#define AssertIntNE(x, y) AssertInt(x, y, !=, ==)
#define AssertIntGT(x, y) AssertInt(x, y,  >, <=)
#define AssertIntLT(x, y) AssertInt(x, y,  <, >=)
#define AssertIntGE(x, y) AssertInt(x, y, >=,  <)
#define AssertIntLE(x, y) AssertInt(x, y, <=,  >)

#define AssertStr(x, y, op, er) do {                                           \
    const char* _x = x;                                                        \
    const char* _y = y;                                                        \
    int   _z = (_x && _y) ? strcmp(_x, _y) : -1;                               \
                                                                               \
    Assert(_z op 0, ("%s " #op " %s", #x, #y),                                 \
                                            ("\"%s\" " #er " \"%s\"", _x, _y));\
} while(0)

#define AssertStrEQ(x, y) AssertStr(x, y, ==, !=)
#define AssertStrNE(x, y) AssertStr(x, y, !=, ==)
#define AssertStrGT(x, y) AssertStr(x, y,  >, <=)
#define AssertStrLT(x, y) AssertStr(x, y,  <, >=)
#define AssertStrGE(x, y) AssertStr(x, y, >=,  <)
#define AssertStrLE(x, y) AssertStr(x, y, <=,  >)

#define AssertPtr(x, y, op, er) do {                                           \
    void* _x = (void*)(x);                                                     \
    void* _y = (void*)(y);                                                     \
    Assert(_x op _y, ("%s " #op " %s", #x, #y), ("%p " #er " %p", _x, _y));    \
} while(0)

#define AssertPtrEq(x, y) AssertPtr(x, y, ==, !=)
#define AssertPtrNE(x, y) AssertPtr(x, y, !=, ==)
#define AssertPtrGT(x, y) AssertPtr(x, y,  >, <=)
#define AssertPtrLT(x, y) AssertPtr(x, y,  <, >=)
#define AssertPtrGE(x, y) AssertPtr(x, y, >=,  <)
#define AssertPtrLE(x, y) AssertPtr(x, y, <=,  >)


void ApiTest(void);
int  SuiteTest(int argc, char** argv);
int  HashTest(void);
void SrpTest(void);


#endif /* CyaSSL_UNIT_H */
