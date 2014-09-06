
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
add_subdirectory(lib)
add_subdirectory(common)
add_subdirectory(names)
add_subdirectory(css)
add_subdirectory(html)
add_subdirectory(xml)

###
## Inform caller of object files
###
set(obj_src
    ${obj_lib}
    ${obj_common}
    ${obj_names}
    ${obj_css}
    ${obj_html}
    ${obj_xml}
    PARENT_SCOPE
   )


