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
#include "ODF.h"
#include "DFCommon.h"
#include "ODFConverter.h"

#include <stdio.h>

DFDocument *ODFGet(DFStorage *concreteStorage, DFStorage *abstractStorage, const char *idPrefix, DFError **error)
{
    int ok = 0;
    DFDocument *html = NULL;
    ODFPackage *package = NULL;

    printf("ODFGet\n");
    package = ODFPackageOpenFrom(concreteStorage, error);
    if (package == NULL)
        goto end;
    printf("ODFGet\n");
    html = DFDocumentNew();
    if(ODFConverterGet(html, abstractStorage, package, idPrefix, error) == 0)
        goto end;
    ok = 1;

end:
    ODFPackageRelease(package);
    if (!ok) {
        DFDocumentRelease(html);
        return NULL;
    }
    return html;
}

int ODFPut(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, const char *idPrefix, DFError **error)
{
    int ok = 0;
    ODFPackage *ODFPackage = NULL;

    ODFPackage = ODFPackageOpenFrom(concreteStorage,error);
    if (ODFPackage == NULL)
        goto end;

    if (!ODFConverterPut(htmlDoc,abstractStorage,ODFPackage,idPrefix,error))
        goto end;

    if (!ODFPackageSave(ODFPackage,error))
        goto end;

    ok = 1;

    end:
    ODFPackageRelease(ODFPackage);
    return ok;
}

int ODFCreate(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, DFError **error)
{
    DFErrorFormat(error, "not implemented");
    return 0;
}
