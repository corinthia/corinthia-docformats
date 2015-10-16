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
var path = require('path');
var favicon = require('static-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
// var bodyParser = require('body-parser');

var routes = require('./routes/index');
var spawn = require('child_process').spawn;

var Busboy = require('busboy');
var inspect = require('util').inspect;
var os = require('os');
var fs = require('fs');

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

//server.use('/', routes);

server.get('/app', function(req, res, next) {
    req.redirect('app/index.html');
    next(err);
});

server.use('/doc/output/*', function(req, res, next) {
    filein = path.basename(req.originalUrl);
    odfFile = path.join('public/input', filein);
    console.log("Edit " + filein + " " + odfFile);
    runcorinthia(filein, res, 'p');
});

server.use('/doc/delete/*', function(req, res, next) {
    filein = path.basename(req.originalUrl);
    odfFile = path.join('public/input', filein);
    console.log("Delete " + filein + " " + odfFile);
    fs.unlinkSync(odfFile);
    //do we need to get rid of the corresponding html files too?
    //would be cleaner
    var outfile = 'public/app/output/' + filein + '.html';
    if(fs.existsSync(outfile)) {
         console.log(outfile + ' exists so deleting');
         fs.unlinkSync(outfile); //delete any existing
    }
    getDocs();
    res.redirect('../../app/index.html');
    res.end();
});

server.post('/process', function(req, res) {
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
            console.log("File steamed to " + odfFile);
            runcorinthia(filein, res, 'p');
    });

    req.pipe(bb);
});

server.post('/app/edit/*', function(req, res) {
    var bb = new Busboy({
        headers : req.headers
    }); 
    filein = path.basename(req.url);
    console.log('so file is ' + filein);

    bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
        console.log('Field [' + fieldname + ']: value: ' + inspect(val));
        odfFile = path.join('public/input',(val));
        filein = val;
      });

    bb.on('finish', function() {
            console.log("Edit " + odfFile);
            runcorinthia(filein, res, 'p');
    });

    req.pipe(bb);
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
           runcorinthiaPut(res, doc);
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


var runcorinthia = function(filein, res, doc) {
    var errmsg;
    console.log('process ' + process.cwd() + ' odfFile ' + odfFile);
    var outfile = 'public/app/output/' + filein + '.html';
    fs.exists(outfile, function(exists)  {
        if(exists) {
            console.log(outfile + ' exists so deleting');
            fs.unlinkSync(outfile); //delete any existing
        }
        var cmdArgs = ['get'];
        cmdArgs.push(odfFile);
        cmdArgs.push(outfile);
        console.log('Do the Corinthia ' + odfFile + ' to ' + outfile);
        ls = spawn('../../build/bin/dfconvert', cmdArgs);

        ls.stdout.on('data', function (data) {
            console.log('stdout: ' + data);
        });

        ls.stderr.on('data', function (data) {
            console.log('stderr: ' + data);
            errmsg = data;
        });

        ls.on('close', function (code) {
            console.log('child process exited with code ' + code);
            if(code == 0) {
                console.log('redirect too ' + outfile);
                res.redirect('../../app/output/'+filein+'.html');
                fs.renameSync('abstract.json', 'public/app/output/abstract.json');
                fs.renameSync('concrete.json', 'public/app/output/concrete.json');
                getDocs();
            } else {
            res.render('error', {message: 'input/' + filein});
            }
            res.end();
        });
    });
}

var runcorinthiaPut = function(res, doc) {
    console.log('Corinthia Put ');
    var errmsg;

    //need to take the doc and write it to a file on disk
    var outfile = 'public/app/output/' + filein + '.html';
    var fd = fs.openSync(outfile, 'w');
    fs.writeSync(fd, doc);
    fs.closeSync(fd);

    var cmdArgs = ['put'];
    cmdArgs.push(odfFile);
    cmdArgs.push(outfile);
    console.log('Do the Corinthia ' + odfFile + ' put ' + outfile);
//    console.log(cmdArgs);
    ls = spawn('../../build/bin/dfconvert', cmdArgs);

    ls.stdout.on('data', function (data) {
        console.log('stdout: ' + data);
    });

    ls.stderr.on('data', function (data) {
        console.log('stderr: ' + data);
        errmsg = data;
    });

    ls.on('close', function (code) {
        console.log('child process exited with code ' + code + ' from ' + odfFile);
        if(code == 0) {
            res.redirect('../../app/index.html');
            fs.renameSync('abstractPut.json', 'public/app/output/abstractPut.json');
            fs.renameSync('concretePut.json', 'public/app/output/concretePut.json');
            getDocs();
        }
        else {
            res.render('error', {message: 'input/' + filein});
        }
        res.end();
    });
}

var getDocs = function() {
    var filesData = {files:[]}
    var filesArray = fs.readdirSync("public/input");
    for(var i=0; i<filesArray.length; i++)
    {
        var stat = fs.statSync("public/input/" + filesArray[i]);
        filesData.files[i] = {};
        filesData.files[i].name = filesArray[i];
        var fdate = new Date(stat.mtime);
        filesData.files[i].mtime = fdate.toLocaleString();;
    }
    var filesStr = JSON.stringify(filesData);
    var fd = fs.openSync("public/app/docs.json", 'w');
    fs.writeSync(fd, filesStr);
    fs.closeSync(fd);
}

module.exports = server;
