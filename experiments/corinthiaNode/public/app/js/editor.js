/*
 * Copyright 2015 Ian Cunningham
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.Copyright [yyyy] [name of copyright owner]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// the common js needed to load the editor code.
"use strict";

var api;
var autosave = true;

function start(theAPI) {
    autosave = true;
    api = theAPI;
    console.log("test start");
    api.main.init(768, 100, null);
    var iframe = document.getElementById("editFrame");
    removeScripts(iframe.contentDocument.body);
    autoEdit(api);
    //can we switch on a testcase variable
    if(autosave) {
        angular.element(document.getElementById('TestDiv')).scope().autoSaveDoc();
        console.log("test auto saved");
    }
}

function contentLoaded() {
    console.log("Content loaded");

    var iframe = document.getElementById("editFrame");
    if (iframe.contentDocument.URL !== "about:blank") {
        var requireScript = iframe.contentDocument.createElement("script");
        requireScript.src = "require.js";
        requireScript.setAttribute("src", "../../js/require.js");
        requireScript.setAttribute("data-main", "../../js/iframe-code");
        requireScript.addEventListener("load", function() {
            console.log("require.js loaded in content iframe");
            iframe.contentWindow.require(["editor/build/src/externalapi"], function(api) {
                console.log("** here");
                start(api);
            });
        });
        iframe.contentDocument.body.appendChild(requireScript);
    }
}

function removeScripts(from) {
    var scripts = from.getElementsByTagName("script");
    while (scripts.length > 0) {
        from.removeChild(scripts[0]);
    }
}

function cleanup() {
    console.log("remove scripts");
    var iframe = document.getElementById("editFrame");
    if (iframe.contentDocument.URL !== "about:blank") {
        //only one of these but ...
        removeScripts(iframe.contentDocument.body);
        removeScripts(iframe.contentDocument.head);
        //We added viewport metadata
        var metas = iframe.contentDocument.head.getElementsByTagName("meta");
        var ndx = 0;
        while (ndx < metas.length) {
            if (metas[ndx].hasAttribute("name")) {
                if (metas[ndx].getAttribute("name").toLowerCase() == "viewport") {
                    iframe.contentDocument.head.removeChild(metas[ndx]);
                    //don't increment the ndx if removed because length changes
                } else {
                    ndx++;
                }
            } else {
                ndx++;
            }
        }
        return true;
    }
    return false;
}
