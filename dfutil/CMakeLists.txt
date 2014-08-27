
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

cmake_minimum_required(VERSION 2.8)

set(SOURCES
    BDTTest.c
    Commands.c
    DFChanges.c
    Plain.c
    Test.c
    TestCase.c
    TestFunctions.c
    TextPackage.c
    main.c
)

set(LIBS DocFormats tidy minizip xml2 z)

include_directories(.)
include_directories(../DocFormats)
include_directories(../DocFormats/css)
include_directories(../DocFormats/html)
include_directories(../DocFormats/latex)
include_directories(../DocFormats/lib)
include_directories(../DocFormats/names)
include_directories(../DocFormats/odf)
include_directories(../DocFormats/word)
include_directories(../DocFormats/word/formatting)
include_directories(../DocFormats/word/lenses)
include_directories(../DocFormats/xml)
include_directories(/usr/include/libxml2)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(IMAGEIO_LIBRARY ImageIO)
    set(SOURCES ${SOURCES} FunctionTests.m StringTests.m)
    set(LIBS ${LIBS} iconv ${FOUNDATION_LIBRARY} ${IMAGEIO_LIBRARY})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
    set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g")
    set(LIBS ${LIBS} m pthread)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux") 

add_executable(dfutil ${SOURCES})
target_link_libraries(dfutil ${LIBS})
