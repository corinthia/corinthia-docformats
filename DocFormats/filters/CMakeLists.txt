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
## build object files
###
add_subdirectory(latex)

add_library(jixtest
           ${obj_latex}
           )
add_library(jixtest_test
           ${obj_test_latex}
           )
return()



###
## Identify objects to caller
###
set(obj_core
    ${obj_src}
    PARENT_SCOPE
   )

# WARNING: PARENT_SCOPE is only 1 level so we need to repeat
set(obj_test_core
    ${obj_test}
    PARENT_SCOPE
   )


