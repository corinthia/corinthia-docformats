/*
Copyright 2015 Ian Cunningham

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.Copyright [yyyy] [name of copyright owner]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

var inspect = require('util').inspect;
var extend = require('util')._extend;

var path = require('path');
var logger = require('morgan');
var moment = require('moment');

var os = require('os');
var fse = require('fs-extra');
var Q = require('q');
var spawn = require('child_process').spawn;

var ROOT_DIR = 'public';

var TEST_DIR = 'public/app/tests/';
var OUTPUT_DIR = 'app/output/';
var DATA_DIR = 'app/data/';
var SEED_DIR = 'public/seedDocs/';

var currentDoc = "";
var inputFile = '';
var dataDirectory = '';
var targetHTML = '';

//the get abstract has a parent element we want to ignore
exports.merge = function(first, second, getFromFirstChild) {
    //    console.log("merge/diff  " + first + " and " + second);
    var beforeObj = JSON.parse(fse.readFileSync(first, 'utf8'));
    var afterObj = JSON.parse(fse.readFileSync(second, 'utf8'));
    initNodes(beforeObj);
    if (getFromFirstChild) {
        mergeDoc(beforeObj.children[0], afterObj, 0);

    } else {
        mergeDoc(beforeObj, afterObj, 0);
    }
    return beforeObj;
};

function initNodes(root) {
    for (var n = 0; n < root.children.length; n++) {
        addState(root.children[n], "ORIG");
        initNodes(root.children[n]);
    }
}

// for each node in root2 find its match in root1
// check to see if it has changed -> INST or DIFF
// or it is NEW
// add index numbers to track repositioning?
function mergeDoc(root1, root2, level) {
    //        console.log("merge1 " + inspect(root1));
    //        console.log("merge2 " + inspect(root2));
    var r1 = 0;
    for (var r2 = 0; r2 < root2.children.length; r2++) {
        var root2Node = root2.children[r2];
        if (root1.children && r1 < root1.children.length) {
            var root1Node = root1.children[r1];
            if (isMatch(root1Node, root2Node)) {
                mergeNode(root1Node, root2Node);
                mergeDoc(root1Node, root2Node, level);
            } else {
                addNew(root1, r1, root2Node);
            }
            r1++;
        } else {
            // all of root2 is NEW
            addNew(root1, r1, root2Node);
        }
    }
    //if we get here with no iterations then root1 and its children will
    //be left as ORIG
}

function addNew(root1, ndx, root2Node) {
    //    console.log("NEW: " + inspect(root2Node));
    newNode = extend({}, root2Node);
    newNode.state = "NEW";
    propagateState(newNode, "NEW");
    root1.children.splice(ndx, 0, newNode);
}

function addState(node, val) {
    node.state = val;
}

// is node in root?
// Compare
// or add new
// need to consider the attributes too
function mergeNode(match, root2Node) {
    if (match.value === root2Node.value && attributesMatch(match, root2Node)) {
        match.state = "INST";
    } else {
        //        console.log("DIFF Compare Merge ");
        match.state = "DIFF";
        match.diff = root2Node.value;
    }
}

function attributesMatch(match, root2Node) {
    var retval = true;
    if (match.attributes && root2Node.attributes) {
        var matchAttrs = match.attributes.length;
        var root2Attrs = root2Node.attributes.length;
        if (matchAttrs === root2Attrs) {
            //they may not be in the same order
            for (var a = 0; a < matchAttrs; a++) {
                if (inspect(match.attributes[a]) !== inspect(root2Node.attributes[a])) {
                    console.log("Mismatch attr value " + inspect(match.attributes[a]) + " " + inspect(root2Node.attributes[a]));
                    if (match.attrdiff) {
                        match.attrdiff += inspect(root2Node.attributes[a]) + " ";
                    } else {
                        match.attrdiff = inspect(root2Node.attributes[a]) + " ";
                    }
                    retval = false;
                }
            }
        } else {
            match.attrdiff = "Number " + matchAttrs + " -> " + root2Attrs;
            console.log("Mismatch attrs length " + matchAttrs + " " + root2Attrs);
            retval = false;
        }
    }
    return retval;
}

function isMatch(root, node) {
    //    console.log("Compare Match " + root.type + " " + node.type);
    if (root.type === node.type) {
        //console.log("MATCH");
        return true;
    }
    //console.log("NO MATCH");
    return false;
}

function propagateState(root, state) {
    for (var n = 0; n < root.children.length; n++) {
        addState(root.children[n], "NEW");
        propagateState(root.children[n], "NEW");
    }
}

// This could be done as we walk the tree above?
// But probably best done as a pass through the merged tree
// Where do we report too?
exports.reportChanges = function(mergedTree) {
    //walk the tree and look for Nodes with
    // NEW means elements added to the document
    // DIFF means elements with value that has changed
    // ORIG means must have been deleted in the edited document
    var diffString = "fred";
    diffString = reportTree(mergedTree, diffString);
    return diffString;
};

function reportTree(root) {
    var diffString = "";
    if (root.children) {
        for (var n = 0; n < root.children.length; n++) {
            var node = root.children[n];
            switch (node.state) {
                case "NEW":
                    diffString += reportAdded(node, diffString);
                    break;
                case "DIFF":
                    diffString += reportDiff(node, diffString);
                    break;
                case "ORIG":
                    diffString += reportDeleted(node, diffString);
                    break;
                    //ignore anything else
            }
            diffString += reportTree(node, diffString);
        }
    }
    return diffString;
}

//These are all the same structure at the moment.
//May change in future to add more context
function reportAdded(node) {
    var repString = "Added: " + "\nnode: " + node.type;
    if (node.value) {
        repString += "\nvalue: \"" + node.value + "\"\n";
    }
    if (node.attributes) {
        repString += "\nattributes: \"" + inspect(node.attributes) + "\"\n";
    } else {
        repString += "\n";
    }
    return repString;
}

function reportDiff(node, diffString) {
    var rdiffString = "Changed:" + "\nnode: " + node.type + "\nseq: " + node.seq + "\nfrom: \"";
    if (node.diff) {
        rdiffString += node.value + "\"\nto: \"" + node.diff + "\"\n";
    }
    if (node.attrdiff) {
        rdiffString += "\"\nattribute(s): \"" + node.attrdiff + "\"\n";
    }
    return rdiffString;
}

function reportDeleted(node, diffString) {
    return "Deleted: " + inspect(node) + "\n";
}
