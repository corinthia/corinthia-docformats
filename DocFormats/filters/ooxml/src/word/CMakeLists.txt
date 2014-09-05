
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
## build object files
###
add_subdirectory(formatting)
add_subdirectory(lenses)



include_directories()


###
## Build ooxml presentation filter objects
###
include_directories(../../../../core/headers)
include_directories(lenses)
include_directories(formatting)
include_directories(.)
include_directories(../common)
add_library(obj_filter_ooxml_word OBJECT
            CSSClassNames.c
            Word.c
            WordCaption.c
            WordConverter.c
            WordGC.c
            WordLists.c
            WordNotes.c
            WordNumbering.c
            WordObjects.c
            WordPackage.c
            WordSection.c
            WordSettings.c
            WordSheet.c
            WordStyles.c
            WordTheme.c
            WordWhitespace.c
           )
set_property(TARGET obj_filter_ooxml_word PROPERTY FOLDER DocFormats/filters/ooxml)


###
## Inform caller about objects
###
set(obj_word
    $<TARGET_OBJECTS:obj_filter_ooxml_word>
    ${obj_formatting}
    ${obj_lenses}
    PARENT_SCOPE)

