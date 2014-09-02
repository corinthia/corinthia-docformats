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


include_directories()
source_group(DocFormats\\3rdparty\\external\\minizip
             REGULAR_EXPRESSION minizip/.*)
include_directories(minizip)
add_library(obj_3rdparty_external_minizip OBJECT
            minizip/ioapi.c
            minizip/unzip.c
            minizip/zip.c
           )



source_group(DocFormats\\3rdparty\\external\\w3c-tidy-html5
             REGULAR_EXPRESSION w3c-tidy-html5/.*)
include_directories(w3c-tidy-html5/include)
include_directories(w3c-tidy-html5/src)
add_library(obj_3rdparty_external_w3c-tidy-html5 OBJECT
            w3c-tidy-html5/src/access.c
            w3c-tidy-html5/src/alloc.c
            w3c-tidy-html5/src/attrask.c
            w3c-tidy-html5/src/attrdict.c
            w3c-tidy-html5/src/attrget.c
            w3c-tidy-html5/src/attrs.c
            w3c-tidy-html5/src/buffio.c
            w3c-tidy-html5/src/charsets.c
            w3c-tidy-html5/src/clean.c
            w3c-tidy-html5/src/config.c
            w3c-tidy-html5/src/entities.c
            w3c-tidy-html5/src/fileio.c
            w3c-tidy-html5/src/gdoc.c
            w3c-tidy-html5/src/iconvtc.c
            w3c-tidy-html5/src/istack.c
            w3c-tidy-html5/src/lexer.c
            w3c-tidy-html5/src/localize.c
            w3c-tidy-html5/src/mappedio.c
            w3c-tidy-html5/src/parser.c
            w3c-tidy-html5/src/pprint.c
            w3c-tidy-html5/src/streamio.c
            w3c-tidy-html5/src/tagask.c
            w3c-tidy-html5/src/tags.c
            w3c-tidy-html5/src/tidylib.c
            w3c-tidy-html5/src/tmbstr.c
            w3c-tidy-html5/src/utf8.c
            w3c-tidy-html5/src/win32tc.c
           )

set(obj_external
    $<TARGET_OBJECTS:obj_3rdparty_external_minizip>
    $<TARGET_OBJECTS:obj_3rdparty_external_w3c-tidy-html5>
    PARENT_SCOPE
   )

