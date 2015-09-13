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

#include "color.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *show_color(char *color, const char* str)
{
    char *r;
    if (COLOR_ON) {
        size_t len = strlen (str) + 2 * COLOR_SIZEOF + 1;
        r = malloc(len);
        snprintf (r, len, "%s%s%s", color, str, RESET);
    }
    else {
        size_t len = strlen (str) + 1;
        r = malloc(len);
        snprintf (r, len, "%s",  str);
    }

    return r;
}

char *red(const char *str) { return show_color(RED, str); }
char *blue(const char *str) { return show_color(BLUE, str); }
char *green(const char *str) { return show_color(GREEN, str); }
char *yellow(const char *str) { return show_color(YELLOW, str); }
char *cyan(const char *str) { return show_color(CYAN, str); }
char *magenta(const char *str) { return show_color(MAGENTA, str); }



