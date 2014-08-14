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

#include "WordWhitespace.h"
#include "DFDOM.h"
#include "DFFilesystem.h"
#include "DFClassNames.h"
#include "DFString.h"
#include "DFCommon.h"

static void addNbsps(DFNode *node, int inParagraph, int *havePrecedingSpace)
{
    switch (node->tag) {
        case WORD_P:
            inParagraph = 1;
            *havePrecedingSpace = 1;
            break;
        case DOM_TEXT: {
            if (node->parent->tag != WORD_T)
                break;
            uint32_t *chars = DFUTF8To32(node->value);
            size_t length = DFUTF32Length(chars);
            for (size_t i = 0; i < length; i++) {
                if (chars[i] == ' ') {
                    if (*havePrecedingSpace)
                        chars[i] = DFNbspChar;
                    else
                        *havePrecedingSpace = 1;
                }
                else {
                    *havePrecedingSpace = 0;
                }
            }
            char *value = DFUTF32to8(chars);
            DFSetNodeValue(node,value);
            free(value);
            free(chars);
            break;
        }
    }

    for (DFNode *child = node->first; child != NULL; child = child->next)
        addNbsps(child,inParagraph,havePrecedingSpace);
}

void WordAddNbsps(DFDocument *doc)
{
    int havePrecedingSpace = 0;
    addNbsps(doc->root,1,&havePrecedingSpace);
}

static void removeNbsps(DFNode *node)
{
    if (node->tag == DOM_TEXT) {
        uint32_t *chars = DFUTF8To32(node->value);
        size_t length = DFUTF32Length(chars);
        for (size_t i = 0; i < length; i++) {
            if (chars[i] == DFNbspChar)
                chars[i] = ' ';
        }
        char *value = DFUTF32to8(chars);
        DFSetNodeValue(node,value);
        free(value);
        free(chars);
    }

    for (DFNode *child = node->first; child != NULL; child = child->next)
        removeNbsps(child);
}

void WordRemoveNbsps(DFDocument *doc)
{
    removeNbsps(doc->docNode);
}
