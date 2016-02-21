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
var bodyParser = require('body-parser')
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

var server = express();

var odfFile = "";
var filein = '';

// view engine setup
// server.set('views', path.join(__dirname, 'views'));
server.set('view engine', 'jade');

// server.use(favicon());
server.use(logger('dev'));
// server.use(bodyParser.json());
// server.use(bodyParser.urlencoded());
// server.use(cookieParser());
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
/*    var outfile = 'public/app/data/' + filein + '/' + filein + '.html';
    if(fs.existsSync(outfile)) {
         console.log(outfile + ' exists so deleting');
         fs.unlinkSync(outfile); //delete any existing
    }*/
    corinthia.getDocs();
    res.redirect('../../app/index.html'); //not needed already on that page.
    res.end();
});

server.get('/', function(req, res, next) {odfFile
    console.log("default url");
    res.redirect('/app');
});

server.get('/app', function(req, res, next) {
    req.redirect('app/index.html');
    next(err);
});

server.post('/submit', function(req, res) {
    var bb = new Busboy({
        headers : req.headers
    });

    bb.on('file', function(fieldname, file, filename, encoding, mimetype) {
        console.log("Filename " + filename + " field " + fieldname);
        filein = path.basename(filename);
        odfFile = path.join('public/input',path.basename(filename));
        file.pipe(fs.createWriteStream(odfFile));
    });

    bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
        console.log('Field [' + fieldname + ']: value: ' + inspect(val));

    });

    bb.on('finish', function() {
        console.log("File streamed to " + odfFile);
        fs.stat(odfFile, function(err, stat) {
            if(err) {
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

server.post('/corput', function(req, res) {
        console.log("received corput post");
        var bb = new Busboy({
                headers : req.headers
        });

        var doc;

        bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
//          console.log('Field ' + fieldname + ': value: ' + inspect(val));

          switch(fieldname){
            case 'htmldata':
 //               console.log('corput document ' + val);
                doc = val;
            break;
          };
        });

        bb.on('finish', function() {
           console.log('corput done');
           corinthia.put(res, doc);
        });

        req.pipe(bb);
});

server.post('/help', function(req, res) {
        console.log("received help post");
        var bb = new Busboy({
                headers : req.headers
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
if (server.get('env') === 'development') {
    server.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
server.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


module.exports = server;
