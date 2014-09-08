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
## group object files
###
set(obj_common
    common/ODF.c
    common/ODF.h
    common/ODFManifest.c
    common/ODFManifest.h
    common/ODFPackage.c
    common/ODFPackage.h
    common/ODFSheet.c
    common/ODFSheet.h
   )
source_group(common FILES ${obj_common})

set(obj_drawing
    drawing/ODFDrawing.c
   )
source_group(drawing FILES ${obj_drawing})

set(obj_presentation
    presentation/ODFPresentation.c
   )
source_group(presentation FILES ${obj_presentation})

set(obj_spreadsheet
    spreadsheet/ODFSpreadsheet.c
   )
source_group(spreadsheet FILES ${obj_spreadsheet})

set(obj_text
    text/ODFText.c
   )
source_group(text FILES ${obj_text})


include_directories()


###
## Build odf filter objects
###
include_directories(../../../platform/headers)
include_directories(../../../core/headers)
add_library(obj_filter_odf OBJECT
            ${obj_common}
            ${obj_drawing}
            ${obj_presentation}
            ${obj_spreadsheet}
            ${obj_text}
           )
set_property(TARGET obj_filter_odf PROPERTY FOLDER DocFormats/filters/odf)


###
## Inform caller about objects
###
set(obj_src
    $<TARGET_OBJECTS:obj_filter_odf>
    PARENT_SCOPE)


