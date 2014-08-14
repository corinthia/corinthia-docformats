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

#ifndef DocFormats_WordNumbering_h
#define DocFormats_WordNumbering_h

#include "WordConverter.h"
#include "DFXMLForward.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                          WordNumLevel                                          //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct WordNumLevel WordNumLevel;

struct WordNumLevel {
    int ilvl;
    char *numFmt;
    char *lvlText;
    DFNode *element;
};

WordNumLevel *WordNumLevelNew(DFNode *element);
const char *WordNumLevelToListStyleType(WordNumLevel *level);

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                         WordAbstractNum                                        //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct WordAbstractNum WordAbstractNum;

struct WordAbstractNum {
    char *abstractNumId;
    DFNode *element;
    int refCount;
    struct DFHashTable *levels;
};

void WordAbstractNumAddLevel(WordAbstractNum *abs, WordNumLevel *numLevel);
WordNumLevel *WordAbstractNumGetLevel(WordAbstractNum *abs, int ilvl);

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                         WordConcreteNum                                        //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct WordConcreteNum WordConcreteNum;

struct WordConcreteNum {
    char *numId;
    DFNode *element;
    WordAbstractNum *abstractNum;
    int referenceCount;
};

WordNumLevel *WordConcreteNumGetLevel(WordConcreteNum *con, int ilvl);

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                          WordNumbering                                         //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct WordNumbering WordNumbering;

WordNumbering *WordNumberingNew(WordPackage *package);
void WordNumberingFree(WordNumbering *num);
WordNumLevel *WordNumberingCreateLevel(WordNumbering *num, const char *type, const char *lvlText, int ilvl, int indent);
WordAbstractNum *WordNumberingCreateAbstractNum(WordNumbering *num);
WordAbstractNum *WordNumberingCreateAbstractNumWithType(WordNumbering *num, const char *type);
WordConcreteNum *WordNumberingConcreteWithId(WordNumbering *num, const char *numId);
WordConcreteNum *WordNumberingAddConcreteWithAbstract(WordNumbering *num, WordAbstractNum *abstractNum);
void WordNumberingRemoveConcrete(WordNumbering *num, WordConcreteNum *concrete);
void WordNumberingRemoveUnusedAbstractNums(WordNumbering *num);

#endif
