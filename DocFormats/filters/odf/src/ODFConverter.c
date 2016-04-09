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
#include "ODFConverter.h"
#include "DFString.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ODFSheet.h"
#include "text/ODFText.h"
#include "lenses/ODFLenses.h"
#include "DFHTML.h"
#include "DFHTMLNormalization.h"
#include "ProductionCoverage.h"

#include "text/gbg_test.h"

#include <stdio.h>


static ODFConverter *ODFConverterNew(DFDocument *html, DFStorage *abstractStorage, ODFPackage *package, const char *idPrefix)
{
    ODFConverter *converter = (ODFConverter *)xcalloc(1,sizeof(ODFConverter));
    converter->html = DFDocumentRetain(html);
    converter->abstractStorage = DFStorageRetain(abstractStorage);
    assert(DFStorageFormat(converter->abstractStorage) == DFFileFormatHTML);
    converter->idPrefix = (idPrefix != NULL) ? xstrdup(idPrefix) : xstrdup("odf");
    converter->package = ODFPackageRetain(package);
    converter->styles = ODFSheetNew(converter->package->stylesDoc, converter->package->contentDoc);
    converter->warnings = DFBufferNew();
    return converter;
}

static void ODFConverterFree(ODFConverter *converter)
{
    DFDocumentRelease(converter->html);
    DFStorageRelease(converter->abstractStorage);
    free(converter->idPrefix);
    ODFSheetRelease(converter->styles);
    DFBufferRelease(converter->warnings);
    CSSSheetRelease(converter->styleSheet);
    ODFPackageRelease(converter->package);
    free(converter);
}

/*
 * Recursive walk to find the paragraph elements
 */
static void buildListMapFromHTML(WordPutData *put, DFNode *node)
{
    printf(CYAN "buildListMapFromHTML\n" RESET);
    if (node->tag == HTML_P) {
        printf(CYAN "Found an HTML paragraph\n" RESET);
        trace_node_info(node, 0);
        //Don't know what this CONV_LISTNUM is
        const char *htmlId = DFGetAttribute(node,CONV_LISTNUM);
        if(htmlId != NULL) {
            printf(CYAN "ID %s %s\n", htmlId, RESET);
            DFNode *conElem = (htmlId != NULL) ? WordConverterGetConcrete(put,node) : NULL;
/*            DFNode *pPrElem = (conElem != NULL) ? DFChildWithTag(conElem,WORD_PPR) : NULL;
            DFNode *numPrElem = (pPrElem != NULL) ? DFChildWithTag(pPrElem,WORD_NUMPR) : NULL;
            DFNode *numIdElem = (numPrElem != NULL) ? DFChildWithTag(numPrElem,WORD_NUMID) : NULL;
            const char *numId = (numIdElem != NULL) ? DFGetAttribute(numIdElem,WORD_VAL) : NULL;

            if (numId != NULL) {
                const char *existingHtmlId = DFHashTableLookup(put->htmlIdByNumId,numId);
                const char *existingNumId = DFHashTableLookup(put->numIdByHtmlId,htmlId);
                if ((existingHtmlId == NULL) && (existingNumId == NULL)) {
                    DFHashTableAdd(put->htmlIdByNumId,numId,htmlId);
                    DFHashTableAdd(put->numIdByHtmlId,htmlId,numId);

                    WordConcreteNum *num = WordNumberingConcreteWithId(put->conv->numbering,numId);
                    if (num != NULL)
                        num->referenceCount++;
                }
            }*/
        }
    }

    for (DFNode *child = node->first; child != NULL; child = child->next)
        buildListMapFromHTML(put,child);
}


int ODFConverterGet(DFDocument *html, DFStorage *abstractStorage, ODFPackage *package, const char *idPrefix, DFError **error)
{
    printf(CYAN "ODFConverterGet\n" RESET);

    if (package->contentDoc == NULL) {
        DFErrorFormat(error,"document.xml not found");
        return 0;
    }
    printf("doc node %s\n", translateXMLEnumName[package->contentDoc->root->tag]);
    if (package->contentDoc->root->tag != OFFICE_DOCUMENT_CONTENT) {
        DFErrorFormat(error,"odf:document content not found");
        return 0;
    }

    DFNode *odfDocument = package->contentDoc->root;

    ODFConverter *converter = ODFConverterNew(html,abstractStorage,package,idPrefix);

    //Get the styles data
    //CSSSheetRelease(converter->styleSheet);
    converter->styleSheet = ODFStylesGet(converter);

    //Try a lenses approach
    ODFGetData get;
    get.conv = converter;
    DFNode *abstract = ODFDocumentLens.get(&get,odfDocument);
    DFAppendChild(converter->html->docNode,abstract);
    converter->html->root = abstract;
    //ODF_postProcessHTMLDoc(converter);

    //Convert the content.xml to an html beastie
    //ODFTextGet(converter);

    char *cssText = CSSSheetCopyCSSText(converter->styleSheet);
    HTMLAddInternalStyleSheet(converter->html, cssText);
    //Safe indent adds a lot of DOM_TEXT nodes around the generated nodes
    //not sure we want this.
//    HTML_safeIndent(converter->html->docNode,0);

    int ok = 1;
    if (converter->warnings->len > 0) {
        DFErrorFormat(error,"%s",converter->warnings->data);
        ok = 0;
    }

    writejson(odfDocument, "getconcrete.json");
    writejson(converter->html->docNode, "getabstract.json");
    ODFConverterFree(converter);
    return ok;
}

DFNode *ODFConverterCreateAbstract(ODFGetData *get, Tag tag, DFNode *concrete)
{
    DFNode *element = DFCreateElement(get->conv->html,tag);

   if (concrete != NULL) {
        char *idStr;
        if (concrete->doc == get->conv->package->contentDoc)
            idStr = DFFormatString("%s%u",get->conv->idPrefix,concrete->seqNo);
        else
            idStr = DFFormatString("%s%u-%s",get->conv->idPrefix,concrete->seqNo,DFNodeName(concrete->doc->root));
        DFSetAttribute(element,HTML_ID,idStr);
        free(idStr);
    }
    return element;
}

DFNode *ODFConverterGetConcrete(ODFPutData *put, DFNode *abstract)
{
    // Is the abstract node an element, and does it have an id that matches the prefix used for
    // conversion? That is, does it look like it has a corresponding node in the concrete document?
    printf(CYAN "ODFConverterGetConcrete\n" RESET);
    //When the abstract is DOM_TEXT it is less than MIN_ELEMENT_TAG
    //and it does not have an ID anyway
    if ((abstract == NULL) || (abstract->tag < MIN_ELEMENT_TAG)) {
        printf(RED "No Abstract\n" RESET);
        return NULL;
    }
    trace_node_info(abstract, 0);
    const char *idStr = DFGetAttribute(abstract,HTML_ID);
    printf(CYAN "HTML id %s %s\n", idStr, RESET);
    if ((idStr == NULL) || !DFStringHasPrefix(idStr,put->conv->idPrefix)) {
        printf(RED "ID was NULL?\n" RESET);
        return NULL;
    }

    // Determine the node sequence number and the document based on the id attribute.
    // The format of the attribute is <prefix><seqno>(-<docname>)?, where
    //
    //     <prefix>  is the BDT prefix we use to identify nodes that match the original document
    //     <seqno>   is an integer uniquely identifying a node in a given document
    //     <docname> is the name of the document, either footnotes or endnotes. If absent, it is
    //               the main content document (that is, document.xml)
    //
    // Note that the sequence number only makes sense within the context of a specific document. It
    // is possible to have two different nodes in different documents that have the same sequence number.
    // It is for this reason that the id string identifies both the node and the document.

    size_t idLen = strlen(idStr);
    size_t prefixLen = strlen(put->conv->idPrefix);

    unsigned int seqNo = 0;
    size_t pos = prefixLen;
    while ((pos < idLen) && (idStr[pos] >= '0') && (idStr[pos] <= '9'))
        seqNo = seqNo*10 + (idStr[pos++] - '0');

    printf(CYAN "build seq no %d %s\n", seqNo, RESET);

    const char *docName = NULL;
    if ((pos < idLen) && (idStr[pos] == '-')) {
        pos++;
        docName = &idStr[pos];
    }

    if(docName != NULL) {
        printf(CYAN "docName %s %s\n", docName, RESET);
    } else {
        printf(CYAN "No docName \n" RESET);
    }

/*    DFDocument *doc = NULL;
    if (docName == NULL)
        doc = put->conv->package->contentDoc;
    else if (!strcmp(docName,"footnotes"))
        doc = put->conv->package->footnotes;
    else if (!strcmp(docName,"endnotes"))
        doc = put->conv->package->endnotes;
    else
        return NULL;*/

    // Check to see if we have a node in the concrete document matching that sequence number
    DFNode *node = DFNodeForSeqNo(put->conv->package->contentDoc,seqNo);

    // Only return the node if it's actually an element
    if ((node == NULL) || (node->tag < MIN_ELEMENT_TAG)) {
        printf(RED "No matching node found \n" RESET);
        return NULL;
    }
    printf(GREEN "FOUND A MATCH IN\n" RESET);
    trace_node_info(node, 0);
    return node;
}

int ODFConverterPut(DFDocument *html, DFStorage *abstractStorage, ODFPackage *package, const char *idPrefix, DFError **error)
{
    printf(CYAN "ODFConverterPut\n" RESET);
    if (package->contentDoc == NULL) {
        DFErrorFormat(error,"document.xml not found");
        return 0;
    }

    if (package->contentDoc->root == NULL) {
        DFErrorFormat(error,"odf:document content not found");
        return 0;
    }

    DFNode *ODFDocument = package->contentDoc->root;
    trace_node_info(ODFDocument, 0);
    printf(CYAN "We have a document\n" RESET);

//    HTML_normalizeDocument(html);
    HTML_pushDownInlineProperties(html->docNode);

    printf(CYAN "Normalised the HTML\n" RESET);
    ODFConverter *converter = ODFConverterNew(html,abstractStorage,package,idPrefix);

    /* not sure what this is all about
     * can it be a new document?
     *
     * ignoring for the moment
     */
    // FIXME: Need a more reliable way of telling whether this is a new document or not - it could be that the
    // document already existed (with styles set up) but did not have any content
    //DFNode *ODFBody = DFChildWithTag(ODFDocument,ODF_BODY);
    //int creating = ((ODFBody == NULL) || (ODFBody->first == NULL));
    int creating = 0;
    //ignoring fields for the moment
    //converter->haveFields = ODF_simplifyFields(converter->package);

    //Don't understand what runs are in a Word document
    //so not applying here until I figure if there is an equivalent
    //ODF_mergeRuns(converter->package);

    //assert(converter->package->styles);

    //restore the style information
    printf(GREEN "Number of style nodes before restore: %lu\n" RESET, (unsigned long)converter->package->stylesDoc->nodesCount);

    CSSSheetRelease(converter->styleSheet);
    converter->styleSheet = CSSSheetNew();

    char *cssText = HTMLCopyCSSText(converter->html);
    CSSSheetUpdateFromCSSText(converter->styleSheet,cssText);
    free(cssText);

    printf(CYAN "Updated CSS Sheet\n" RESET);

    //ODF does have the equivalent of default styles
    //the function below adds in defaults to the document if they are missing in the CSS
    //But if this is a true round trip would they be unless deliberately edit out
    //so skipping for the moment
    /*addMissingDefaultStyles(converter);*/

    CSSEnsureReferencedStylesPresent(converter->html,converter->styleSheet);
    if (creating)
        CSSSetHTMLDefaults(converter->styleSheet);
    CSSEnsureUnique(converter->styleSheet,converter->html,creating);

    CSSStyle *pageStyle = CSSSheetLookupElement(converter->styleSheet,"@page",NULL,0,0);
    CSSStyle *bodyStyle = CSSSheetLookupElement(converter->styleSheet,"body",NULL,1,0);
    CSSProperties *page = (pageStyle != NULL) ? CSSPropertiesRetain(CSSStyleRule(pageStyle)) : CSSPropertiesNew();
    CSSProperties *body = (bodyStyle != NULL) ? CSSPropertiesRetain(CSSStyleRule(bodyStyle)) : CSSPropertiesNew();

    if (CSSGet(body,"margin-left") == NULL)
        CSSPut(body,"margin-left","10%");
    if (CSSGet(body,"margin-right") == NULL)
        CSSPut(body,"margin-right","10%");
    if (CSSGet(body,"margin-top") == NULL)
        CSSPut(body,"margin-top","10%");
    if (CSSGet(body,"margin-bottom") == NULL)
        CSSPut(body,"margin-bottom","10%");

    //ODFSectionUpdateFromCSSPage(converter->mainSection,page,body);

    ODFPutData put;
    put.conv = converter;
    put.contentDoc = converter->package->contentDoc;
    put.numIdByHtmlId = DFHashTableNew((DFCopyFunction)xstrdup,free);
    put.htmlIdByNumId = DFHashTableNew((DFCopyFunction)xstrdup,free);

    // Make sure we update styles.xml from the CSS stylesheet *before* doing any conversion of the content,
    // since the latter requires a full mapping of CSS selectors to styleIds to be in place.
   // ODFUpdateStyles(converter,converter->styleSheet);


    printf(GREEN "Number of style nodes AFTER restore: %lu\n" RESET, (unsigned long)converter->package->stylesDoc->nodesCount);

    /*
     * For Word this looks at the HTML lists and
     * and Tables and figures. Ignoreing for the moment
    ODF_preProcessHTMLDoc(converter,converter->html);
    */

    /* Recursive look for HTML_P nodes - no they're within list
     */
    //buildListMapFromHTML(&put,converter->html->docNode);

    /*updateListTypes(&put);
    ODFBookmarks_removeCaptionBookmarks(converter->package->document);
    ODFObjectsCollapseBookmarks(converter->objects);
    ODFObjectsScan(converter->objects);
    ODF_setupBookmarkLinks(&put);
    ODFObjectsAnalyzeBookmarks(converter->objects,converter->styles); */


    //This looks like the real beast - stuff above is some sort of housekeeping I don't get yet.
    ODFDocumentLens.put(&put,converter->html->root,ODFDocument);

    //Let's see what we made at the end
    writejson(put.contentDoc->root, "putconcrete.json");
    writejson(converter->html->root, "putabstract.json");

    //ODFObjectsExpandBookmarks(converter->objects);
    //ODFRemoveNbsps(converter->package->document);

    // Make sure the updateFields flag is set
    //ODF_updateSettings(converter->package,converter->haveFields);

    // Remove any abstract numbering definitions that are no longer referenced from concrete
    // numbering definitions
    //ODFNumberingRemoveUnusedAbstractNums(converter->numbering);

    // Remove any relationships and images that have been removed from the HTML file and no longer
    // have any other references pointing to them
    //ODFGarbageCollect(converter->package);*/

/*    CSSPropertiesRelease(page);
    CSSPropertiesRelease(body);
    DFHashTableRelease(put.numIdByHtmlId);
    DFHashTableRelease(put.htmlIdByNumId); */

     int ok = 1;
/*    if (converter->warnings->len > 0) {
        DFErrorFormat(error,"%s",converter->warnings->data);
        ok = 0;
    }

    ODFConverterFree(converter);*/
    return ok;
}
