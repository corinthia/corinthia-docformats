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

var path = require('path');
var inspect = require('util').inspect;

var differ = require('./differ');

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

function qmove(from, to) {
    return Q.nfcall(fse.move, from, to, {clobber: true}) ;
}

exports.moveGauges = function(prefix, testDirectory) {
    var to = path.join(TEST_DIR, testDirectory);
    qmove('abstract.json', path.join(to, prefix + 'abstract.json'))
    .then (function() {
        qmove('concrete.json', path.join(to, prefix + 'concrete.json'));
    })
    .then (function() {
        qmove('gauges_abstract.json', path.join(to, prefix + 'gauges_abstract.json'));
    })
    .then (function() {
        qmove('gauges_concrete.json', path.join(to, prefix + 'gauges_concrete.json'));
    })
    .then(function () { console.log(prefix + " files moved"); })
    .catch(function (err) { console.log(prefix + " files moved failed " + err); })
    .done();
};

exports.getAbstract = function(doc, test) {
    return TEST_DIR + test + "/" + doc + ".html";
};

exports.getConcrete = function(doc, test) {
    return TEST_DIR + test + "/" + doc;
};

exports.setup = function(doc, concrete, abstract) {
    var from = SEED_DIR + doc;
    console.log("Copy " + from + " -> " + abstract);
    fse.copySync(from, concrete);
    //delete previous html
    fse.removeSync(abstract);
};

exports.replaceAbstract = function(test, abstract, content) {
    console.log("Replace the abstract");
    var fd = fse.openSync(abstract, 'w');
    fse.writeSync(fd, content);
    fse.closeSync(fd);
};

exports.getTests = function() {
    var testData = {
        tests: []
    };
    var filesArray = fse.readdirSync(TEST_DIR);
    for (var i = 0; i < filesArray.length; i++) {
        //get the runtest.js file and add it to the overall JSON
        var testName = filesArray[i];
        var testObj = JSON.parse(fse.readFileSync(TEST_DIR + testName + "/test.json", 'utf8'));
        testData.tests.push(testObj);
    }
    var testsStr = JSON.stringify(testData);
    var fd = fse.openSync("public/app/tests.json", 'w');
    fse.writeSync(fd, testsStr);
    fse.closeSync(fd);
};

exports.writeMerged = function(test){
    //did it pass? What was expected
};

// Should we round trip the expected or have the test runner get it from the json
exports.verify = function(test, expected){
    var mergedTree = differ.merge(TEST_DIR  + test + "/getconcrete.json", TEST_DIR  + test + "/putconcrete.json");
    // save the tree so we can see it
    var filesStr =  JSON.stringify(mergedTree);
    var fd = fse.openSync(TEST_DIR  + test + "/merged.json", 'w');
    fse.writeSync(fd, filesStr);
    fse.closeSync(fd);

    var diffreport = differ.reportChanges(mergedTree, TEST_DIR  + test + "/diff.txt");

    var testObj = JSON.parse(fse.readFileSync(TEST_DIR + test + "/test.json", 'utf8'));
    if(testObj.expected === diffreport) {
        testObj.passed = true;
    } else {
        testObj.passed = false;
        testObj.reported = diffreport;
    }
    testObj.lastrun = Date().toString();

    //update test.json
    var testStr = JSON.stringify(testObj);
    var testfd = fse.openSync(TEST_DIR + test + "/test.json", 'w');
    fse.writeSync(testfd, testStr);
    fse.closeSync(testfd);
};
