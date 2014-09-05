
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
include_directories(../../../DocFormats/api/headers)
include_directories(../../../DocFormats/filters/ooxml/src/common)
include_directories(../../../DocFormats/filters/ooxml/src/word)
link_directories(${LIB_DIRS})

set(SOURCES
    BDTTest.c
    Commands.c
    DFChanges.c
    Plain.c
    Test.c
    TestCase.c
    TestFunctions.c
    TextPackage.c
    main.c)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SOURCES ${SOURCES} FunctionTests.m StringTests.m)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(dfutil ${SOURCES})
target_link_libraries(dfutil DocFormats ${LIBS})
