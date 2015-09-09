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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "DFPlatform.h"



void *xmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL) {
        perror("xmalloc: out of memory.\n");
        abort();
        return NULL;
    }

    return ptr;
}



void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);

    if (ptr == NULL) {
        perror("xcalloc: out of memory.\n");
        abort();
        return NULL;
    }

    return ptr;
}



void *xrealloc(void *in_ptr, size_t size)
{
    void *ptr = realloc(in_ptr, size);

    if (ptr == NULL) {
        perror("xrealloc: out of memory.\n");
        abort();
        return NULL;
    }

    return ptr;
}


char *xstrdup(const char *s)
{
    size_t l = strlen(s)+1;
    return (char*) memcpy (xmalloc (l), s, l);
}
