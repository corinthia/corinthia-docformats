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


include_directories(SYSTEM ${INCLUDE_DIRS})


###
## build minzip objects
###
include_directories(minizip)
add_library(obj_3rdparty_external_minizip OBJECT
            minizip/crypt.h
            minizip/ioapi.c
            minizip/ioapi.h
            minizip/unzip.c
            minizip/unzip.h
            minizip/zip.c
            minizip/zip.h
           )
set_property(TARGET obj_3rdparty_external_minizip PROPERTY FOLDER DocFormats/3rdparty)

###
## build w3c-tidy-html5 objects
###
include_directories(w3c-tidy-html5/include)
include_directories(w3c-tidy-html5/src)
add_library(obj_3rdparty_external_w3c-tidy-html5 OBJECT
# NOT SUPPORTED            w3c-tidy-html5/license.html
            w3c-tidy-html5/include/buffio.h
            w3c-tidy-html5/include/platform.h
            w3c-tidy-html5/include/tidyenum.h
            w3c-tidy-html5/include/tidy.h
            w3c-tidy-html5/src/access.c
            w3c-tidy-html5/src/access.h
            w3c-tidy-html5/src/alloc.c
            w3c-tidy-html5/src/attrask.c
            w3c-tidy-html5/src/attrdict.c
            w3c-tidy-html5/src/attrdict.h
            w3c-tidy-html5/src/attrget.c
            w3c-tidy-html5/src/attrs.c
            w3c-tidy-html5/src/attrs.h
            w3c-tidy-html5/src/buffio.c
            w3c-tidy-html5/src/charsets.c
            w3c-tidy-html5/src/charsets.h
            w3c-tidy-html5/src/clean.c
            w3c-tidy-html5/src/clean.h
            w3c-tidy-html5/src/config.c
            w3c-tidy-html5/src/config.h
            w3c-tidy-html5/src/entities.c
            w3c-tidy-html5/src/entities.h
            w3c-tidy-html5/src/fileio.c
            w3c-tidy-html5/src/fileio.h
            w3c-tidy-html5/src/forward.h
            w3c-tidy-html5/src/gdoc.c
            w3c-tidy-html5/src/gdoc.h
            w3c-tidy-html5/src/iconvtc.c
            w3c-tidy-html5/src/iconvtc.h
            w3c-tidy-html5/src/istack.c
            w3c-tidy-html5/src/lexer.c
            w3c-tidy-html5/src/lexer.h
            w3c-tidy-html5/src/localize.c
            w3c-tidy-html5/src/mappedio.c
            w3c-tidy-html5/src/mappedio.h
            w3c-tidy-html5/src/message.h
            w3c-tidy-html5/src/parser.c
            w3c-tidy-html5/src/parser.h
            w3c-tidy-html5/src/pprint.c
            w3c-tidy-html5/src/pprint.h
            w3c-tidy-html5/src/streamio.c
            w3c-tidy-html5/src/streamio.h
            w3c-tidy-html5/src/tagask.c
            w3c-tidy-html5/src/tags.c
            w3c-tidy-html5/src/tags.h
            w3c-tidy-html5/src/tidy-int.h
            w3c-tidy-html5/src/tidylib.c
            w3c-tidy-html5/src/tmbstr.c
            w3c-tidy-html5/src/tmbstr.h
            w3c-tidy-html5/src/utf8.c
            w3c-tidy-html5/src/utf8.h
            w3c-tidy-html5/src/version.h
            w3c-tidy-html5/src/win32tc.c
            w3c-tidy-html5/src/win32tc.h
           )
set_property(TARGET obj_3rdparty_external_w3c-tidy-html5 PROPERTY FOLDER DocFormats/3rdparty)

###
## Identify objects to caller
###
set(obj_external
    $<TARGET_OBJECTS:obj_3rdparty_external_minizip>
    $<TARGET_OBJECTS:obj_3rdparty_external_w3c-tidy-html5>
    PARENT_SCOPE
   )


