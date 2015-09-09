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

#ifdef _WINDOWS
#include <direct.h>

#define _CRT_SECURE_NO_WARNINGS
#define snprintf _snprintf
#define strcasecmp _stricmp
#define mktemp _mktemp
#define mkdir  _mkdir
#define bzero(mem,size) memset(mem,0,size)

#ifndef snprintf
#define snprintf _snprintf
#endif // snprintf

#else
#include <unistd.h>
#endif // _WINDOWS

#ifndef ATTRIBUTE_FORMAT
#ifdef _MSC_VER
#define ATTRIBUTE_FORMAT(archetype,index,first)
#define ATTRIBUTE_ALIGNED(n) __declspec(align(8))
#else
#define ATTRIBUTE_FORMAT(archetype,index,first) __attribute__((format(archetype,index,first)))
#define ATTRIBUTE_ALIGNED(n) __attribute__((aligned (n)))
#endif // _MSC_VER
#endif // ATTRIBUTE_FORMAT

typedef struct DFDirEntryList DFDirEntryList;

struct DFDirEntryList {
    char *name;
    DFDirEntryList *next;
};

int DFMkdirIfAbsent(const char *path, char **errmsg);

int DFAddDirContents(const char *absPath, const char *relPath, 
                     int recursive, DFDirEntryList ***list, 
                     char **errmsg);

int DFGetImageDimensions(const void *data, size_t len, 
                         const char *ext, unsigned int *width, 
                         unsigned int *height, char **errmsg);

#define DF_ONCE_INIT 0
typedef int DFOnce;
typedef void (*DFOnceFunction)(void);

void DFInitOnce(DFOnce *once, DFOnceFunction fun);

// Zip functions
typedef struct {
    int   compressedSize;    // File size on disk
    int   uncompressedSize;  // Real file size
    int   compressionMethod; // Type of compression
    long  offset;            // offset in file
    long  crc32;             // copy from local header
    char *fileName;          // filename zero terminated
} DFextZipDirEntry;
typedef DFextZipDirEntry * DFextZipDirEntryP;
typedef struct {
    void             *zipFile;        // file handle to zip file
    int               zipFileCount;   // number of entries in array
    int               zipCreateMode;  // > 0 signals create mode, # is allocation of array
    DFextZipDirEntry *zipFileEntries; // array with filenames in zip
} DFextZipHandle;
typedef DFextZipHandle * DFextZipHandleP;


DFextZipHandleP DFextZipOpen(const char *zipFilename);
DFextZipHandleP DFextZipCreate(const char *zipFilename);

unsigned char     *DFextZipReadFile(DFextZipHandleP zipHandle, DFextZipDirEntryP zipEntry);
DFextZipDirEntryP  DFextZipWriteFile(DFextZipHandleP zipHandle, const char *fileName, const void *buf, const int len);

void DFextZipClose(DFextZipHandleP zipHandle);




void *xmalloc(size_t size);

void *xcalloc(size_t nmemb, size_t size);

void *xrealloc(void *ptr, size_t size);

char *xstrdup(const char *s);
