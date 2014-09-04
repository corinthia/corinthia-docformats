
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
add_subdirectory(core)
add_subdirectory(filters)


###
## Build libraries from source
###
add_library(docformats
            ${obj_3rdparty}
            ${obj_core}
            ${obj_filters}
           )
add_library(test_docformats
            ${obj_test_3rdparty}
            ${obj_test_core}
            ${obj_test_filters}
           )

