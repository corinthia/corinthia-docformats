
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

include_directories(SYSTEM ${INCLUDE_DIRS})


###
## Build html filter objects
###
source_group(DocFormats\\filters\\html .*)
include_directories(../../../3rdparty/headers)
include_directories(../../../core/headers)
add_library(obj_filter_html OBJECT
            DFHTDocument.c
            DFHTML.c
            DFHTMLNormalization.c
            DFTidyHelper.c
            DFTidyWrapper.c
           )


###
## Inform caller about objects
###
set(obj_src
    $<TARGET_OBJECTS:obj_filter_html>
    PARENT_SCOPE)

