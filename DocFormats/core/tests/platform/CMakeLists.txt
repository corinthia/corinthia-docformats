#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include_directories()


###
## Build test object files (white box test with access to everyting)
###
source_group(DocFormats\\core\\tests\\platform REGULAR_EXPRESSION .*)
include_directories(../../../api/headers)
include_directories(../../src/platform)
add_library(test_core_platform OBJECT
            test_core_platform.c
           )



###
## identify objects to caller
###
set(obj_test_platform
    $<TARGET_OBJECTS:test_core_platform>
    PARENT_SCOPE
   )

