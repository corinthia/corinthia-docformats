
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

source_group(DocFormats\\core\\css .*)


set(src_css
    src/css/CSS.c
    src/css/CSSClassNames.c
    src/css/CSSLength.c
    src/css/CSSParser.c
    src/css/CSSProperties.c
    src/css/CSSSelector.c
    src/css/CSSSheet.c
    src/css/CSSStyle.c
    src/css/CSSSyntax.c
    PARENT_SCOPE)
