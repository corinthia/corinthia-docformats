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
#ifdef WIN32
#include <windows.h>
#define DF_ONCE_INIT INIT_ONCE_STATIC_INIT
#define DF_ONCE_DECL INIT_ONCE
#else
#include <pthread.h>
#define DF_ONCE_INIT PTHREAD_ONCE_INIT
#define DF_ONCE_DECL pthread_once_t
#endif



int test1(char *errorText)
{
  DF_ONCE_DECL tx;


  if (sizeof(tx) == sizeof(int))
	  return 1;

  sprintf(errorText, "got size=%d expected size(int)=%d",
		      (int)sizeof(tx),
		      (int)sizeof(int));
  return -1;
}


int test2(char *errorText)
{
  int x = DF_ONCE_INIT;
  if (x == 0)
    return 1;

  sprintf(errorText, "PTHREAD_ONCE_INIT/INIT_ONCE_STATIC_INIT expected 0 is %d", x);
  return -1;
}


static int runOnceCount;
static void runOnceTest(void)
{
	++runOnceCount;
}



int test3(char *errorText)
{
  int runOnceMutex = DF_ONCE_INIT;

  runOnceCount = 0;
  PlatformRunOnce(&runOnceMutex, runOnceTest);
  if (runOnceCount != 1)
  {
    sprintf(errorText, "f() called %d times, expected 1", runOnceCount);
    return -1;
  }

  PlatformRunOnce(&runOnceMutex, runOnceTest);
  if (runOnceCount != 1)
  {
    sprintf(errorText, "should block, f() called %d times, expected 1",
            runOnceCount);
    return -1;
  }
  return 1;
}



int test4(char *errorText)
{
  int runOnceMutex1 = DF_ONCE_INIT;
  int runOnceMutex2 = DF_ONCE_INIT;

  runOnceCount = 0;
  PlatformRunOnce(&runOnceMutex1, runOnceTest);
  PlatformRunOnce(&runOnceMutex2, runOnceTest);
  if (runOnceCount != 2)
  {
    sprintf(errorText, "f() called %d times, expected 2", runOnceCount);
    return -1;
  }
  PlatformRunOnce(&runOnceMutex1, runOnceTest);
  PlatformRunOnce(&runOnceMutex2, runOnceTest);
  if (runOnceCount != 2)
  {
    sprintf(errorText, "should block, f() called %d times, expected 1",
            runOnceCount);
    return -1;
  }
  return 1;
}



int test5(char *errorText)
{
  runOnceCount = 0;
  RUN_ONCE(runOnceTest);
  if (runOnceCount != 1)
  {
    sprintf(errorText, "f() called %d times, expected 1", runOnceCount);
    return -1;
  }

  for (int j = 0; j < 5; ++j)
    RUN_ONCE(runOnceTest);
  if (runOnceCount != 2)
  {
    sprintf(errorText, "should block, f() called %d times, expected 2",
      runOnceCount);
    return -1;
  }
  return 1;
}



int test6(char *errorText)
{
  runOnceCount = 0;
  RUN_ONCE(runOnceTest);
  RUN_ONCE(runOnceTest);
  if (runOnceCount != 2)
  {
    sprintf(errorText, "f() called %d times, expected 2", runOnceCount);
    return -1;
  }

  for (int j = 0; j < 5; ++j)
  {
    RUN_ONCE(runOnceTest);
    RUN_ONCE(runOnceTest);
  }
  if (runOnceCount != 4)
  {
    sprintf(errorText, "should block, f() called %d times, expected 4",
      runOnceCount);
    return -1;
  }
  return 1;
}



int test7(char *errorText)
{
  char test[20];


  snprintf(test, sizeof(test), "chk %d ok", 134);
  if (!strcmp(test, "chk 134 ok"))
    return 1;

  sprintf(errorText, "got <%s> expected <chk 134 ok>", test);
  return -1;
}



int test8(char *errorText)
{
  if (!strcasecmp("check IGEN", "check igen"))
    return 1;

  sprintf(errorText, "expected 0 got %d", strcasecmp("check IGEN", "check igen"));
  return -1;
}




int test_core_platform(int runTest, char *testName, char *errorText)
{
  switch (runTest)
  {
    case 1:
      strcpy(testName,"Control sizeof(pthread_once_t/INIT_ONCE)");
	  return test1(errorText);

    case 2:
      strcpy(testName, "Test RUN_ONCE init constant");
      return test2(errorText);

	case 3:
		strcpy(testName, "PlatformRunOnce works singular");
		return test3(errorText);

  case 4:
    strcpy(testName, "PlatformRunOnce combination test");
    return test4(errorText);

  case 5:
    strcpy(testName, "RUN_ONCE works singular");
    return test5(errorText);

  case 6:
    strcpy(testName, "RUN_ONCE combination test");
    return test6(errorText);

  case 7:
    strcpy(testName, "snprintf test (different impl. on windows");
    return test7(errorText);

  case 8:
    strcpy(testName, "strcasecmp test (different impl. on windows");
    return test8(errorText);

  default:
    return NO_MORE_TEST_CASES;
  }
}

