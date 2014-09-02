
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
## Build object files
###
add_subdirectory(3rdparty)



###
## Build libraries from source
###
add_library(docformats
            ${obj_3rdparty}
           )
add_library(test_docformats
            ${obj_test_3rdparty}
           )



return()
add_subdirectory(core)



include_directories(/usr/include/libxml2)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)


include_directories(3rdparty/headers)

include_directories(core/headers)
include_directories(filters/html/src)
include_directories(filters/latex/src)
include_directories(filters/odf/src/common)
include_directories(filters/ooxml/src/common)
include_directories(filters/ooxml/src/word)
include_directories(filters/ooxml/src/word/formatting)
include_directories(filters/ooxml/src/word/lenses)

set(GroupHTML
    filters/html/src/DFHTDocument.c
    filters/html/src/DFHTDocument.h
    filters/html/src/DFHTML.c
    filters/html/src/DFHTML.h
    filters/html/src/DFHTMLNormalization.c
    filters/html/src/DFHTMLNormalization.h
    filters/html/src/DFHTMLTables.c
    filters/html/src/DFHTMLTables.h
    filters/html/src/DFTidyHelper.c
    filters/html/src/DFTidyHelper.h
    filters/html/src/DFTidyWrapper.c
    filters/html/src/DFTidyWrapper.h)

set(GroupLaTeX
    filters/latex/src/HTMLToLaTeX.c
    filters/latex/src/HTMLToLaTeX.h)

set(GroupODF
    filters/odf/src/common/ODF.c
    filters/odf/src/common/ODF.h
    filters/odf/src/common/ODFManifest.c
    filters/odf/src/common/ODFManifest.h
    filters/odf/src/common/ODFPackage.c
    filters/odf/src/common/ODFPackage.h
    filters/odf/src/common/ODFSheet.c
    filters/odf/src/common/ODFSheet.h)

set(GroupWord
    filters/ooxml/src/common/OPC.c
    filters/ooxml/src/common/OPC.h
    filters/ooxml/src/word/Word.c
    filters/ooxml/src/word/Word.h
    filters/ooxml/src/word/WordCaption.c
    filters/ooxml/src/word/WordCaption.h
    filters/ooxml/src/word/WordConverter.c
    filters/ooxml/src/word/WordConverter.h
    filters/ooxml/src/word/WordGC.c
    filters/ooxml/src/word/WordGC.h
    filters/ooxml/src/word/WordLists.c
    filters/ooxml/src/word/WordLists.h
    filters/ooxml/src/word/WordNotes.c
    filters/ooxml/src/word/WordNotes.h
    filters/ooxml/src/word/WordNumbering.c
    filters/ooxml/src/word/WordNumbering.h
    filters/ooxml/src/word/WordObjects.c
    filters/ooxml/src/word/WordObjects.h
    filters/ooxml/src/word/WordPackage.c
    filters/ooxml/src/word/WordPackage.h
    filters/ooxml/src/word/WordSection.c
    filters/ooxml/src/word/WordSection.h
    filters/ooxml/src/word/WordSettings.c
    filters/ooxml/src/word/WordSettings.h
    filters/ooxml/src/word/WordSheet.c
    filters/ooxml/src/word/WordSheet.h
    filters/ooxml/src/word/WordStyles.c
    filters/ooxml/src/word/WordStyles.h
    filters/ooxml/src/word/WordTheme.c
    filters/ooxml/src/word/WordTheme.h
    filters/ooxml/src/word/WordWhitespace.c
    filters/ooxml/src/word/WordWhitespace.h)

set(GroupWordFormatting
    filters/ooxml/src/word/formatting/WordCommonPr.c
    filters/ooxml/src/word/formatting/WordCommonPr.h
    filters/ooxml/src/word/formatting/WordNumPr.c
    filters/ooxml/src/word/formatting/WordNumPr.h
    filters/ooxml/src/word/formatting/WordPPr.c
    filters/ooxml/src/word/formatting/WordPPr.h
    filters/ooxml/src/word/formatting/WordRPr.c
    filters/ooxml/src/word/formatting/WordRPr.h
    filters/ooxml/src/word/formatting/WordTblPr.c
    filters/ooxml/src/word/formatting/WordTblPr.h)

set(GroupWordLenses
    filters/ooxml/src/word/lenses/WordBlockLevel.c
    filters/ooxml/src/word/lenses/WordBody.c
    filters/ooxml/src/word/lenses/WordBookmark.c
    filters/ooxml/src/word/lenses/WordBookmark.h
    filters/ooxml/src/word/lenses/WordChange.c
    filters/ooxml/src/word/lenses/WordDocument.c
    filters/ooxml/src/word/lenses/WordDrawing.c
    filters/ooxml/src/word/lenses/WordDrawing.h
    filters/ooxml/src/word/lenses/WordEquation.c
    filters/ooxml/src/word/lenses/WordField.c
    filters/ooxml/src/word/lenses/WordField.h
    filters/ooxml/src/word/lenses/WordHyperlink.c
    filters/ooxml/src/word/lenses/WordLenses.c
    filters/ooxml/src/word/lenses/WordLenses.h
    filters/ooxml/src/word/lenses/WordParagraph.c
    filters/ooxml/src/word/lenses/WordParagraphContent.c
    filters/ooxml/src/word/lenses/WordRun.c
    filters/ooxml/src/word/lenses/WordRunContent.c
    filters/ooxml/src/word/lenses/WordSmartTag.c
    filters/ooxml/src/word/lenses/WordTable.c)

add_library(DocFormats
    ${GroupCSS}
    ${GroupHTML}
    ${GroupLaTeX}
    ${GroupLib}
    ${GroupNames}
    ${GroupODF}
    ${GroupPlatform}
    ${GroupWord}
    ${GroupWordFormatting}
    ${GroupWordLenses}
    ${GroupXML})

source_group(filters\\odf FILES ${GroupODF})
source_group(filters\\html FILES ${GroupHTML})
source_group(filters\\latex FILES ${GroupLaTeX})
source_group(filters\\ooxml\\word FILES ${GroupWord})
source_group(filters\\ooxml\\word\\formatting FILES ${GroupWordFormatting})
source_group(filters\\ooxml\\word\\lenses FILES ${GroupWordLenses})
