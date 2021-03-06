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

#include "DFXMLNames.h"
#include "CSSSheet.h"
#include <DocFormats/DFXMLForward.h>
#include <DocFormats/DFError.h>
#include "CSSLength.h"

typedef struct CSSSize CSSSize;

struct CSSSize {
    CSSLength width;
    CSSLength height;
};

void HTMLAddExternalStyleSheet(DFDocument *doc, const char *href);
void HTMLAddInternalStyleSheet(DFDocument *doc, const char *cssText);
char *HTMLCopyCSSText(DFDocument *doc);

int HTML_isContainerTag(Tag tag);
int HTML_isBlockLevelTag(Tag tag);
int HTML_isParagraphTag(Tag tag);
int HTML_isListTag(Tag tag);
int HTML_isSpecialSpan(DFNode *node);
int HTML_isContentNode(DFNode *node);
int HTML_nodeHasContent(DFNode *node);
int HTML_nodeIsHyperlink(DFNode *node);
void HTML_safeIndent(DFNode *node, int depth);
void HTMLBreakBDTRefs(DFNode *node, const char *idPrefix);
CSSSize HTML_getImageDimensions(DFNode *img);

int isRRGGBB(const char *str);
int isHashRRGGBB(const char *str);

const char *HTMLMetaGet(DFDocument *htmlDoc, const char *name);
void HTMLMetaSet(DFDocument *htmlDoc, const char *name, const char *content);
void HTMLMetaRemove(DFDocument *htmlDoc, const char *name);

DFDocument *DFParseHTMLString(const char *str, int removeSpecial, DFError **error);
DFDocument *DFParseHTMLFile(const char *filename, int removeSpecial, DFError **error);
const char **DFHTMLGetImages(DFDocument *htmlDoc);
