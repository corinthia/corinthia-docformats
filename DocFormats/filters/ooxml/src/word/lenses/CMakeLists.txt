
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
## Build ooxml word lenses filter objects
###
include_directories(../../../../../core/headers)
include_directories(..)
include_directories(../formatting)
include_directories(../../common)
add_library(obj_filter_ooxml_word_lenses OBJECT
            WordBlockLevel.c
            WordBody.c
            WordBookmark.c
            WordChange.c
            WordDocument.c
            WordDrawing.c
            WordEquation.c
            WordField.c
            WordHyperlink.c
            WordLenses.c
            WordParagraph.c
            WordParagraphContent.c
            WordRun.c
            WordRunContent.c
            WordSmartTag.c
            WordTable.c
           )
set_property(TARGET obj_filter_ooxml_word_lenses PROPERTY FOLDER DocFormats/core/filter/ooxml)


###
## Inform caller about objects
###
set(obj_lenses
    $<TARGET_OBJECTS:obj_filter_ooxml_word_lenses>
    PARENT_SCOPE)

