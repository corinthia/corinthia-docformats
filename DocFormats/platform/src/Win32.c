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

#include <platform.h>
#include <windows.h>


static void PlatformWin32ErrorString(DWORD code, DF_ERR_TXT errmsg)
{
    char *lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        code,
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,NULL);
    size_t len = strlen(lpMsgBuf);
    while ((len > 0) &&
        ((lpMsgBuf[len - 1] == '\n') ||
        (lpMsgBuf[len - 1] == '\r') ||
        (lpMsgBuf[len - 1] == '.')))
        len--;
    lpMsgBuf[len] = '\0';
    // Does LocalFree work with the same heap as malloc/free? If so, we could avoid making the
    // separate copy here.
	strcpy_s(errmsg, sizeof(errmsg), lpMsgBuf);
    LocalFree(lpMsgBuf);
}



int PlatformMkdirIfAbsent(const char *path,
	                      DF_ERR_TXT  errmsg)
{
    if (!CreateDirectory(path,NULL) && (GetLastError() != ERROR_ALREADY_EXISTS)) {
        PlatformWin32ErrorString(GetLastError(), errmsg);
        return 0;
    }
    return 1;
}



int PlatformReadDir(const char        *path,
                    DF_ERR_TXT         errmsg,
                    PlatformDirEntry **list)
{
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char pattern[4096];
	_snprintf_s(pattern, sizeof(pattern), sizeof(pattern), "%s/*", path);
    hFind = FindFirstFile(pattern,&ffd);
    if (hFind == INVALID_HANDLE_VALUE) {
        PlatformWin32ErrorString(GetLastError(), errmsg);
        return 0;
    }

    PlatformDirEntry **outputPtr = list;

    int ok = 1;
    do {
        if (!strcmp(ffd.cFileName,".") || !strcmp(ffd.cFileName,".."))
            continue;

        (*outputPtr) = (PlatformDirEntry *)calloc(1,sizeof(PlatformDirEntry));
        (*outputPtr)->name = _strdup(ffd.cFileName);
        (*outputPtr)->isDirectory = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
        outputPtr = &(*outputPtr)->next;
    } while (ok && (FindNextFile(hFind,&ffd) != 0));

    FindClose(hFind);
    return ok;
}



int PlatformGetImageDimensions(const char   *path,
                               unsigned int *width,
                               unsigned int *height,
                               DF_ERR_TXT    errmsg)
{
    printf("WARNING: DFGetImageDimensions is not implemented on Windows\n");
    abort();
    return 0;
}


