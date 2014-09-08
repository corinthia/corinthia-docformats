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
#include <pthread.h>

int test_core_platform(int runTest, char *testName, char *errorText)
{
  switch (runTest)
  {
    case 1:
      strcpy(testName,"Control sizeof(pthread_once_t/INIT_ONCE)");
#ifdef WIN32
      INIT_ONCE tx;
#else 
      pthread_once_t tx;
#endif
      if (sizeof(tx) == sizeof(int))
        return 1;

      sprintf(errorText, "got size=%d expected size(int)=%d",
                         sizeof(tx),
                         sizeof(int));
      return -1;
            
    default:
      return NO_MORE_TEST_CASES;
  }
}

