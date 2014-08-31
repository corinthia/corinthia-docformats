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
#ifndef DEF_3RDPARTY_H
#define DEF_3RDPARTY_H

#include "../external/w3c-tidy-html5/include/tidy.h"
#include "../external/w3c-tidy-html5/include/buffio.h"
#define UTF8        4

#include <zlib.h>

typedef void * voidp;
typedef unsigned int uInt;
typedef unsigned long uLong;

typedef voidp zipFile;
typedef voidp unzFile;

extern unzFile unzOpen (const char *path);
extern int unzGoToFirstFile (unzFile file);
extern int unzGoToNextFile (unzFile file);

#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define ZIP_OK                          (0)
#define APPEND_STATUS_CREATE        (0)




typedef struct
{
    uInt tm_sec;            /* seconds after the minute - [0,59] */
    uInt tm_min;            /* minutes after the hour - [0,59] */
    uInt tm_hour;           /* hours since midnight - [0,23] */
    uInt tm_mday;           /* day of the month - [1,31] */
    uInt tm_mon;            /* months since January - [0,11] */
    uInt tm_year;           /* years - [1980..2044] */
} tm_zip;




typedef struct unz_file_info_s
{
    uLong version;              /* version made by                 2 bytes */
    uLong version_needed;       /* version needed to extract       2 bytes */
    uLong flag;                 /* general purpose bit flag        2 bytes */
    uLong compression_method;   /* compression method              2 bytes */
    uLong dosDate;              /* last mod file date in Dos fmt   4 bytes */
    uLong crc;                  /* crc-32                          4 bytes */
    uLong compressed_size;      /* compressed size                 4 bytes */
    uLong uncompressed_size;    /* uncompressed size               4 bytes */
    uLong size_filename;        /* filename length                 2 bytes */
    uLong size_file_extra;      /* extra field length              2 bytes */
    uLong size_file_comment;    /* file comment length             2 bytes */

    uLong disk_num_start;       /* disk number start               2 bytes */
    uLong internal_fa;          /* internal file attributes        2 bytes */
    uLong external_fa;          /* external file attributes        4 bytes */

    tm_zip tmu_date;
} unz_file_info;
typedef struct
{
    tm_zip      tmz_date;       /* date in understandable format           */
    uLong       dosDate;       /* if dos_date == 0, tmu_date is used      */
/*    uLong       flag;        */   /* general purpose bit flag        2 bytes */

    uLong       internal_fa;    /* internal file attributes        2 bytes */
    uLong       external_fa;    /* external file attributes        4 bytes */
} zip_fileinfo;

extern int unzGetCurrentFileInfo (unzFile file,
                         unz_file_info *pfile_info,
                         char *szFileName,
                         uLong fileNameBufferSize,
                         void *extraField,
                         uLong extraFieldBufferSize,
                         char *szComment,
                         uLong commentBufferSize);
extern int unzOpenCurrentFile (unzFile file);
extern int unzReadCurrentFile (unzFile file,
                      voidp buf,
                      unsigned len);
extern int unzCloseCurrentFile (unzFile file);
extern int unzClose (unzFile file);
extern int zipOpenNewFileInZip (zipFile file,
                       const char* filename,
                       const zip_fileinfo* zipfi,
                       const void* extrafield_local,
                       uInt size_extrafield_local,
                       const void* extrafield_global,
                       uInt size_extrafield_global,
                       const char* comment,
                       int method,
                       int level);
extern int zipWriteInFileInZip (zipFile file,
                       const void* buf,
                       unsigned len);
extern int zipCloseFileInZip (zipFile file);
extern zipFile zipOpen (const char *pathname, int append);
extern int zipClose (zipFile file, const char* global_comment);






#endif
