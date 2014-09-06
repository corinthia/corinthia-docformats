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
## gather object files
###
set(obj_common
    common/OOXMLTypedefs.h
    common/OPC.c
    common/OPC.h
   )
source_group(common FILES ${obj_common})

set(obj_drawing
    drawing/OOXMLDrawing.c
   )
source_group(drawing FILES ${obj_drawing})
   
set(obj_presentation
    presentation/OOXMLPresentation.c
   )
source_group(presentation FILES ${obj_presentation})

set(obj_spreadsheet
    spreadsheet/OOXMLSpreadsheet.c
   )
source_group(spreadsheet FILES ${obj_spreadsheet})

set(obj_word_formatting
    word/formatting/WordCommonPr.c
    word/formatting/WordCommonPr.h
    word/formatting/WordNumPr.c
    word/formatting/WordNumPr.h
    word/formatting/WordPPr.c
    word/formatting/WordPPr.h
    word/formatting/WordRPr.c
    word/formatting/WordRPr.h
    word/formatting/WordTblPr.c
    word/formatting/WordTblPr.h
   )
source_group(word\\formatting FILES ${obj_word_formatting})
  
set(obj_word_lenses
    word/lenses/WordBlockLevel.c
    word/lenses/WordBody.c
    word/lenses/WordBookmark.c
    word/lenses/WordBookmark.h
    word/lenses/WordChange.c
    word/lenses/WordDocument.c
    word/lenses/WordDrawing.c
    word/lenses/WordDrawing.h
    word/lenses/WordEquation.c
    word/lenses/WordField.c
    word/lenses/WordField.h
    word/lenses/WordHyperlink.c
    word/lenses/WordLenses.c
    word/lenses/WordLenses.h
    word/lenses/WordParagraph.c
    word/lenses/WordParagraphContent.c
    word/lenses/WordRun.c
    word/lenses/WordRunContent.c
    word/lenses/WordSmartTag.c
    word/lenses/WordTable.c
   )
source_group(word\\lenses FILES ${obj_word_lenses})

set(obj_word
    word/CSSClassNames.c
    word/CSSClassNames.h
    word/Word.c
    word/WordCaption.c
    word/WordCaption.h
    word/WordConverter.c
    word/WordConverter.h
    word/WordGC.c
    word/WordGC.h
    word/Word.h
    word/WordLists.c
    word/WordLists.h
    word/WordNotes.c
    word/WordNotes.h
    word/WordNumbering.c
    word/WordNumbering.h
    word/WordObjects.c
    word/WordObjects.h
    word/WordPackage.c
    word/WordPackage.h
    word/WordSection.c
    word/WordSection.h
    word/WordSettings.c
    word/WordSettings.h
    word/WordSheet.c
    word/WordSheet.h
    word/WordStyles.c
    word/WordStyles.h
    word/WordTheme.c
    word/WordTheme.h
    word/WordWhitespace.c
    word/WordWhitespace.h
   )
source_group(word FILES ${obj_word})


include_directories()


###
## Build ooxml common filter objects
###
include_directories(../../../core/headers)
include_directories(common)
include_directories(word)
include_directories(word/lenses)
include_directories(word/formatting)
add_library(obj_filter_ooxml OBJECT
            ${obj_common}
            ${obj_drawing}
            ${obj_presentation}
            ${obj_spreadsheet}
            ${obj_word}
            ${obj_word_formatting}
            ${obj_word_lenses}
           )
set_property(TARGET obj_filter_ooxml PROPERTY FOLDER DocFormats/filters/ooxml)



###
## Identify objects to caller
###
set(obj_src
    $<TARGET_OBJECTS:obj_filter_ooxml>
    PARENT_SCOPE
   )


