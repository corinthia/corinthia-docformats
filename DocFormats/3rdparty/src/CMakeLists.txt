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
## build src object files
###
include_directories(../external/minizip)
include_directories(../external/w3c-tidy-html5/include)
include_directories(../external/w3c-tidy-html5/src)
add_library(obj_3rdparty_src OBJECT
            ../headers/3rdparty.h
            wrapper.c
           )
set_property(TARGET obj_3rdparty_src PROPERTY FOLDER DocFormats/3rdparty)

###
## identify object files to caller
###
set(obj_src
    $<TARGET_OBJECTS:obj_3rdparty_src>
    PARENT_SCOPE
   )

