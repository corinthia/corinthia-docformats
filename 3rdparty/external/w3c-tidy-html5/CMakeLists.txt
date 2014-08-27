
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

cmake_minimum_required(VERSION 2.8)
include_directories(include)
include_directories(src)
add_library(tidy
    src/access.c
    src/alloc.c
    src/attrask.c
    src/attrdict.c
    src/attrget.c
    src/attrs.c
    src/buffio.c
    src/charsets.c
    src/clean.c
    src/config.c
    src/entities.c
    src/fileio.c
    src/gdoc.c
    src/iconvtc.c
    src/istack.c
    src/lexer.c
    src/localize.c
    src/mappedio.c
    src/parser.c
    src/pprint.c
    src/streamio.c
    src/tagask.c
    src/tags.c
    src/tidylib.c
    src/tmbstr.c
    src/utf8.c
    src/win32tc.c
)
