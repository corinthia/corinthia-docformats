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
## build object files
###
add_subdirectory(headers)
add_subdirectory(src)


add_library(jix_core
            ${obj_src}
           )

return()
add_subdirectory(tests)

###
## Build module library
###
include_directories()
include_directories(/usr/include/libxml2)
include_directories(../3rdparty/headers)
include_directories(src/names)
include_directories(src/common)
include_directories(src/lib)
include_directories(src/platform)
include_directories(src/xml)
include_directories(src/html)
include_directories(src/css)
add_library(core
            ${src_headers}
            ${src_src}
           )
add_library(test_core
            ${src_tests}
          )

