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

#ifndef DocFormats_ODFText_h
#define DocFormats_ODFText_h

#include <DocFormats/DFError.h>
#include <DocFormats/DFStorage.h>
#include <DocFormats/DFXMLForward.h>

DFDocument *ODFTextGet(DFStorage *concreteStorage, DFStorage *abstractStorage, DFError **error);
int ODFTextPut(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, DFError **error);
int ODFTextCreate(DFStorage *concreteStorage, DFStorage *abstractStorage, DFDocument *htmlDoc, DFError **error);

#endif
