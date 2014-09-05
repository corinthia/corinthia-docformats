
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
project(Socrates)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# platform dependent stuff
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(IMAGEIO_LIBRARY ImageIO)
    set(LIBS ${LIBS} z xml2 ${FOUNDATION_LIBRARY} ${IMAGEIO_LIBRARY})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g")
    set(LIBS ${LIBS} m pthread z xml2)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/libs/zlib/include
        ${PROJECT_SOURCE_DIR}/libs/iconv/include
        ${PROJECT_SOURCE_DIR}/libs/libxml2/include)
    set(LIB_DIRS
        ${PROJECT_SOURCE_DIR}/libs/zlib/lib
        ${PROJECT_SOURCE_DIR}/libs/iconv/lib
        ${PROJECT_SOURCE_DIR}/libs/libxml2/lib)
    set(LIBS ${LIBS} libxml2 zdll iconv)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_subdirectory(DocFormats)
add_subdirectory(consumers)
