// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "DFPlatform.h"
#include "ODFLenses.h"
#include "DFHTML.h"
#include "DFNameMap.h"
#include "DFString.h"
#include "DFCommon.h"
#include <assert.h>
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

#include <stdlib.h>
#include <string.h>
#include "text/gbg_test.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                        ODFHeaderLens                                       //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * We know we have a header - but need to work out which level
 */

static DFNode *ODFHeaderCreateAbstractNode(ODFGetData *get, DFNode *concrete)
{
    DFNode *abstract = NULL;
    const char * styleName = DFGetAttribute(concrete,TEXT_STYLE_NAME);
    const char * outlevel = DFGetAttribute(concrete,TEXT_OUTLINE_LEVEL);
    if(outlevel != NULL) {
        int s_val = atoi(&outlevel[strlen(outlevel)-1]);
        if(s_val > 6) {
            abstract = ODFConverterCreateAbstract(get, HTML_DIV, concrete);
        } else {
            abstract = ODFConverterCreateAbstract(get, HTML_H1 + s_val - 1, concrete);
        }
    } else { //no outline level assume 1
        printf("Header with no ooutline level!!!\n");
        abstract = ODFConverterCreateAbstract(get, HTML_H1, concrete);;
    }
    if(styleName != NULL) {
        printf("Found style name %s\n", styleName);
        DFSetAttribute(abstract, HTML_CLASS, styleName); //DFGetAttribute(odfNode,TEXT_STYLE_NAME));
    }
  return abstract;
}

/**
 * For the moment just create an H1 tag
 * and treat as a paragraph
 */
static DFNode *ODFHeaderGet(ODFGetData *get, DFNode *concrete)
{
    //DFNode *abstract = ODFConverterCreateAbstract(get,HTML_H1,concrete);
    DFNode *abstract = ODFHeaderCreateAbstractNode(get, concrete);
    ODFContainerGet(get,&ODFParagraphContentLens,abstract,concrete);
    printf("Header tag %s\n", translateXMLEnumName[abstract->tag]);

    return abstract;
}

//We already know the concrete tag is TEXT_H
static void ODFHeaderPut(ODFPutData *put, DFNode *abstract, DFNode *concrete)
{
    printf(CYAN "ODFHeaderPut\n" RESET);
    //the isParagraph will check for a header... but not uniquely
    if (!HTML_isParagraphTag(abstract->tag) && (abstract->tag != HTML_FIGURE)) {
        printf(RED "Not a para or figure\n" RESET);
        return;
    }

    if (concrete->tag != TEXT_H) {
        printf(RED "Concrete not an H\n" RESET);
        return;
    }
    //we have an issue here in that there can be many descendents
    //and they could be straight DOM_TEXT too (which does not go through the BDT module )

    //all abstract text is in the matching abtract DOM Text - so only use the first DOM_TEXT found
    int allowText = 1;
    for (DFNode *child = concrete->first; child != NULL; child = child->next) {
        if (child->tag == DOM_TEXT) {
            printf("found DOM_TEXT\n" );
            if( allowText == 1) { //only trigger on the first
                allowText = 0;
                if(abstract->first != NULL) {
                    printf("new DOM_TEXT %s\n", abstract->first->value);
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
        printf(RED "Concrete empty H\n" RESET);
        if(abstract->first != NULL && abstract->first->tag == DOM_TEXT) {
            printf(RED "ADD a Concrete DOM_TEXT node\n" RESET);
            DFAppendChild(concrete,DFCreateTextNode(concrete->doc,abstract->first->value));
        } else {
            // the concrete paragraph should be deleted? There is no text
        }
    }
}

static DFNode *ODFHeaderCreate(ODFPutData *put, DFNode *abstract)
{
    DFNode *concrete = DFCreateElement(put->contentDoc,TEXT_P);
    ODFHeaderPut(put,abstract,concrete);
    return concrete;
}

static int ODFHeaderIsVisible(ODFPutData *put, DFNode *concrete)
{
    return 1;
}

static void ODFHeaderRemove(ODFPutData *put, DFNode *concrete)
{
//    for (DFNode *child = concrete->first; child != NULL; child = child->next)
//        ODFHeaderContentLens.remove(put,child);
}

ODFLens ODFHeaderLens = {
    .isVisible = ODFHeaderIsVisible,
    .get = ODFHeaderGet,
    .put = ODFHeaderPut,
    .create = ODFHeaderCreate,
    .remove = ODFHeaderRemove,
};
