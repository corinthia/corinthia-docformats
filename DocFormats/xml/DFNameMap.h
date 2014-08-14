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

#ifndef DocFormats_DFNameMap_h
#define DocFormats_DFNameMap_h

#include "DFXMLNamespaces.h"
#include "DFXMLNames.h"
#include <libxml/xmlstring.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                            DFNameMap                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

/** TODO */
typedef struct DFNameMap DFNameMap;

DFNameMap *DFNameMapNew(void);
void DFNameMapFree(DFNameMap *map);

NamespaceID  DFNameMapFoundNamespace(DFNameMap *map, const xmlChar *URI, const xmlChar *prefix);
const NamespaceDecl *DFNameMapNamespaceForID(DFNameMap *map, NamespaceID nsId);
NamespaceID DFNameMapNamespaceCount(DFNameMap *map);

const TagDecl *DFNameMapNameForTag(DFNameMap *map, Tag tag);
Tag DFNameMapTagForName(DFNameMap *map, const xmlChar *URI, const xmlChar *localName);

const TagDecl *DFBuiltinMapNameForTag(Tag tag);
Tag DFBuiltinMapTagForName(const xmlChar *URI, const xmlChar *localName);

#endif
