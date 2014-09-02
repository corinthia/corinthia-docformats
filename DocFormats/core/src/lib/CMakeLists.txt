
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
## Build lib objects
###
source_group(DocFormats\\core\\lib .*)
include_directories(../../../3rdparty/headers)
include_directories(../platform)
include_directories(../../forward_decl_BAD)
add_library(obj_core_lib OBJECT
            DFAllocator.c
            DFArray.c
            DFBuffer.c
            DFCallback.c
            DFCharacterSet.c
            DFError.c
            DFFilesystem.c
            DFHashTable.c
            DFString.c
            DFZipFile.c
           )

###
## Inform caller about object list
###
set(obj_lib
    $<TARGET_OBJECTS:obj_core_lib>
    PARENT_SCOPE
   )
