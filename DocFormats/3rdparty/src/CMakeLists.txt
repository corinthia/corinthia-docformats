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


include_directories()
include_directories(../external/minizip)
include_directories(../external/w3c-tidy-html5/include)
include_directories(../external/w3c-tidy-html5/src)
source_group(DocFormats\\3rdparty\\src
             REGULAR_EXPRESSION .*)
add_library(obj_src_src OBJECT
            wrapper.c
           )

set(obj_src
    $<TARGET_OBJECTS:obj_src_src>
    PARENT_SCOPE
   )

