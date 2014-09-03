
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
## Build ooxml spreadsheet filter objects
###
source_group(DocFormats\\filters\\ooxml\\spreadsheet .*)
include_directories(../../../../core/headers)
add_library(obj_filter_ooxml_spreadsheet OBJECT
            OOXMLSpreadsheet.c
           )


###
## Inform caller about objects
###
set(obj_spreadsheet
    $<TARGET_OBJECTS:obj_filter_ooxml_spreadsheet>
    PARENT_SCOPE)

