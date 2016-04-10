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
var logger = require('morgan');
var moment = require('moment');

var os = require('os');
var fse = require('fs-extra');
var Q = require('q');
var spawn = require('child_process').spawn;

var ROOT_DIR = 'public';

var REPOSITORY = 'input/';
var OUTPUT_DIR = 'app/output/';
var DATA_DIR = 'app/data/';

var currentDoc = "";
var inputFile = '';
var dataDirectory = '';
var targetHTML = '';

//if it doesn't exist make the doc's data directory
function ensureDataDir(doc) {
    console.log('ensureDataDir');
    currentDoc = doc;
    inputFile = path.join(ROOT_DIR, REPOSITORY, doc);
    dataDirectory = path.join(ROOT_DIR, DATA_DIR, doc);
    console.log("file " + inputFile + " data to " + dataDirectory);
    fse.ensureDirSync(dataDirectory);
}

function cleanTargetHTML(file) {
    var retval = false;
    targetHTML = path.join(dataDirectory, file) + '.html';
    console.log('cleanTargetHTML ' + targetHTML);
    fse.removeSync(targetHTML);
}

function qmove(from, to) {
    var deferred = Q.defer();
    Q.nfcall(fse.exists, from)
        .then(function(retval) {
            return Q.nfcall(fse.rename, from, to);
        })
        .catch(function(err) {
            console.log(err);
            deferred.reject(err);
        })
        .done();
    return deferred.promise;
}

exports.run = function(direction, concrete, abstract) {
    var deferred = Q.defer();

    var cmdArgs = [];
    var errmsg = "";
    cmdArgs.push(direction);
    cmdArgs.push(concrete);
    cmdArgs.push(abstract);
    console.log('Corinthia ' + direction + ' ' + concrete + ' ' + abstract);

    ls = spawn('../../build/bin/dfconvert', cmdArgs);

    ls.stdout.on('data', function(data) {
        console.log('stdout: ' + data);
    });

    ls.stderr.on('data', function(data) {
        console.log('stderr: ' + data);
        errmsg = data;
    });

    ls.on('close', function(code) {
        if (code === 0) {
            deferred.resolve("Converted");
        } else {
            deferred.reject(errmsg);
        }
    });
    return deferred.promise;
};


function moveGetFiles() {
    //assume they are there - something went wrong if they're not
    qmove('abstract.json', path.join(dataDirectory, 'abstract.json'))
        .then(function(mv) {
            qmove('concrete.json', path.join(dataDirectory, 'concrete.json'));
        })
        .then(function(mv) {
            qmove('gauges_abstract.json', path.join(dataDirectory, 'gauges_abstract.json'));
        })
        .then(function(mv) {
            qmove('gauges_concrete.json', path.join(dataDirectory, 'gauges_concrete.json'));
        })
        .catch(function(err) {
            console.log("Get files moved failed " + err);
        })
        .done();
}

function movePutFiles() {
    //assume they are there - something went wrong if they're not
    qmove('abstractPut.json', path.join(dataDirectory, 'abstractPut.json'))
        .then(function(mv) {
            qmove('concretePut.json', path.join(dataDirectory, 'concretePut.json'));
        })
        .then(function(mv) {
            qmove('gauges_abstractPut.json', path.join(dataDirectory, 'gauges_abstractPut.json'));
        })
        .then(function(mv) {
            qmove('gauges_concretePut.json', path.join(dataDirectory, 'gauges_concretePut.json'));
        })
        .catch(function(err) {
            console.log("Put files moved failed " + err);
        })
        .done();
}

function runCorinthiaGet(doc, res, type) {
    var cmdArgs = ['get'];
    cmdArgs.push(inputFile);
    cmdArgs.push(targetHTML);

    console.log('Corinthia Get ' + inputFile + ' to ' + targetHTML);
    ls = spawn('../../build/bin/dfconvert', cmdArgs);

    ls.stdout.on('data', function(data) {
        console.log('stdout: ' + data);
    });

    ls.stderr.on('data', function(data) {
        console.log('stderr: ' + data);
        errmsg = data;
    });

    ls.on('close', function(code) {
        console.log('child process exited with code ' + code);
        if (code === 0) {
            var redirectTo = '/app/data/' + doc + '/' + doc + '.html';
            var resStr = "Done did it ->";
            console.log(resStr + type + ' ' + redirectTo);
            //if this was called from a submit don't want to use send
            //want a redirect. - kludge but seems to work
            if (type == 'edit') {
                res.send(redirectTo); //let the client sort it
            } else {
                res.redirect('app/index.html#edit/' + doc);
            }
            moveGetFiles();
            exports.getDocs();
        } else {
            res.render('error', {
                message: 'input/' + inputFile
            });
        }
    });
}

function runCorinthiaPut(res) {
    var cmdArgs = ['put'];
    cmdArgs.push(inputFile);
    cmdArgs.push(targetHTML);
    console.log('Corinthia Put ' + inputFile + ' put ' + targetHTML);
    ls = spawn('../../build/bin/dfconvert', cmdArgs);

    ls.stdout.on('data', function(data) {
        console.log('stdout: ' + data);
    });

    ls.stderr.on('data', function(data) {
        console.log('stderr: ' + data);
        errmsg = data;
    });

    ls.on('close', function(code) {
        console.log('child process exited with code ' + code + ' from ' + inputFile);
        if (code === 0) {
            res.redirect('../../app/index.html');
            movePutFiles();
            exports.getDocs();
        } else {
            res.render('error', {
                message: 'input/' + filein
            });
        }
        res.end();
    });
}

exports.get = function(doc, res, type) {
    console.log('process ' + process.cwd() + ' file ' + doc);
    //Do we have a working directory
    ensureDataDir(doc);
    cleanTargetHTML(doc);
    runCorinthiaGet(doc, res, type);
};

exports.put = function(res, doc) {
    console.log('Corinthia Put ');
    //need to take the doc and write it to a file on disk
    //ensureDataDir(doc);
    //targetHTML = path.join(dataDirectory,currentDoc) + '.html';
    var fd = fse.openSync(targetHTML, 'w');
    fse.writeSync(fd, doc);
    fse.closeSync(fd);
    runCorinthiaPut(res);
};

exports.getDocs = function() {
    var filesData = {
        files: []
    };
    var repo = path.join(ROOT_DIR, REPOSITORY);
    var filesArray = fse.readdirSync(repo);
    for (var i = 0; i < filesArray.length; i++) {
        var stat = fse.statSync(repo + filesArray[i]);
        filesData.files[i] = {};
        filesData.files[i].name = filesArray[i];
        var fdate = moment(stat.mtime);
        filesData.files[i].mtime = fdate.format("YYYY-MM-DD hh:mm:ss");
    }
    var filesStr = JSON.stringify(filesData);
    var fd = fse.openSync("public/app/docs.json", 'w');
    fse.writeSync(fd, filesStr);
    fse.closeSync(fd);
};
