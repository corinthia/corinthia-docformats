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
#include "ODFLenses.h"
#include "DFHTML.h"
#include "DFNameMap.h"
#include "DFString.h"
#include "DFCommon.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                        ODFParagraphLens                                       //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

static DFNode *ODFParagraphCreateAbstractNode(ODFGetData *get, DFNode *concrete)
{
    DFNode *abstract = NULL;
    abstract = ODFConverterCreateAbstract(get, HTML_P, concrete);
    const char * styleName = DFGetAttribute(concrete,TEXT_STYLE_NAME);
    if(styleName != NULL) {
        printf("Found style name %s\n", styleName);
        DFSetAttribute(abstract, HTML_CLASS, styleName); //DFGetAttribute(odfNode,TEXT_STYLE_NAME));
    }
    return abstract;
}

/**
 * Map to an HTML_P
 * and treat as a paragraph
 */
static DFNode *ODFParagraphGet(ODFGetData *get, DFNode *concrete)
{
    printf("ODFParagraphGet look at the content\n");

    //DFNode *abstract = ODFParagraphCreateAbstractNode(get,concrete);
    DFNode *abstract = ODFParagraphCreateAbstractNode(get, concrete);
    ODFContainerGet(get,&ODFParagraphContentLens,abstract,concrete);

    return abstract;
}

static void ODFParagraphPut(ODFPutData *put, DFNode *abstract, DFNode *concrete)
{
    printf(CYAN "ODFParagraphPut\n" RESET);
    if (!HTML_isParagraphTag(abstract->tag) && (abstract->tag != HTML_FIGURE)) {
        printf(RED "Not a para or figure\n" RESET);
        return;
    }

    if (concrete->tag != TEXT_P) {
        printf(RED "Concrete not a P\n" RESET);
        return;
    }
    //we have an issue here in that there can be many descendents
    //and they could be straight DOM_TEXT too (which does not go through the BDT module )

    //all abstract text is in the matching abtract DOM Text - so only use the first DOM_TEXT found
    int allowText = 1;
    for (DFNode *child = concrete->first; child != NULL; child = child->next) {
        if (child->tag == DOM_TEXT) {
            if( allowText == 1) { //only trigger on the first
                allowText = 0;
                if(abstract->first != NULL) {
                    ODFParagraphContentLens.put(put, abstract->first, concrete->first);
                } else {
                    // the concrete node should be deleted?
                    // can we do it in here?
                    // the case where we have some text a <text:s/> and more text is causing hassle
                    printf(RED "Remove Concrete node\n" RESET);
                }
            } else {
                printf(RED "Remove Concrete node allowText false\n" RESET);
                DFRemoveNode(child);
            }
        } else if(child->tag == TEXT_S) {
            printf(RED "Filter Space and remove the node\n" RESET);
        } else {
            allowText = 1;
            ODFContainerPut(put,&ODFParagraphContentLens,abstract,child);
        }
    }
    if (concrete->first == NULL) { //this was an empty paragraph
        printf(RED "Concrete empty P\n" RESET);
        if(abstract->first != NULL && abstract->first->tag == DOM_TEXT) {
            printf(RED "ADD a Concrete DOM_TEXT node\n" RESET);
            DFAppendChild(concrete,DFCreateTextNode(concrete->doc,abstract->first->value));
        } else {
            // the concrete paragraph should be deleted? There is no text
        }
    }
}

static DFNode *ODFParagraphCreate(ODFPutData *put, DFNode *abstract)
{
    printf(RED "ODFParagraphCreate\n" RESET);
    DFNode *concrete = DFCreateElement(put->contentDoc,TEXT_P);
    ODFParagraphPut(put,abstract,concrete);
    return concrete;
}

static int ODFParagraphIsVisible(ODFPutData *put, DFNode *concrete)
{
    return 1;
}

static void ODFParagraphRemove(ODFPutData *put, DFNode *concrete)
{
    for (DFNode *child = concrete->first; child != NULL; child = child->next)
        ODFParagraphContentLens.remove(put,child);
}

ODFLens ODFParagraphLens = {
    .isVisible = ODFParagraphIsVisible,
    .get = ODFParagraphGet,
    .put = ODFParagraphPut,
    .create = ODFParagraphCreate,
    .remove = ODFParagraphRemove,
};
