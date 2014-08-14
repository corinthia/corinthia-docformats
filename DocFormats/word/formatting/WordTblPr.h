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

#ifndef DocFormats_WordTblPr_h
#define DocFormats_WordTblPr_h

#include "WordConverter.h"

void WordGetTblPr(DFNode *concrete, CSSProperties *table, CSSProperties *cell, struct WordSection *section, const char **styleId);
void WordPutTblPr(DFNode *concrete, CSSProperties *newTable, CSSProperties *newCell,
                  struct WordSection *section, const char *styleId);

void WordPutTrPr(DFNode *concrete, const char *oldJc, const char *newJc);

void WordGetTcPr(DFNode *concrete, CSSProperties *properties);
void WordPutTcPr2(DFNode *concrete, unsigned int gridSpan, const char *vMerge);
void WordPutTcPr1(DFNode *concrete, CSSProperties *newp);

#endif
