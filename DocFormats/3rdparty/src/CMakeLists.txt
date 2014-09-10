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
## build minzip objects
###
set(minizip
    ../external/minizip/crypt.h
    ../external/minizip/ioapi.c
    ../external/minizip/ioapi.h
    ../external/minizip/unzip.c
    ../external/minizip/unzip.h
    ../external/minizip/zip.c
    ../external/minizip/zip.h
   )
source_group(minizip FILES ${minizip})

set(html5
# NOT SUPPORTED            w3c-tidy-html5/license.html
    ../external/w3c-tidy-html5/include/buffio.h
    ../external/w3c-tidy-html5/include/platform.h
    ../external/w3c-tidy-html5/include/tidyenum.h
    ../external/w3c-tidy-html5/include/tidy.h
    ../external/w3c-tidy-html5/src/access.c
    ../external/w3c-tidy-html5/src/access.h
    ../external/w3c-tidy-html5/src/alloc.c
    ../external/w3c-tidy-html5/src/attrask.c
    ../external/w3c-tidy-html5/src/attrdict.c
    ../external/w3c-tidy-html5/src/attrdict.h
    ../external/w3c-tidy-html5/src/attrget.c
    ../external/w3c-tidy-html5/src/attrs.c
    ../external/w3c-tidy-html5/src/attrs.h
    ../external/w3c-tidy-html5/src/buffio.c
    ../external/w3c-tidy-html5/src/charsets.c
    ../external/w3c-tidy-html5/src/charsets.h
    ../external/w3c-tidy-html5/src/clean.c
    ../external/w3c-tidy-html5/src/clean.h
    ../external/w3c-tidy-html5/src/config.c
    ../external/w3c-tidy-html5/src/config.h
    ../external/w3c-tidy-html5/src/entities.c
    ../external/w3c-tidy-html5/src/entities.h
    ../external/w3c-tidy-html5/src/fileio.c
    ../external/w3c-tidy-html5/src/fileio.h
    ../external/w3c-tidy-html5/src/forward.h
    ../external/w3c-tidy-html5/src/gdoc.c
    ../external/w3c-tidy-html5/src/gdoc.h
    ../external/w3c-tidy-html5/src/iconvtc.c
    ../external/w3c-tidy-html5/src/iconvtc.h
    ../external/w3c-tidy-html5/src/istack.c
    ../external/w3c-tidy-html5/src/lexer.c
    ../external/w3c-tidy-html5/src/lexer.h
    ../external/w3c-tidy-html5/src/localize.c
    ../external/w3c-tidy-html5/src/mappedio.c
    ../external/w3c-tidy-html5/src/mappedio.h
    ../external/w3c-tidy-html5/src/message.h
    ../external/w3c-tidy-html5/src/parser.c
    ../external/w3c-tidy-html5/src/parser.h
    ../external/w3c-tidy-html5/src/pprint.c
    ../external/w3c-tidy-html5/src/pprint.h
    ../external/w3c-tidy-html5/src/streamio.c
    ../external/w3c-tidy-html5/src/streamio.h
    ../external/w3c-tidy-html5/src/tagask.c
    ../external/w3c-tidy-html5/src/tags.c
    ../external/w3c-tidy-html5/src/tags.h
    ../external/w3c-tidy-html5/src/tidy-int.h
    ../external/w3c-tidy-html5/src/tidylib.c
    ../external/w3c-tidy-html5/src/tmbstr.c
    ../external/w3c-tidy-html5/src/tmbstr.h
    ../external/w3c-tidy-html5/src/utf8.c
    ../external/w3c-tidy-html5/src/utf8.h
    ../external/w3c-tidy-html5/src/version.h
    ../external/w3c-tidy-html5/src/win32tc.c
    ../external/w3c-tidy-html5/src/win32tc.h
   )
source_group(w3c-tidy-html5 FILES ${w3c-tidy-html5})
    



###
## build src object files
###
include_directories()
include_directories(SYSTEM ${INCLUDE_DIRS})
include_directories(../external/minizip)
include_directories(../external/w3c-tidy-html5/include)
include_directories(../external/w3c-tidy-html5/src)
add_library(obj_3rdparty_src OBJECT
            ../headers/3rdparty.h
            wrapper.c
            ${minizip}
            ${html5}
           )
set_property(TARGET obj_3rdparty_src PROPERTY FOLDER DocFormats/3rdparty)

###
## identify object files to caller
###
set(obj_src
    $<TARGET_OBJECTS:obj_3rdparty_src>
    PARENT_SCOPE
   )

