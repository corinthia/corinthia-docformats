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

#ifndef DocFormats_DFError_h
#define DocFormats_DFError_h

#include "DFTypes.h"

typedef struct DFError DFError;

void DFErrorSetPosix(DFError **error, int code);
#ifdef WIN32
void DFErrorSetWin32(DFError **error, DWORD code);
#endif
void DFErrorVFormat(DFError **error, const char *format, va_list ap);
void DFErrorFormat(DFError **error, const char *format, ...) ATTRIBUTE_FORMAT(printf,2,3);
DFError *DFErrorRetain(DFError *error);
void DFErrorRelease(DFError *error);
const char *DFErrorMessage(DFError **error);

#endif
