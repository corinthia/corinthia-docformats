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

#ifndef DocFormats_OOXMLTypedefs_h
#define DocFormats_OOXMLTypedefs_h

// word/OPC.h
typedef struct OPCRelationship OPCRelationship;
typedef struct OPCRelationshipSet OPCRelationshipSet;
typedef struct OPCPart OPCPart;
typedef struct OPCContentTypes OPCContentTypes;
typedef struct OPCPackage OPCPackage;

// word/WordCaption.h
typedef struct WordCaption WordCaption;

// word/WordConverter.h
typedef struct WordGetData WordGetData;
typedef struct WordPutData WordPutData;
typedef struct WordConverter WordConverter;

// word/WordNotes.h
typedef struct WordNote WordNote;
typedef struct WordNoteGroup WordNoteGroup;

// word/WordNumbering.h
typedef struct WordNumLevel WordNumLevel;
typedef struct WordAbstractNum WordAbstractNum;
typedef struct WordConcreteNum WordConcreteNum;
typedef struct WordNumbering WordNumbering;

// word/WordObjects.h
typedef struct WordObjects WordObjects;

// word/WordPackage.h
typedef struct WordPackage WordPackage;

// word/WordSection.h
typedef struct WordSection WordSection;

// word/WordSheet.h
typedef struct WordStyle WordStyle;
typedef struct WordSheet WordSheet;

// word/WordTheme.h
typedef struct WordTheme WordTheme;

// word/lenses/WordBookmark.h
typedef enum WordBookmarkType WordBookmarkType;
typedef struct CaptionParts CaptionParts;
typedef struct WordBookmark WordBookmark;

// word/lenses/WordDrawing.h
typedef struct WordDrawing WordDrawing;

// word/lenses/WordLenses.h
typedef struct WordLens WordLens;


//////////////////////////////////////////////////////////////////
// ODF experiment... ignore this for now. 
//////////////////////////////////////////////////////////////////

// ODF/ODFCaption.h
typedef struct ODFCaption ODFCaption;

// ODF/ODFConverter.h
typedef struct ODFGetData ODFGetData;
typedef struct ODFPutData ODFPutData;
typedef struct ODFConverter ODFConverter;

// ODF/ODFNotes.h
typedef struct ODFNote ODFNote;
typedef struct ODFNoteGroup ODFNoteGroup;

// ODF/ODFNumbering.h
typedef struct ODFNumLevel ODFNumLevel;
typedef struct ODFAbstractNum ODFAbstractNum;
typedef struct ODFConcreteNum ODFConcreteNum;
typedef struct ODFNumbering ODFNumbering;

// ODF/ODFObjects.h
typedef struct ODFObjects ODFObjects;

// ODF/ODFSection.h
typedef struct ODFSection ODFSection;

// ODF/ODFTheme.h
typedef struct ODFTheme ODFTheme;

// ODF/lenses/ODFBookmark.h
typedef enum ODFBookmarkType ODFBookmarkType;
typedef struct ODFBookmark ODFBookmark;

// ODF/lenses/ODFDrawing.h
typedef struct ODFDrawing ODFDrawing;

// ODF/lenses/ODFLenses.h
typedef struct ODFLens ODFLens;


#endif
