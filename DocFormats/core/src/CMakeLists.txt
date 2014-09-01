
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

include_directories(/usr/include/libxml2)
include_directories(../../3rdparty/headers)

source_group(DocFormats\\core\\headers headers/*})

set(GroupCommon
    common/DFBDT.c
    common/DFTable.c)
source_group(DocFormats\\core\\common common/*)

set(GroupPlatform
    platform/Apple.c
    platform/Linux.c
    platform/Unix.c
    platform/Win32.c)
source_group(DocFormats\\core\\platform platform/*)

set(GroupCSS
    css/CSS.c
    css/CSSClassNames.c
    css/CSSLength.c
    css/CSSParser.c
    css/CSSParser.h
    css/CSSProperties.c
    css/CSSSelector.c
    css/CSSSheet.c
    css/CSSStyle.c
    css/CSSSyntax.c
    css/CSSSyntax.h)
source_group(DocFormats\\core\\css css/*)

set(GroupLib
    lib/DFAllocator.c
    lib/DFAllocator.h
    lib/DFArray.c
    lib/DFBuffer.c
    lib/DFCallback.c
    lib/DFCallback.h
    lib/DFCharacterSet.c
    lib/DFError.c
    lib/DFFilesystem.c
    lib/DFHashTable.c
    lib/DFString.c
    lib/DFZipFile.c)
source_group(DocFormats\\core\\lib lib/*)

set(GroupNames
    names/DFXMLNames.c
    names/DFXMLNames.h
    names/DFXMLNamespaces.c
    names/DFXMLNamespaces.h)
source_group(DocFormats\\core\\names names/*)

set(GroupXML
    xml/DFDOM.c
    xml/DFMarkupCompatibility.c
    xml/DFMarkupCompatibility.h
    xml/DFNameMap.c
    xml/DFNameMap.h
    xml/DFXML.c)
source_group(DocFormats\\core\\xml xml/*)

add_library(DocFormats
    ${GroupHeaders}
    ${GroupCommon}
    ${GroupPlatform}
    ${GroupCSS}
    ${GroupLib}
    ${GroupNames}
    ${GroupXML})

