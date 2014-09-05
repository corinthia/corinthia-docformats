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
#include <stdio.h>
#include <string.h>
#include "DocFormats_test.h"



void doEntityTest(int verbose, char *entityName, int *runTest, int *failTest,
                  int (*funcptr)(int, char*, char*))
{
  int i, rc;
  char testName[200], errorText[200];

  if (verbose)
    printf("--- Test:   %s\n", entityName);
  *runTest = *failTest = 0;

  // loop through all local test cases
  for (i = 1;; ++i)
  {
    snprintf(testName, 100, "test %d", i);
    errorText[0] = '\0';

    // run test
    rc = funcptr(i, testName, errorText);
    
    // Check result 
    //     = 0 Test skipped
    if (!rc)
      continue;
    //    -999 No higher test cases
    if (rc == NO_MORE_TEST_CASES)
      break;
    ++*runTest;

    //     > 0 SUCCESS
    if (rc > 0)
    {
      if (verbose == 2)
        printf("%s SUCCESS\n", testName);
    }
    else
    {
      printf("%s FAILED with %d (%s)\n", testName, rc, errorText);
      ++*failTest;
    }
  }
}


int main(int argc, const char * argv[])
{
  int vb = 2;
  int rT, fT;

  doEntityTest(vb, "3rdparty",      &rT, &fT, test_3rdparty);
  doEntityTest(vb, "core platform", &rT, &fT, test_core_platform);
  doEntityTest(vb, "core lib",      &rT, &fT, test_core_lib);
  doEntityTest(vb, "core common",   &rT, &fT, test_core_common);
  doEntityTest(vb, "core names",    &rT, &fT, test_core_names);
  doEntityTest(vb, "core data",     &rT, &fT, test_core_data);
  doEntityTest(vb, "filter latex",  &rT, &fT, test_filter_latex);
  doEntityTest(vb, "filter odf",    &rT, &fT, test_filter_odf);
  doEntityTest(vb, "filter ooxml",  &rT, &fT, test_filter_ooxml);
  doEntityTest(vb, "filter html",   &rT, &fT, test_filter_html);
  doEntityTest(vb, "api",           &rT, &fT, test_api);
}
