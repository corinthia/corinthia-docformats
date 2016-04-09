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



###
## group headers objects
###
#set(GroupHeaders
#    headers/DocFormats/DFError.h
#    headers/DocFormats/DFStorage.h
#    headers/DocFormats/DFXMLForward.h
#    headers/DocFormats/DocFormats.h
#    headers/DocFormats/Formats.h
#    headers/DocFormats/Operations.h)



###
## group api objects
###
set(GroupSrcCoverage
    src/ProductionCoverage.c
    src/ProductionCoverage.h
    )

#set(GroupTests
#    tests/APITests.c)



###
# Common include for all platform files
###
include_directories()
include_directories(/usr/include/libxml2)
include_directories(../DocFormats/3rdparty/external/w3c-tidy-html5/include)
include_directories(../DocFormats/3rdparty/external/w3c-tidy-html5/src)

include_directories(SYSTEM ${INCLUDE_DIRS})
include_directories(SYSTEM ../api/headers)
include_directories(../headers)
include_directories(../core/src/common)
include_directories(../core/src/css)
include_directories(../core/src/html)
include_directories(../core/src/lib)
include_directories(../core/src/names)
include_directories(../core/src/xml)



###
# Prebuild library (needed to use different compile options)
###
add_library(coverage OBJECT
    ${GroupSrcCoverage}
)

source_group(src     FILES ${GroupSrcCoverage})
#source_group(tests   FILES ${GroupTests})
set_property(TARGET coverage PROPERTY FOLDER DocFormats)
