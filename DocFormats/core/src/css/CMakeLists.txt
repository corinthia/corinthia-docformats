
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
## Build css objects
###
include_directories(.)
include_directories(../lib)
include_directories(../common)
include_directories(../names)
include_directories(../../forward_decl_BAD)
add_library(obj_core_css OBJECT
            CSS.c
            CSS.h
            CSSLength.c
            CSSLength.h
            CSSParser.c
            CSSParser.h
            CSSProperties.c
            CSSProperties.h
            CSSSelector.c
            CSSSelector.h
            CSSSheet.c
            CSSSheet.h
            CSSStyle.c
            CSSStyle.h
            CSSSyntax.c
            CSSSyntax.h
           )
set_property(TARGET obj_core_css PROPERTY FOLDER DocFormats/core)


###
## Inform caller about object list
###
set(obj_css
    $<TARGET_OBJECTS:obj_core_css>
    PARENT_SCOPE
   )
                          
