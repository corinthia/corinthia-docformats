
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

source_group(DocFormats\\core\\lib .*)


set(src_lib
    src/lib/DFAllocator.c
    src/lib/DFArray.c
    src/lib/DFBuffer.c
    src/lib/DFCallback.c
    src/lib/DFCharacterSet.c
    src/lib/DFError.c
    src/lib/DFFilesystem.c
    src/lib/DFHashTable.c
    src/lib/DFString.c
    src/lib/DFZipFile.c
    PARENT_SCOPE)
