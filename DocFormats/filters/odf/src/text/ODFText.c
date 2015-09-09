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
#include "ODFText.h"
#include "ODFPackage.h"

DFDocument *ODFTextGet(DFStorage *concreteStorage, DFStorage *abstractStorage, const char *idPrefix, DFError **error)
{
    // DFErrorFormat(error,"ODFTextGet: Not yet implemented.");

    int ok = 0;
    ODFPackage *odfPackage = NULL;
    DFDocument *htmlDoc = NULL;
    
    odfPackage = ODFPackageOpenFrom(concreteStorage,error);
    if (odfPackage == NULL)
        goto end;

    htmlDoc = DFDocumentNew();

    // WordConverterGet
    if (!ODFConverterGet(htmlDoc,abstractStorage,odfPackage,idPrefix,error))
        goto end;

    ok = 1;

end:
    /*
    ODFPackageRelease(odfPackage);
    if (ok) {
        return htmlDoc;
    }
    else {
        DFDocumentRelease(htmlDoc);
        return NULL;
    }
    */
    return NULL;
}

int ODFTextPut(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, const char *idPrefix, DFError **error)
{
    DFErrorFormat(error,"ODFTextPut: Not yet implemented");
    return 0;
}

int ODFTextCreate(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, DFError **error)
{
    DFErrorFormat(error,"ODFTextCreate: Not yet implemented");
    return 0;
}
