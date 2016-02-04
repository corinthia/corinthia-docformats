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
#include "ODFText.h"
#include "ODFPackage.h"
#include "ODFTextConverter.h"
#include "DFDOM.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DFXMLNames.h"
#include "DFNameMap.h"
#include "productionCoverage.h"


static FILE* jsonFile = NULL;

static void escapeJson(char * strin, char * strout)
{
    char *ptr = strin;
    int j = 0;
    for(int i=0; i<strlen(strin); i++){
        switch(*ptr) {
            case '\n':
                strout[j++] = '\\';
                strout[j] = 'n';
                break;
            case '\r':
                strout[j++] = '\\';
                strout[j] = 'r';
                break;
            case 34: //a "
                strout[j++] = '\\';
                strout[j] = 0x22;
                break;
            case '\t':
                strout[j++] = '\\';
                strout[j] = 't';
                break;
            case '\\':
                strout[j++] = '\\';
                strout[j] = '\\';
                break;
            default:
                strout[j] = *ptr;
                break;
        }
        ptr++;
        j++;
    }
    strout[j] = 0;
}


static void jsonNodeOpen(DFNode *n, int level)
{
    //bit like a trace but with names and curly braces
    //will need to escape some characters?
    if (n == NULL) return;
//    char spaces[] = "                                      ";
//    spaces[level*4] = 0;
    if (n->tag) {
        fprintf(jsonFile, "{\"type\": \"%s\",\n", translateXMLEnumName[n->tag]);
        fprintf(jsonFile, " \"seq\": %d,\n ", n->seqNo);
    }
    if(n->attrsCount > 0) {
        fprintf(jsonFile, "\"attributes\": [\n");
        for (int i = 0; i < n->attrsCount; i++) {
            if(i>0)  fputs(",", jsonFile);
            char escStr[strlen(n->attrs[i].value)*2]; //just hard code for the moment
            escapeJson(n->attrs[i].value, escStr);

            fprintf(jsonFile, "{  \"%s\": \"%s\"}", translateXMLEnumName[n->attrs[i].tag], escStr);
        }
        fprintf(jsonFile, "\n ],\n");
    }
    if (n->value) {
        //how big - not all characters will need escaping
        char escStr[strlen(n->value)*2]; //just hard code for the moment
//        puts(n->value);
        escapeJson(n->value, escStr);
//        puts(n->value);
        fprintf(jsonFile, " \"value\": \"%s\",\n", escStr);
    }
}

static void jsonNodeClose(DFNode *n, int level, int last)
{
    //bit like a trace but with names and curly braces
    //will need to escape some characters?
//    char spaces[] = "                                      ";
//    spaces[level*4] = 0;
    if(last) {
        fprintf(jsonFile, "}\n");
    } else {
        fprintf(jsonFile, "},           \n");
    }
}

void writejson(DFNode *odfNode, const char* name)
{
    jsonFile = fopen(name, "w");
    if(jsonFile != NULL) {
        nodes2json(odfNode, 0);
    }
    fclose(jsonFile);
}

void nodes2json(DFNode *odfNode, int level)
{
    jsonNodeOpen(odfNode, level);
    level++;
    int i = 0;
    fprintf(jsonFile, "\"children\": [\n");
    for (DFNode *odfChild = odfNode->first; odfChild != NULL; odfChild = odfChild->next) {
        //if(i>0)  fputs(",", jsonFile);
        nodes2json(odfChild, level);
        i++;
    }
    fprintf(jsonFile, "]\n");
    level--;
    int last = 1;
    //want to know whether to add the comma
    if(odfNode->next != NULL) {
        last = 0;
    }
    jsonNodeClose(odfNode, level, last);
}

