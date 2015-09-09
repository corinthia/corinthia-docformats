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

#include "DFPlatform.h"
#include "ODFTextConverter.h"
#include "DFString.h"
#include <stdlib.h>

ODFTextConverter *ODFTextConverterNew(DFDocument *html,
                                      DFStorage *abstractStorage,
                                      ODFPackage *package,
                                      const char *idPrefix)
{
    ODFTextConverter *conv = (ODFTextConverter *)calloc(1,sizeof(ODFTextConverter));
    conv->retainCount = 1;
    conv->html = DFDocumentRetain(html);
    conv->abstractStorage = DFStorageRetain(abstractStorage);
    conv->idPrefix = (idPrefix != NULL) ? xstrdup(idPrefix) : xstrdup("odf");
    conv->package = ODFPackageRetain(package);
    return conv;
}

ODFTextConverter *ODFTextConverterRetain(ODFTextConverter *conv)
{
    if (conv != NULL)
        conv->retainCount++;
    return conv;
}

void ODFTextConverterRelease(ODFTextConverter *conv)
{
    if ((conv == NULL) || (--conv->retainCount > 0))
        return;
    DFDocumentRelease(conv->html);
    DFStorageRelease(conv->abstractStorage);
    free(conv->idPrefix);
    ODFPackageRelease(conv->package);
    free(conv);
}
