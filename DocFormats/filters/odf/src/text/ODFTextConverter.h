// This file is part of the Corinthia project (http://corinthia.io).
//
// See the COPYRIGHT.txt file distributed with this work for
// information regarding copyright ownership.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <DocFormats/DFStorage.h>
#include "DFDOM.h"
#include "ODFPackage.h"

typedef struct ODFTextConverter ODFTextConverter;

struct ODFTextConverter {
    size_t retainCount;
    DFDocument *html;
    DFStorage *abstractStorage;
    ODFPackage *package;
    char *idPrefix;
};

ODFTextConverter *ODFTextConverterNew(DFDocument *html,
                                      DFStorage *abstractStorage,
                                      ODFPackage *package,
                                      const char *idPrefix);
ODFTextConverter *ODFTextConverterRetain(ODFTextConverter *conv);
void ODFTextConverterRelease(ODFTextConverter *conv);
