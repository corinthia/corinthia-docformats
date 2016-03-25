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

var express = require('express');
var bodyParser = require('body-parser');
var path = require('path');
var favicon = require('static-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
// var bodyParser = require('body-parser');

var moment = require('moment');

var routes = require('./routes/index');

var Busboy = require('busboy');
var inspect = require('util').inspect;
var os = require('os');
var fs = require('fs-extra');
var rimraf = require('rimraf');


var corinthia = require('./corinthiaProcess');
var testRunner = require('./testRunner');

var server = express();

var odfFile = "";
var filein = '';

testRunner.getTests();

// view engine setup
// server.set('views', path.join(__dirname, 'views'));
server.set('view engine', 'jade');

// server.use(favicon());
server.use(logger('dev'));
server.use(express.static(path.join(__dirname, 'public')));
server.use(bodyParser.json());

server.use('/', routes);

server.use('/doc/output/*', function(req, res, next) {
    corinthia.get(req, res);
});

server.use('/doc/delete/*', function(req, res, next) {
    // should manage this in the Corinthia file..

    filein = path.basename(req.originalUrl);
    odfFile = path.join('public/input', filein);
    console.log("Delete " + filein + " " + odfFile);
    fs.unlinkSync(odfFile);
    //do we need to get rid of the corresponding data and html files too?
    //rimraf package manages this
    rimraf('public/app/data/' + filein, function(err) {
        if (err) {
            console.log(err);
        }
    });
    corinthia.getDocs();
    res.redirect('../../app/index.html'); //not needed already on that page.
    res.end();
});

server.get('/', function(req, res, next) {
    console.log("default url");
    res.redirect('/app');
});

server.get('/app', function(req, res, next) {
    req.redirect('app/index.html');
    next(err);
});

server.post('/submit', function(req, res) {
    var bb = new Busboy({
        headers: req.headers
    });

    bb.on('file', function(fieldname, file, filename, encoding, mimetype) {
        console.log("Filename " + filename + " field " + fieldname);
        filein = path.basename(filename);
        odfFile = path.join('public/input', path.basename(filename));
        file.pipe(fs.createWriteStream(odfFile));
    });

    bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
        console.log('Field [' + fieldname + ']: value: ' + inspect(val));

    });

    bb.on('finish', function() {
        console.log("File streamed to " + odfFile);
        fs.stat(odfFile, function(err, stat) {
            if (err) {
                console.log("To be sure to be sure failed: " + err);
            } else {
                console.log("have: " + inspect(stat));
                corinthia.get(filein, res, 'submit');
            }
        });
    });

    bb.on('error', function(err) {
        console.log("File stream error" + err);
        //corinthia.get(filein, res, 'submit');
    });

    req.pipe(bb);
});

server.post('/app/edit', function(req, res) {
    corinthia.get(path.basename(req.body.name), res, 'edit');
    console.log('Edit post completed');
});

// Setup the test by getting the seed document
// and converting it to abstract HTML
// and return the url of the abstract
server.post('/app/seedtest', function(req, res) {
    var seedDoc = req.body.seedDoc;
    var test = req.body.test;

    var concrete = testRunner.getConcrete(seedDoc, test);
    var abstract = testRunner.getAbstract(seedDoc, test);
    console.log('seedtest ' + concrete + ' to ' + abstract);
    testRunner.setup(seedDoc, concrete, abstract);
    corinthia.run('get', concrete, abstract)
        .then(function(result) {
            console.log(result);
            testRunner.moveGauges('get', test);
            res.send(abstract);
            console.log('Seed test completed');
        })
        .catch(function(err) {
            console.log(err);
            res.send("Seed Failed");
        })
        .done();
    //res.send("Blah");
});

// Take the HTML in the post and replace the abstract HTML
// Update the original document
// save the gauges etc
//
// Leave the test verification to another stage.
server.post('/app/save', function(req, res) {
    console.log('save ' + inspect(req.body));
    var abstractContent = req.body.abstractHTML;
    var documentName = req.body.documentName;
    var test = req.body.test;

    var concrete = testRunner.getConcrete(documentName, test);
    var abstract = testRunner.getAbstract(documentName, test);
    console.log('save test ' + concrete + ' from ' + abstract);

    testRunner.replaceAbstract(test, abstract, abstractContent);
    corinthia.run('put', concrete, abstract)
        .then(function(result) {
            testRunner.moveGauges('put', test);
            testRunner.verify(test);
            testRunner.getTests();
            res.send("Saved");
            console.log('Saved test document');
        })
        .catch(function(err) {
            console.log(err);
            res.send("Save Failed");
        })
        .done();
});

server.post('/corput', function(req, res) {
    console.log("received corput post");
    if (req.body === null) {
        res.send("No Data");
    } else {
        corinthia.put(res, req.body.doc);
    }
});

server.post('/help', function(req, res) {
    console.log("received help post");
    var bb = new Busboy({
        headers: req.headers
    });

    var doc = "";
    var extract = "";
    bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
        console.log('Field ' + fieldname + ': value: ' + inspect(val));

    });

    bb.on('finish', function() {

    });
    req.pipe(bb);
});



// / catch 404 and forward to error handler
server.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});



// / error handlers

// development error handler
// will print stacktrace
server.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: err
    });
});

// production error handler
// no stacktraces leaked to user
/*server.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});*/


module.exports = server;
