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

add_subdirectory(platform)
add_subdirectory(lib)
add_subdirectory(common)
add_subdirectory(names)
add_subdirectory(data)


###
## identify objects to caller
###
set(obj_test
    ${obj_test_platform}
    ${obj_test_lib}
    ${obj_test_common}
    ${obj_test_names}
    ${obj_test_data}
    PARENT_SCOPE
   )

