
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
include_directories(../../forward_decl_BAD)
add_library(obj_core_platform OBJECT
            Apple.c
            DFPlatform.h
            Linux.c
            Unix.c
            Win32.c
           )
set_property(TARGET obj_core_platform PROPERTY FOLDER DocFormats/core/src)



###
## Identify objects to caller
###
set(obj_platform
    $<TARGET_OBJECTS:obj_core_platform>
    PARENT_SCOPE)

