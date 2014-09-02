
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
add_subdirectory(platform)
add_subdirectory(lib)

add_library(jix_core
            ${obj_platform}
            ${obj_lib}
           )
return()

add_subdirectory(common)
add_subdirectory(css)
add_subdirectory(names)
add_subdirectory(xml)

set(src_src
    ${src_common}
    ${src_platform}
    ${src_lib}
    ${src_css}
    ${src_names}
    ${src_xml}
    PARENT_SCOPE)
