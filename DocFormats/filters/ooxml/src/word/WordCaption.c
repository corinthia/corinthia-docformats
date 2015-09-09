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

#include "WordCaption.h"
#include "DFPlatform.h"
#include "DFCommon.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                           WordCaption                                          //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

WordCaption *WordCaptionNew(DFNode *element)
{
    WordCaption *caption = (WordCaption *)xcalloc(1,sizeof(WordCaption));
    caption->retainCount = 1;
    caption->element = element;
    return caption;
}

WordCaption *WordCaptionRetain(WordCaption *caption)
{
    if (caption != NULL)
        caption->retainCount++;
    return caption;
}

void WordCaptionRelease(WordCaption *caption)
{
    if ((caption == NULL) || (--caption->retainCount > 0))
        return;
    free(caption);
}
