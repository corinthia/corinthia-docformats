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

#include "platform.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>



int PlatformGetImageDimensions(const char   *path,
                               unsigned int *width,
                               unsigned int *height,
                               ERROR         errmsg)
{
    printf("WARNING: PlatformGetImageDimensions is not implemented on Linux\n");
    abort();
    return 0;
}



int PlatformMkdirIfAbsent(const char *path,
                          ERROR       errmsg)
{
    if ((mkdir(path,0777) != 0) && (errno != EEXIST)) {
        strcpy(errmsg, strerror(errno));
        return 0;
    }
    return 1;
}



int PlatformReadDir(const char        *path,
                    ERROR              errmsg,
                    PlatformDirEntry **list)
{
    DIR *dir = opendir(path);
    if (dir == NULL) {
        strcpy(errmsg, strerror(errno));
        return 0;
    }

    PlatformDirEntry **outputPtr = list;

    struct dirent buffer;
    struct dirent *result = NULL;
    int ok = 1;
    while (ok && (0 == readdir_r(dir,&buffer,&result)) && (result != NULL)) {
        if (!strcmp(result->d_name,".") || !strcmp(result->d_name,".."))
            continue;

        struct stat statbuf;
        char entryPath[4096];
        snprintf(entryPath,4096,"%s/%s",path,result->d_name);
        if (0 != stat(entryPath,&statbuf))
            continue;

        (*outputPtr) = (PlatformDirEntry *)calloc(1,sizeof(PlatformDirEntry));
        (*outputPtr)->name = strdup(result->d_name);
        (*outputPtr)->isDirectory = S_ISDIR(statbuf.st_mode);
        outputPtr = &(*outputPtr)->next;
    }
    closedir(dir);
    return ok;
}
