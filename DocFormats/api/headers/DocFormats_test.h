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

//---------------------------
// Black box test functions are local in every module
//---------------------------
// Result are always:
//     > 0 SUCCESS
//     = 0 Test skipped
//     < 0 FAILED
//    -999 No higher test cases
// testName will be filled with name of test case
// errorText will be filled for failures
//---------------------------
#define NO_MORE_TEST_CASES -999
extern int test_3rdparty      (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_core_platform (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_core_lib      (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_core_common   (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_core_names    (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_core_data     (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_filter_latex  (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_filter_odf    (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_filter_ooxml  (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_filter_html   (int   runTest,
                               char *textName,
                               char *errorText);
extern int test_api           (int   runTest,
                               char *textName,
                               char *errorText);

