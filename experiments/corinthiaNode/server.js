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

server.use('/', routes);

server.get('/app', function(req, res, next) {
    req.redirect('app/index.html');
    next(err);
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

server.post('/corput', function(req, res) {
        console.log("received corput post");
        var bb = new Busboy({
                headers : req.headers
        });

        var doc;

        bb.on('field', function(fieldname, val, fieldnameTruncated, valTruncated) {
          console.log('Field ' + fieldname + ': value: ' + inspect(val));

          switch(fieldname){
            case 'htmldata':
                console.log('corput document ' + val);
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

        var cmdArgs = ['-jar', 'odfe.jar', '-help'];

        bb.on('finish', function() {
          console.log('cmd ' + cmdArgs);
          ls    = spawn('java', cmdArgs);

          var title="ODFE Version Info";
          var info="";
          ls.stdout.on('data', function (data) {
                console.log('stdout: ' + data);
                info = info.concat( data );
          });

          ls.stderr.on('data', function (data) {
                console.log('stdout: ' + data);
                info = info.concat( data );
          });

          ls.on('close', function (code) {
              console.log('child process exited with code ' + code);
              res.render('help', {
                message: title,
                helpinfo: info
              });
              res.end();
          });
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


var runcorinthia = function(filein, res, doc, extract) {
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
        });

        ls.on('close', function (code) {
            console.log('child process exited with code ' + code);
            res.redirect('app/output/' + filein + '.html');
            res.end();
        });
    });
}

var runcorinthiaPut = function(res, doc) {
    console.log('Corinthia Put ');

    //need to take the doc and write it to a file on disk
    var outfile = 'public/app/output/' + filein + '.saved.html';
    var fd = fs.openSync(outfile, 'w');
    fs.writeSync(fd, doc);
    fs.closeSync(fd);

    var cmdArgs = ['put'];
    cmdArgs.push(odfFile);
    cmdArgs.push(outfile);
    console.log('Do the Corinthia ' + odfFile + ' put ' + outfile);
    console.log(cmdArgs);
    ls = spawn('../../build/bin/dfconvert', cmdArgs);

    ls.stdout.on('data', function (data) {
        console.log('stdout: ' + data);
    });

    ls.stderr.on('data', function (data) {
        console.log('stderr: ' + data);
    });

    ls.on('close', function (code) {
        console.log('child process exited with code ' + code + ' from ' + odfFile);
        res.render('result', {result: odfFile});
//        res.redirect('app/output/' + filein + '.html');
        res.end();
    });

}

module.exports = server;
