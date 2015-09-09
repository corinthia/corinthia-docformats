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

#pragma once
#include "qt_classes.hpp"


void Editor::webViewloadFinished(bool ok) {}

Editor::Editor(QWidget *parent, Qt::WindowFlags f) {}
Editor::~Editor() {}


void Editor::mouseDoubleClickEvent(QMouseEvent *event) {}
void Editor::mouseMoveEvent(QMouseEvent *event) {}
void Editor::mousePressEvent(QMouseEvent *event) {}
void Editor::mouseReleaseEvent(QMouseEvent *event) {}
void Editor::resizeEvent(QResizeEvent *event) {}
bool Editor::eventFilter(QObject *obj, QEvent *event) { return true; }
