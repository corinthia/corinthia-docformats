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

var gaugesMoved = "";

function qmove(from, to) {
    var deferred = Q.defer();
    fse.move(from, to, {
        clobber: true
    }, function(err) {
        if (err) {
            deferred.reject("move err " + err);
        } else {
            deferred.resolve("qmove move" + from);
        }
    });
    return deferred.promise;
}

//The moves are all independent and so we can use a Q.all
exports.moveGauges = function(prefix, testDirectory) {
    var deferred = Q.defer();
    var to = path.join(TEST_DIR, testDirectory);
    var concMove = qmove(prefix + 'concrete.json', path.join(to, prefix + 'concrete.json'));
    var absMove = qmove(prefix + 'abstract.json', path.join(to, prefix + 'abstract.json'));
    var absGaugeMove = qmove('gauges_' + prefix + 'abstract.json', path.join(to, 'gauges_' + prefix + 'putabstract.json'));
    var concGaugeMove = qmove('gauges_' + prefix + 'concrete.json', path.join(to, 'gauges_' + prefix + 'concrete.json'));

    Q.all([concMove, absMove, absGaugeMove, concGaugeMove])
        .then(function(allVals) {
            gaugesMoved = prefix;
            deferred.resolve(allVals);
        })
        .catch(function(err) {
            //        console.log("moveGauges err " + err);
            deferred.reject(err);
        })
        .done();
    return deferred.promise;
};

exports.getAbstract = function(doc, test) {
    return TEST_DIR + test + "/" + doc + ".html";
};

exports.getConcrete = function(doc, test) {
    return TEST_DIR + test + "/" + doc;
};

exports.setup = function(doc, concrete, abstract) {
    gaugesMoved = "";
    var from = SEED_DIR + doc;
    fse.copySync(from, concrete);
    //delete previous html
    fse.removeSync(abstract);
};

exports.replaceAbstract = function(test, abstract, content) {
    var fd = fse.openSync(abstract, 'w');
    fse.writeSync(fd, content);
    fse.closeSync(fd);
};

exports.getTests = function() {
    var deferred = Q.defer();

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
    deferred.resolve("built tests.json");

    return deferred.promise;
};

exports.writeMerged = function(test) {
    //did it pass? What was expected
};

// Should we round trip the expected or have the test runner get it from the json
exports.verify = function(test, expected) {
    var deferred = Q.defer();
    var getabs = TEST_DIR + test + "/getabstract.json";
    var putabs = TEST_DIR + test + "/putabstract.json";

    //the putabs has not always finished by the time we get here
    //so make sure it is around before doing the business
    //
    // maybe try the concrete first?
    var getconc = TEST_DIR + test + "/getconcrete.json";
    var putconc = TEST_DIR + test + "/putconcrete.json";
    var mergedTree = differ.merge(getconc, putconc);
    // save the tree so we can see it
    var filesStr = JSON.stringify(mergedTree);
    var fd = fse.openSync(TEST_DIR + test + "/merged.json", 'w');
    fse.writeSync(fd, filesStr);
    fse.closeSync(fd);

    var diffreport = differ.reportChanges(mergedTree, TEST_DIR + test + "/diff.txt");

    var abstractmerg = differ.merge(getabs, putabs, true);
    // save the tree so we can see it
    var absfilesStr = JSON.stringify(abstractmerg);
    var afd = fse.openSync(TEST_DIR + test + "/absmerged.json", 'w');
    fse.writeSync(afd, absfilesStr);
    fse.closeSync(afd);



    var testObj = JSON.parse(fse.readFileSync(TEST_DIR + test + "/test.json", 'utf8'));
    testObj.gauges = gaugesMoved; //Need to make sure the checked in version does not have true.
			   //could just use the lastrun date as an indicator too?
    if (testObj.expected === diffreport) {
        testObj.passed = true;
    } else {
        testObj.passed = false;
        testObj.reported = diffreport;
    }
    testObj.lastrun = Date().toString();

    //update test.json
    var testStr = JSON.stringify(testObj, null, 4);
    var testfd = fse.openSync(TEST_DIR + test + "/test.json", 'w');
    fse.writeSync(testfd, testStr);
    fse.closeSync(testfd);

    deferred.resolve("Verified");

    return deferred.promise;
};
