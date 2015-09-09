// This file was automatically generated using schemas/generate.sh. Do not edit.

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

#ifndef _DFXMLNamespaces_h
#define _DFXMLNamespaces_h

enum {
    NAMESPACE_NULL,
    NAMESPACE_XML,
    NAMESPACE_DC,
    NAMESPACE_ANNOTATIONS,
    NAMESPACE_DML_CHART,
    NAMESPACE_DML_CHART_DRAWING,
    NAMESPACE_DML_DIAGRAM,
    NAMESPACE_DML_MAIN,
    NAMESPACE_DML_PICTURE,
    NAMESPACE_DML_SS,
    NAMESPACE_DML_WP,
    NAMESPACE_DML_LC,
    NAMESPACE_CUSTOMXML,
    NAMESPACE_MATH,
    NAMESPACE_OREL,
    NAMESPACE_SHARED,
    NAMESPACE_CHARACTERISTICS,
    NAMESPACE_BIB,
    NAMESPACE_CUSTOMPR,
    NAMESPACE_EXTENDEDPR,
    NAMESPACE_MC,
    NAMESPACE_PML,
    NAMESPACE_SL,
    NAMESPACE_SML,
    NAMESPACE_WORD,
    NAMESPACE_MATHML,
    NAMESPACE_HTML,
    NAMESPACE_XLINK,
    NAMESPACE_XFORMS,
    NAMESPACE_GRDDL,
    NAMESPACE_ANIM,
    NAMESPACE_CHART,
    NAMESPACE_CONFIG,
    NAMESPACE_DB,
    NAMESPACE_NUMBER,
    NAMESPACE_DR3D,
    NAMESPACE_DRAW,
    NAMESPACE_FORM,
    NAMESPACE_META,
    NAMESPACE_OFFICE,
    NAMESPACE_PRESENTATION,
    NAMESPACE_SCRIPT,
    NAMESPACE_SMIL,
    NAMESPACE_STYLE,
    NAMESPACE_SVG,
    NAMESPACE_TABLE,
    NAMESPACE_TEXT,
    NAMESPACE_FO,
    NAMESPACE_MSOFFICE_EXCEL,
    NAMESPACE_MSOFFICE,
    NAMESPACE_MSOFFICE_WORD,
    NAMESPACE_VML,
    NAMESPACE_RNG,
    NAMESPACE_REL,
    NAMESPACE_CT,
    NAMESPACE_SV,
    NAMESPACE_MF,
    NAMESPACE_CONV,
    NAMESPACE_LATEX,
    PREDEFINED_NAMESPACE_COUNT
};

typedef struct {
    const char *namespaceURI;
    const char *prefix;
} NamespaceDecl;

typedef unsigned int NamespaceID;

#ifndef NAMESPACE_C
extern const NamespaceDecl PredefinedNamespaces[PREDEFINED_NAMESPACE_COUNT];
#endif

#endif
