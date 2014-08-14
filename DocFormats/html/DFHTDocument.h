// Copyright 2012-2014 UX Productivity Pty Ltd
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

#ifndef DocFormats_DFHTDocument_h
#define DocFormats_DFHTDocument_h

#include "tidy.h"
#include "buffio.h"
#include "DFError.h"
#include "DFBuffer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                          DFHTDocument                                          //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct DFHTDocument DFHTDocument;

struct DFHTDocument {
    TidyBuffer errbuf;
    TidyDoc doc;
};

DFHTDocument *DFHTDocumentNew();
void DFHTDocumentFree(DFHTDocument *htd);
int DFHTDocumentParseCString(DFHTDocument *htd, const char *str, DFError **error);
void DFHTDocumentRemoveUXWriteSpecial(DFHTDocument *htd);

#endif
