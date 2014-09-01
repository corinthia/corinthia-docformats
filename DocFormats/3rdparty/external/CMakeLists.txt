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


source_group(DocFormats\\3rdparty\\external\\minizip
             REGULAR_EXPRESSION minizip/.*)
source_group(DocFormats\\3rdparty\\external\\w3c-tidy-html5
             REGULAR_EXPRESSION w3c-tidy-html5/.*)

set(src_external
    external/minizip/ioapi.c
    external/minizip/unzip.c
    external/minizip/zip.c
    external/w3c-tidy-html5/src/access.c
    external/w3c-tidy-html5/src/alloc.c
    external/w3c-tidy-html5/src/attrask.c
    external/w3c-tidy-html5/src/attrdict.c
    external/w3c-tidy-html5/src/attrget.c
    external/w3c-tidy-html5/src/attrs.c
    external/w3c-tidy-html5/src/buffio.c
    external/w3c-tidy-html5/src/charsets.c
    external/w3c-tidy-html5/src/clean.c
    external/w3c-tidy-html5/src/config.c
    external/w3c-tidy-html5/src/entities.c
    external/w3c-tidy-html5/src/fileio.c
    external/w3c-tidy-html5/src/gdoc.c
    external/w3c-tidy-html5/src/iconvtc.c
    external/w3c-tidy-html5/src/istack.c
    external/w3c-tidy-html5/src/lexer.c
    external/w3c-tidy-html5/src/localize.c
    external/w3c-tidy-html5/src/mappedio.c
    external/w3c-tidy-html5/src/parser.c
    external/w3c-tidy-html5/src/pprint.c
    external/w3c-tidy-html5/src/streamio.c
    external/w3c-tidy-html5/src/tagask.c
    external/w3c-tidy-html5/src/tags.c
    external/w3c-tidy-html5/src/tidylib.c
    external/w3c-tidy-html5/src/tmbstr.c
    external/w3c-tidy-html5/src/utf8.c
    external/w3c-tidy-html5/src/win32tc.c
    PARENT_SCOPE
   )

