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
#ifdef DocFormats_platform_h
#error platform.h included multiple times, not allowed
#endif
#define DocFormats_platform_h

// Single linked list, used to set/return multiple files
// Reciever is responsible to free list
// Caller for get operations
// Called for set operations
typedef struct PlatformDirEntry {
    struct PlatformDirEntry *next;
    char                    *name;
    int                      isDirectory;
} PlatformDirEntry;


// Standard ERROR message, given by caller
typedef char ERROR[100];



// Not all OS contain all functions, therefore substitues are put in place
int PlatformReadDir(const char        *path,
                    ERROR              errmsg,
                    PlatformDirEntry **list);
int PlatformMkdirIfAbsent(const char *path,
                          ERROR       errmsg);
int PlatformGetImageDimensions(const char   *path,
                               unsigned int *width,
                               unsigned int *height,
                               ERROR         errmsg);


