var gulp = require('gulp');

var install = require("gulp-install");
//var download = require("gulp-download");

gulp.task('bower', function() {
    process.chdir('./public/app/');
    gulp.src(['./bower.json'])
    .pipe(install());
    process.chdir('../../');
});

gulp.task('default',  ['bower'], function() {
// sequence is doing the stuff in order

});
