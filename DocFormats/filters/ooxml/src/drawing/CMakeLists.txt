
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
## Build ooxml drawing filter objects
###
include_directories(../../../../core/headers)
add_library(obj_filter_ooxml_drawing OBJECT
            OOXMLDrawing.c
           )
set_property(TARGET obj_filter_ooxml_drawing PROPERTY FOLDER DocFormats/core/filter/ooxml)


###
## Inform caller about objects
###
set(obj_drawing
    $<TARGET_OBJECTS:obj_filter_ooxml_drawing>
    PARENT_SCOPE)

