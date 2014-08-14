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

#include "OPC.h"
#include "DFDOM.h"
#include "DFFilesystem.h"
#include "DFXML.h"
#include "DFZipFile.h"
#include "DFHashTable.h"
#include "DFString.h"
#include "DFCommon.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                         OPCRelationship                                        //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

static OPCRelationship *OPCRelationshipNew(const char *rId, const char *type, const char *target, int external)
{
    OPCRelationship *rel = (OPCRelationship *)calloc(1,sizeof(OPCRelationship));
    rel->retainCount = 1;
    rel->rId = (rId != NULL) ? strdup(rId) : NULL;
    rel->type = (type != NULL) ? strdup(type) : NULL;
    rel->target = (target != NULL) ? strdup(target) : NULL;
    rel->external = external;
    return rel;
}

static OPCRelationship *OPCRelationshipRetain(OPCRelationship *rel)
{
    if (rel != NULL)
        rel->retainCount++;
    return rel;
}

static void OPCRelationshipRelease(OPCRelationship *rel)
{
    if ((rel == NULL) || (--rel->retainCount > 0))
        return;
    free(rel->rId);
    free(rel->type);
    free(rel->target);
    free(rel);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                       OPCRelationshipSet                                       //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

struct OPCRelationshipSet {
    DFHashTable *relsById;
    DFHashTable *relsByType;
    DFHashTable *relsByDetail;
    int nextId;
};

OPCRelationshipSet *OPCRelationshipSetNew(void)
{
    OPCRelationshipSet *set = (OPCRelationshipSet *)calloc(1,sizeof(OPCRelationshipSet));
    set->relsById = DFHashTableNew((DFCopyFunction)OPCRelationshipRetain,(DFFreeFunction)OPCRelationshipRelease);
    set->relsByType = DFHashTableNew((DFCopyFunction)OPCRelationshipRetain,(DFFreeFunction)OPCRelationshipRelease);
    set->relsByDetail = DFHashTableNew((DFCopyFunction)OPCRelationshipRetain,(DFFreeFunction)OPCRelationshipRelease);
    set->nextId = 1;
    return set;
}

void OPCRelationshipSetFree(OPCRelationshipSet *set)
{
    DFHashTableRelease(set->relsById);
    DFHashTableRelease(set->relsByType);
    DFHashTableRelease(set->relsByDetail);
    free(set);
}

static char *relDetail(int external, const char *type, const char *target)
{
    const char *targetMode = external ? "External" : "Internal";
    return DFFormatString("%s %s %s",targetMode,type,target);
}

const char **OPCRelationshipSetAllIds(OPCRelationshipSet *set)
{
    return DFHashTableCopyKeys(set->relsById);
}

OPCRelationship *OPCRelationshipSetLookupById(OPCRelationshipSet *set, const char *rId)
{
    return (OPCRelationship *)DFHashTableLookup(set->relsById,rId);
}

OPCRelationship *OPCRelationshipSetLookupByType(OPCRelationshipSet *set, const char *type)
{
    return (OPCRelationship *)DFHashTableLookup(set->relsByType,type);
}

OPCRelationship *OPCRelationshipSetAddId(OPCRelationshipSet *set,
                                         const char *rId, const char *type,
                                         const char *target, int external)
{
    char *detail = relDetail(external,type,target);
    OPCRelationship *rel = OPCRelationshipNew(rId,type,target,external);
    DFHashTableAdd(set->relsById,rId,rel);
    DFHashTableAdd(set->relsByType,type,rel);
    DFHashTableAdd(set->relsByDetail,detail,rel);
    OPCRelationshipRelease(rel);
    free(detail);
    return rel;
}

OPCRelationship *OPCRelationshipSetAddType(OPCRelationshipSet *set,
                                           const char *type, const char *target, int external)
{
    char *detail = relDetail(external,type,target);
    OPCRelationship *rel = (OPCRelationship *)DFHashTableLookup(set->relsByDetail,detail);
    if (rel == NULL) {
        char *idStr = NULL;
        while (1) {
            free(idStr);
            idStr = DFFormatString("rId%d",set->nextId);
            if (DFHashTableLookup(set->relsById,idStr) == NULL)
                break;
            set->nextId++;
        }
        rel = OPCRelationshipSetAddId(set,idStr,type,target,external);
        DFHashTableAdd(set->relsByDetail,detail,rel);
        free(idStr);
    }
    free(detail);
    return rel;
}

void OPCRelationshipSetRemove(OPCRelationshipSet *set, OPCRelationship *rel)
{
    char *detail = relDetail(rel->external,rel->type,rel->target);
    DFHashTableRemove(set->relsById,rel->rId);
    if (DFHashTableLookup(set->relsByType,rel->type) == rel)
        DFHashTableRemove(set->relsByType,rel->type);
    if (DFHashTableLookup(set->relsByDetail,detail) == rel)
        DFHashTableRemove(set->relsByDetail,detail);
    free(detail);
}

DFDocument *OPCRelationshipSetToDocument(OPCRelationshipSet *set)
{
    DFDocument *doc = DFDocumentNew();
    DFNode *root = DFCreateElement(doc,REL_RELATIONSHIPS);
    DFAppendChild(doc->docNode,root);
    const char **sortedIds = OPCRelationshipSetAllIds(set);
    DFSortStringsCaseInsensitive(sortedIds);
    for (int i = 0; sortedIds[i]; i++) {
        const char *rId = sortedIds[i];
        OPCRelationship *rel = OPCRelationshipSetLookupById(set,rId);
        DFNode *child = DFCreateElement(doc,REL_RELATIONSHIP);
        DFSetAttribute(child,NULL_Id,rel->rId);
        DFSetAttribute(child,NULL_Type,rel->type);
        DFSetAttribute(child,NULL_TARGET,rel->target);
        if (rel->external)
            DFSetAttribute(child,NULL_TARGETMODE,"External");
        DFAppendChild(root,child);
    }
    free(sortedIds);
    return doc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                             OPCPart                                            //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

OPCPart *OPCPartNew(const char *URI, const char *contentType)
{
    OPCPart *part = (OPCPart *)calloc(1,sizeof(OPCPart));
    part->retainCount = 1;
    part->URI = (URI != NULL) ? strdup(URI) : NULL;
    part->contentType = (contentType != NULL) ? strdup(contentType) : NULL;
    part->relationships = OPCRelationshipSetNew();
    return part;
}

OPCPart *OPCPartRetain(OPCPart *part)
{
    if (part != NULL)
        part->retainCount++;
    return part;
}

void OPCPartRelease(OPCPart *part)
{
    if ((part == NULL) || (--part->retainCount > 0))
        return;
    free(part->URI);
    free(part->contentType);
    OPCRelationshipSetFree(part->relationships);
    free(part);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                         OPCContentTypes                                        //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

struct OPCContentTypes {
    DFHashTable *defaultsByExtension;
    DFHashTable *overridesByPartName;
};

static OPCContentTypes *OPCContentTypesNew(void)
{
    OPCContentTypes *ct = (OPCContentTypes *)calloc(1,sizeof(OPCContentTypes));
    ct->defaultsByExtension = DFHashTableNew((DFCopyFunction)strdup,free);
    ct->overridesByPartName = DFHashTableNew((DFCopyFunction)strdup,free);
    return ct;
}

static void OPCContentTypesFree(OPCContentTypes *ct)
{
    DFHashTableRelease(ct->defaultsByExtension);
    DFHashTableRelease(ct->overridesByPartName);
    free(ct);
}

static const char *OPCContentTypesTypeForPartName(OPCContentTypes *ct, const char *partName)
{
    const char *contentType = DFHashTableLookup(ct->overridesByPartName,partName);
    if (contentType != NULL)
        return contentType;
    char *extension = DFPathExtension(partName);
    if (extension != NULL)
        contentType = DFHashTableLookup(ct->defaultsByExtension,extension);
    free(extension);
    if (contentType != NULL)
        return contentType;
    return "";
}

static int OPCContentTypesLoadFromFile(OPCContentTypes *ct, const char *absPath, DFError **error)
{
    DFDocument *doc = DFParseXMLFile(absPath,error);
    if (doc == NULL) {
        char *filename = DFPathBaseName(absPath);
        DFErrorFormat(error,"%s: %s",filename,DFErrorMessage(error));
        free(filename);
        return 0;
    }
    if (doc->root->tag != CT_TYPES) {
        char *filename = DFPathBaseName(absPath);
        DFErrorFormat(error,"%s: Invalid root element",filename);
        free(filename);
        DFDocumentRelease(doc);
        return 0;
    }
    for (DFNode *child = doc->root->first; child != NULL; child = child->next) {
        switch (child->tag) {
            case CT_DEFAULT: {
                const char *extension = DFGetAttribute(child,NULL_EXTENSION);
                const char *contentType = DFGetAttribute(child,NULL_CONTENTTYPE);
                if ((extension != NULL) && (contentType != NULL))
                    DFHashTableAdd(ct->defaultsByExtension,extension,contentType);
                break;
            }
            case CT_OVERRIDE: {
                const char *partName = DFGetAttribute(child,NULL_PARTNAME);
                const char *contentType = DFGetAttribute(child,NULL_CONTENTTYPE);
                if ((partName != NULL) && (contentType != NULL))
                    DFHashTableAdd(ct->overridesByPartName,partName,contentType);
                break;
            }
        }
    }
    DFDocumentRelease(doc);
    return 1;
}

static int OPCContentTypesSaveToFile(OPCContentTypes *ct, const char *absPath, DFError **error)
{
    DFDocument *doc = DFDocumentNew();
    DFNode *types = DFCreateElement(doc,CT_TYPES);
    DFAppendChild(doc->docNode,types);
    const char **keys = DFHashTableCopyKeys(ct->defaultsByExtension);
    for (int i = 0; keys[i]; i++) {
        const char *extension = keys[i];
        const char *contentType = DFHashTableLookup(ct->defaultsByExtension,extension);
        DFNode *deflt = DFCreateElement(doc,CT_DEFAULT);
        DFSetAttribute(deflt,NULL_EXTENSION,extension);
        DFSetAttribute(deflt,NULL_CONTENTTYPE,contentType);
        DFAppendChild(types,deflt);
    }
    free(keys);
    keys = DFHashTableCopyKeys(ct->overridesByPartName);
    for (int i = 0; keys[i]; i++) {
        const char *partName = keys[i];
        const char *contentType = DFHashTableLookup(ct->overridesByPartName,partName);
        DFNode *override = DFCreateElement(doc,CT_OVERRIDE);
        DFSetAttribute(override,NULL_PARTNAME,partName);
        DFSetAttribute(override,NULL_CONTENTTYPE,contentType);
        DFAppendChild(types,override);
    }
    free(keys);
    if (!DFSerializeXMLFile(doc,NAMESPACE_CT,0,absPath,error)) {
        char *filename = DFPathBaseName(absPath);
        DFErrorFormat(error,"%s: %s",filename,DFErrorMessage(error));
        free(filename);
        DFDocumentRelease(doc);
        return 0;
    }
    DFDocumentRelease(doc);
    return 1;
}

void OPCContentTypesSetDefault(OPCContentTypes *ct, const char *extension, const char *type)
{
    DFHashTableAdd(ct->defaultsByExtension,extension,type);
}

void OPCContentTypesSetOverride(OPCContentTypes *ct, const char *partName, const char *type)
{
    DFHashTableAdd(ct->overridesByPartName,partName,type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                           OPCPackage                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

OPCPackage *OPCPackageNew(const char *tempPath)
{
    OPCPackage *pkg = (OPCPackage *)calloc(1,sizeof(OPCPackage));
    pkg->tempPath = strdup(tempPath);
    pkg->contentTypes = OPCContentTypesNew();
    pkg->relationships = OPCRelationshipSetNew();
    pkg->partsByName = DFHashTableNew((DFCopyFunction)OPCPartRetain,(DFFreeFunction)OPCPartRelease);
    pkg->errors = DFBufferNew();
    return pkg;
}

void OPCPackageFree(OPCPackage *pkg)
{
    free(pkg->tempPath);
    OPCContentTypesFree(pkg->contentTypes);
    OPCRelationshipSetFree(pkg->relationships);
    DFHashTableRelease(pkg->partsByName);
    DFBufferRelease(pkg->errors);
    free(pkg);
}

static void OPCPackageError(OPCPackage *pkg, const char *format, ...)
{
    va_list ap;
    va_start(ap,format);
    DFBufferVFormat(pkg->errors,format,ap);
    va_end(ap);
    DFBufferFormat(pkg->errors,"\n");
}

static char *relRelationshipsPathForURI(const char *URI)
{
    // FIXME: Invalid partFilename or partDirectory not covered by tests
    char *partFilename = DFPathBaseName(URI);
    char *partDirectory = DFPathDirName(URI);
    char *relFilename;
    if (DFStringEquals(partFilename,"/"))
        relFilename = DFFormatString("%s_rels/.rels",partDirectory);
    else
        relFilename = DFFormatString("%s/_rels/%s.rels",partDirectory,partFilename);
    free(partFilename);
    free(partDirectory);
    return relFilename;
}

static void saveRelationships(OPCPackage *pkg, OPCRelationshipSet *rels, const char *URI)
{
    char *relativePath = relRelationshipsPathForURI(URI);
    char *absolutePath = DFAppendPathComponent(pkg->tempPath,relativePath);

    const char **allIds = OPCRelationshipSetAllIds(rels);
    int idCount = 0;
    while (allIds[idCount])
        idCount++;
    free(allIds);

    if (idCount == 0) {
        DFError *error = NULL;
        if (DFFileExists(absolutePath) && !DFDeleteFile(absolutePath,&error)) {
            OPCPackageError(pkg,"%s: %s",relativePath,DFErrorMessage(&error));
            DFErrorRelease(error);
        }
    }
    else {
        char *absoluteParent = DFPathDirName(absolutePath);
        DFError *error = NULL;
        if (!DFFileExists(absoluteParent) &&
            !DFCreateDirectory(absoluteParent,1,&error)) {
            OPCPackageError(pkg,"%s: %s",absoluteParent,DFErrorMessage(&error));
            DFErrorRelease(error);
        }
        else {

            DFDocument *doc = OPCRelationshipSetToDocument(rels);
            if (!DFSerializeXMLFile(doc,NAMESPACE_REL,0,absolutePath,&error)) {
                OPCPackageError(pkg,"%s: %s",relativePath,DFErrorMessage(&error));
                DFErrorRelease(error);
            }
            DFDocumentRelease(doc);
        }
        free(absoluteParent);
    }

    free(relativePath);
    free(absolutePath);
}

static void readRelationships(OPCPackage *pkg, OPCRelationshipSet *rels, const char *partURI)
{
    char *relFilename = relRelationshipsPathForURI(partURI);
    char *absPath = DFAppendPathComponent(pkg->tempPath,relFilename);
    if (DFFileExists(absPath)) {
        DFError *localError = NULL;
        DFDocument *relDoc = DFParseXMLFile(absPath,&localError);
        if (relDoc == NULL) {
            OPCPackageError(pkg,"%s: %s",relFilename,DFErrorMessage(&localError));
            DFErrorRelease(localError);
        }
        else {
            OPCPackageReadRelationships(pkg,rels,partURI,relDoc);
            DFDocumentRelease(relDoc);
        }
    }
    free(relFilename);
    free(absPath);
}

void OPCPackageReadRelationships(OPCPackage *pkg, OPCRelationshipSet *rels, const char *partURI, DFDocument *relDoc)
{
    // FIXME: Not covered by tests
    char *relFilename = relRelationshipsPathForURI(partURI);
    if (relDoc->root->tag != REL_RELATIONSHIPS) {
        OPCPackageError(pkg,"%s: Invalid root element",relFilename);
        free(relFilename);
        return;
    }
    for (DFNode *child = relDoc->root->first; child != NULL; child = child->next) {
        if (child->tag == REL_RELATIONSHIP) {
            const char *rId = DFGetAttribute(child,NULL_Id);
            const char *type = DFGetAttribute(child,NULL_Type);
            const char *relTarget = DFGetAttribute(child,NULL_TARGET);
            const char *targetMode = DFGetAttribute(child,NULL_TARGETMODE);

            if (rId == NULL) {
                OPCPackageError(pkg,"%s: Relationship is missing id attribute",relFilename);
                continue;
            }
            if (type == NULL) {
                OPCPackageError(pkg,"%s: Relationship %s is missing type attribute",relFilename,rId);
                continue;
            }
            if (relTarget == NULL) {
                OPCPackageError(pkg,"%s: Relationship %s is missing target attribute",relFilename,rId);
                continue;
            }
            if ((targetMode != NULL) && strcmp(targetMode,"External") && strcmp(targetMode,"Internal")) {
                char *quotedTargetMode = DFQuote(targetMode);
                OPCPackageError(pkg,"%s: Relationship %s has invalid target mode %s",
                                relFilename,rId,quotedTargetMode);
                free(quotedTargetMode);
            }

            int external = ((targetMode != NULL) && !strcmp(targetMode,"External"));

            if (external) {
                OPCRelationshipSetAddId(rels,rId,type,relTarget,external);
            }
            else {
                char *absTarget = DFPathResolveAbsolute(partURI,relTarget);
                OPCRelationshipSetAddId(rels,rId,type,absTarget,external);
                free(absTarget);
            }
        }
    }
    free(relFilename);
}

static void findParts(OPCPackage *pkg, const char *relPath)
{
    // FIXME: Not covered by tests
    char *absPath = DFAppendPathComponent(pkg->tempPath,relPath);

    DFError *error = NULL;
    const char **contents = DFContentsOfDirectory(absPath,0,&error);

    if (contents == NULL) {
        OPCPackageError(pkg,"%s %s",relPath,DFErrorMessage(&error));
        DFErrorRelease(error);
        free(absPath);
        return;
    }

    for (int i = 0; contents[i]; i++) {
        const char *entry = contents[i];
        char *entryAbsPath = DFAppendPathComponent(absPath,entry);
        char *entryRelPath = DFAppendPathComponent(relPath,entry);
        if (!DFFileExists(entryAbsPath)) {
            OPCPackageError(pkg,"%s: No such file or directory",entryRelPath);
        }
        else if (DFIsDirectory(entryAbsPath)) {
            if (!DFStringEqualsCI(entry,"_rels")) {
                findParts(pkg,entryRelPath);
            }
        }
        else if (!DFStringEqualsCI(entry,"[Content_Types].xml")) {
            OPCPackagePartWithURI(pkg,entryRelPath);
        }
        free(entryAbsPath);
        free(entryRelPath);
    }

    free(absPath);
    free(contents);
}

int OPCPackageOpenNew(OPCPackage *pkg, DFError **error)
{
    return 1;
}

int OPCPackageOpenFrom(OPCPackage *pkg, const char *filename)
{
    DFError *dferror = NULL;
    if (!DFUnzip(filename,pkg->tempPath,&dferror)) {
        OPCPackageError(pkg,"%s",DFErrorMessage(&dferror));
        DFErrorRelease(dferror);
        return 0;
    }

    char *contentTypesPath = DFAppendPathComponent(pkg->tempPath,"[Content_Types].xml");
    int ok = OPCContentTypesLoadFromFile(pkg->contentTypes,contentTypesPath,&dferror);
    free(contentTypesPath);
    if (!ok) {
        OPCPackageError(pkg,"%s",DFErrorMessage(&dferror));
        DFErrorRelease(dferror);
        return 0;
    }
    findParts(pkg,"/");

    const char **keys = DFHashTableCopyKeys(pkg->partsByName);
    for (int i = 0; keys[i]; i++) {
        OPCPart *part = DFHashTableLookup(pkg->partsByName,keys[i]);
        readRelationships(pkg,part->relationships,part->URI);
    }
    free(keys);

    readRelationships(pkg,pkg->relationships,"/");

    return (pkg->errors->len == 0);
}

int OPCPackageSaveTo(OPCPackage *pkg, const char *filename)
{
    // Save content types
    DFError *dferror = NULL;
    char *contentTypesPath = DFAppendPathComponent(pkg->tempPath,"[Content_Types].xml");
    int ok = OPCContentTypesSaveToFile(pkg->contentTypes,contentTypesPath,&dferror);
    free(contentTypesPath);
    if (!ok) {
        OPCPackageError(pkg,"%s",DFErrorMessage(&dferror));
        DFErrorRelease(dferror);
        return 0;
    }

    // Save relationships
    const char **keys = DFHashTableCopyKeys(pkg->partsByName);
    for (int i = 0; keys[i]; i++) {
        OPCPart *part = DFHashTableLookup(pkg->partsByName,keys[i]);
        saveRelationships(pkg,part->relationships,part->URI);
    }
    free(keys);
    saveRelationships(pkg,pkg->relationships,"/");

    // Build zip file
    if (!DFZip(filename,pkg->tempPath,&dferror)) {
        OPCPackageError(pkg,"%s",DFErrorMessage(&dferror));
        DFErrorRelease(dferror);
        return 0;
    }

    return (pkg->errors->len == 0);
}

OPCPart *OPCPackagePartWithURI(OPCPackage *pkg, const char *URI)
{
    OPCPart *part = DFHashTableLookup(pkg->partsByName,URI);
    if (part == NULL) {
        const char *contentType = OPCContentTypesTypeForPartName(pkg->contentTypes,URI);
        part = OPCPartNew(URI,contentType);
        DFHashTableAdd(pkg->partsByName,URI,part);
        OPCPartRelease(part);
    }
    return part;
}

OPCPart *OPCPackageAddRelatedPart(OPCPackage *pkg, const char *URI, const char *contentType,
                                  const char *relType, OPCPart *source)
{
    OPCContentTypesSetOverride(pkg->contentTypes,URI,contentType);
    OPCRelationshipSetAddType(source->relationships,relType,URI,0);
    return OPCPackagePartWithURI(pkg,URI);
}

DFBuffer *OPCPackageReadPart(OPCPackage *pkg, OPCPart *part, DFError **error)
{
    char *absolutePath = DFAppendPathComponent(pkg->tempPath,part->URI);
    DFBuffer *buffer = DFBufferReadFromFile(absolutePath,error);
    free(absolutePath);
    if (buffer == NULL) {
        DFErrorFormat(error,"%s: %s",part->URI,DFErrorMessage(error));
        return NULL;
    }

    return buffer;
}

int OPCPackageWritePart(OPCPackage *pkg, const char *data, size_t len, OPCPart *part, DFError **error)
{
    char *absolutePath = DFAppendPathComponent(pkg->tempPath,part->URI);
    char *absoluteParent = DFPathDirName(absolutePath);
    int result = 0;

    if (!DFFileExists(absoluteParent) &&
        !DFCreateDirectory(absoluteParent,1,error)) {
        DFErrorFormat(error,"%s: %s",absoluteParent,DFErrorMessage(error));
    }
    else {
        DFBuffer *buffer = DFBufferNew();
        DFBufferAppendData(buffer,data,len);
        if (!DFBufferWriteToFile(buffer,absolutePath,error)) {
            DFErrorFormat(error,"%s: %s",part->URI,DFErrorMessage(error));
        }
        else {
            result = 1;
        }
        DFBufferRelease(buffer);
    }
    free(absolutePath);
    free(absoluteParent);
    return result;
}
