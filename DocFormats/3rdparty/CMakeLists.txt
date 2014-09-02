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
## Collect source information
###
add_subdirectory(headers)
add_subdirectory(external)
add_subdirectory(src)


add_library(3rdparty
            ${obj_external}
            ${obj_src}
           )

add_subdirectory(tests)
