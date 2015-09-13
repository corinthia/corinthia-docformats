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
#include "DFDOM.h"
#include "DFString.h"
#include "DFHTML.h"
#include "DFCommon.h"
#include <stdlib.h>
#include "text/gbg_test.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                    ODFParagraphContentLens                                    //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////


static ODFLens *ODFParagraphContentLensForConcrete(ODFConverter *converter, DFNode *concrete)
{
    /*        switch (concrete->tag) {
        case DOMTEXT:
            return &ODFRunLens;
        case ODF_INS:
        case ODF_DEL:
        case ODF_MOVEFROM:
        case ODF_MOVETO:
            return &ODFChangeLens;
        case ODF_FLDSIMPLE:
            return &ODFFieldLens;
        case ODF_BOOKMARK:
            return &ODFBookmarkLens;
        case ODF_HYPERLINK:
            return &ODFHyperlinkLens;
        case ODF_SMARTTAG:
            return &ODFSmartTagLens;
        default:
            return NULL;
}*/
    return NULL;
}

/**
 * Could be a bunch of things here
 * for moment just look for the text
 */
static DFNode *ODFParagraphContentGet(ODFGetData *get, DFNode *concrete)
{
    printf(CYAN "ODFParagraphContentGet\n" RESET);
    printf("Tag %s\n", translateXMLEnumName[concrete->tag]);
    if (concrete->tag == DOM_TEXT) { // we have some text
        DFBuffer *buf = DFBufferNew();
        DFNodeTextToBuffer(concrete,buf);
        printf("Text %s\n", buf->data);
        DFNode *abstract = DFCreateTextNode(get->conv->html,buf->data);
        DFBufferRelease(buf);
        return abstract;
    }
    else { //not text could be a bunch of things - get the correct lens
/*        ODFLens *lens = ODFParagraphContentLensForConcrete(get->conv,concrete);
        if ((lens != NULL) && (lens->get != NULL))
            return lens->get(get,concrete);
        else {
            return NULL;
        }*/
        return NULL;
    }
}

static int ODFParagraphContentIsVisible(ODFPutData *put, DFNode *concrete)
{
    ODFLens *lens = ODFParagraphContentLensForConcrete(put->conv,concrete);
    if ((lens != NULL) && (lens->isVisible != NULL))
        return lens->isVisible(put,concrete);
    else
        return 0;
}

static void ODFParagraphContentPut(ODFPutData *put, DFNode *abstract, DFNode *concrete)
{
    printf(CYAN "ODFParagraphContentPut\n" RESET);
    ODFLens *lens = ODFParagraphContentLensForConcrete(put->conv,concrete);

    //lens will always be null for the moment
    //we need to get the abstract text and have the concrete side use it
    //That way we will pick up any edits. No point in comparing just update.
    printf("Con Tag %s\n", translateXMLEnumName[concrete->tag]);
    printf("Abs Tag %s\n", translateXMLEnumName[abstract->tag]);

    if( concrete->tag == DOM_TEXT && abstract->tag == DOM_TEXT) {

        DFSetNodeValue(concrete,abstract->value);
    }

/*    //We have at least 4 cases here (more when we take into account the other elements that may be decsendents of a paragraph
    if(abstract->first != NULL && concrete->first!=NULL)
    {
    } else if(abstract->first != NULL && concrete->first==NULL) {
        // the concrete paragraph should be deleted? There is no text
    } else if(abstract->first == NULL && concrete->first!=NULL) {
        // we need to add in text to a previously empty paragraph
    } else if(abstract->first = NULL && concrete->first==NULL) {
        // a do nothing case - was nothing and there is still nothing
    }*/

    //if ((lens != NULL) && (lens->put != NULL))
    //    lens->put(put,abstract,concrete);
}

static void ODFParagraphContentRemove(ODFPutData *put, DFNode *concrete)
{
    ODFLens *lens = ODFParagraphContentLensForConcrete(put->conv,concrete);
    if ((lens != NULL) && (lens->remove != NULL))
        lens->remove(put,concrete);
}

static DFNode *ODFParagraphContentCreate(ODFPutData *put, DFNode *abstract)
{
    return NULL;
}

ODFLens ODFParagraphContentLens = {
    .isVisible = ODFParagraphContentIsVisible,
    .get = ODFParagraphContentGet,
    .put = ODFParagraphContentPut,
    .create = ODFParagraphContentCreate,
    .remove = ODFParagraphContentRemove,
};
