// Copyright 2012-2014 UX Productivity Pty Ltd
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <platform.h>
#include "DocFormats_test.h"



int test1(char *errorText, int sizeErrorText)
{
  DF_ONCE_DECL tx;


  if (sizeof(tx) == sizeof(int))
    return 1;

  snprintf(errorText, sizeErrorText,
           "got size=%d expected size(int)=%d",
           (int)sizeof(tx), (int)sizeof(int));
  return -1;
}


int test2(char *errorText, int sizeErrorText)
{
  // With pthreads, pthread_once_t (i.e. DF_ONCE_INIT) is an opaque value and we can't make any
  // assumptions about what it is supposed to be. In fact on Apple platforms it's not even
  // a scalar.
#ifdef WIN32
  int x = DF_ONCE_INIT;
  if (x == 0)
    return 1;

  snprintf(errorText, sizeErrorText,
           "PTHREAD_ONCE_INIT/INIT_ONCE_STATIC_INIT expected 0 is %d", x);
  return -1;
#else
  return 1;
#endif
}


static int runOnceCount;
static void runOnceTest(void)
{
  ++runOnceCount;
}



int test3(char *errorText, int sizeErrorText)
{
  DF_ONCE_DECL runOnceMutex = DF_ONCE_INIT;

  runOnceCount = 0;
  PlatformRunOnce(&runOnceMutex, runOnceTest);
  if (runOnceCount != 1)
  {
    snprintf(errorText, sizeErrorText,
             "f() called %d times, expected 1", runOnceCount);
    return -1;
  }

  PlatformRunOnce(&runOnceMutex, runOnceTest);
  if (runOnceCount != 1)
  {
    snprintf(errorText, sizeErrorText,
             "should block, f() called %d times, expected 1",
             runOnceCount);
    return -1;
  }
  return 1;
}



int test4(char *errorText, int sizeErrorText)
{
  DF_ONCE_DECL runOnceMutex1 = DF_ONCE_INIT;
  DF_ONCE_DECL runOnceMutex2 = DF_ONCE_INIT;

  runOnceCount = 0;
  PlatformRunOnce(&runOnceMutex1, runOnceTest);
  PlatformRunOnce(&runOnceMutex2, runOnceTest);
  if (runOnceCount != 2)
  {
    snprintf(errorText, sizeErrorText,
             "f() called %d times, expected 2", runOnceCount);
    return -1;
  }
  PlatformRunOnce(&runOnceMutex1, runOnceTest);
  PlatformRunOnce(&runOnceMutex2, runOnceTest);
  if (runOnceCount != 2)
  {
    snprintf(errorText, sizeErrorText,
             "should block, f() called %d times, expected 1",
             runOnceCount);
    return -1;
  }
  return 1;
}



int test5(char *errorText, int sizeErrorText)
{
  runOnceCount = 0;
  RUN_ONCE(runOnceTest);
  if (runOnceCount != 1)
  {
    snprintf(errorText, sizeErrorText,
             "f() called %d times, expected 1", runOnceCount);
    return -1;
  }

  for (int j = 0; j < 5; ++j)
    RUN_ONCE(runOnceTest);
  if (runOnceCount != 2)
  {
    snprintf(errorText, sizeErrorText,
             "should block, f() called %d times, expected 2",
             runOnceCount);
    return -1;
  }
  return 1;
}



int test6(char *errorText, int sizeErrorText)
{
  runOnceCount = 0;
  RUN_ONCE(runOnceTest);
  RUN_ONCE(runOnceTest);
  if (runOnceCount != 2)
  {
    snprintf(errorText, sizeErrorText,
             "f() called %d times, expected 2", runOnceCount);
    return -1;
  }

  for (int j = 0; j < 5; ++j)
  {
    RUN_ONCE(runOnceTest);
    RUN_ONCE(runOnceTest);
  }
  if (runOnceCount != 4)
  {
    snprintf(errorText, sizeErrorText,
             "should block, f() called %d times, expected 4",
             runOnceCount);
    return -1;
  }
  return 1;
}



int test7(char *errorText, int sizeErrorText)
{
  char test[20];


  snprintf(test, sizeof(test), "chk %d ok", 134);
  if (!strcmp(test, "chk 134 ok"))
    return 1;

  snprintf(errorText, sizeErrorText, "got <%s> expected <chk 134 ok>", test);
  return -1;
}



int test8(char *errorText, int sizeErrorText)
{
  if (!strcasecmp("check IGEN", "check igen"))
    return 1;

  snprintf(errorText, sizeErrorText,
           "expected 0 got %d", strcasecmp("check IGEN", "check igen"));
  return -1;
}




int test_core_platform(int   runTest,
                       char *testName,  int sizeTestName,
                       char *errorText, int sizeErrorText)
{
  switch (runTest)
  {
    case 1:
      strncpy(testName,
              "Control sizeof(pthread_once_t/INIT_ONCE)",
              sizeTestName);
    return test1(errorText, sizeErrorText);

    case 2:
      strncpy(testName,
              "Test RUN_ONCE init constant",
              sizeTestName);
      return test2(errorText, sizeErrorText);

  case 3:
    strncpy(testName,
            "PlatformRunOnce works singular",
            sizeTestName);
    return test3(errorText, sizeErrorText);

  case 4:
    strncpy(testName,
            "PlatformRunOnce combination test",
            sizeTestName);
    return test4(errorText, sizeErrorText);

  case 5:
    strncpy(testName,
            "RUN_ONCE works singular",
            sizeTestName);
    return test5(errorText, sizeErrorText);

  case 6:
    strncpy(testName,
            "RUN_ONCE combination test",
            sizeTestName);
    return test6(errorText, sizeErrorText);

  case 7:
    strncpy(testName,
            "snprintf test (different impl. on windows",
            sizeTestName);
    return test7(errorText, sizeErrorText);

  case 8:
    strncpy(testName,
            "strcasecmp test (different impl. on windows",
            sizeTestName);
    return test8(errorText, sizeErrorText);

  default:
    return NO_MORE_TEST_CASES;
  }
}

