
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
## Build platform objects
###
include_directories(../headers)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(platform_src Apple.c)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(platform_src Linux.c)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(platform_src Win32.c)
else()
message(FATAL_ERROR "platform not supported, please implement first")
endif()
add_library(obj_platform OBJECT
            ${platform_src}
            ../headers/platform.h
           )
set_property(TARGET obj_platform PROPERTY FOLDER DocFormats/platform)



###
## Identify objects to caller
###
set(obj_src
    $<TARGET_OBJECTS:obj_platform>
    PARENT_SCOPE)

