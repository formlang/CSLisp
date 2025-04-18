import gulp from 'gulp';
const {src, dest, series, task} = gulp;
import concat from 'gulp-concat';
import minify from 'gulp-minify';
import cleanCss from 'gulp-clean-css';
import rev from 'gulp-rev';
// import bumpversion from 'gulp-bump';
import replace from 'gulp-replace';

import fs from 'fs';

function getVersion() {
    return fs.readFileSync('./VERSION', 'utf8', function(err, data) {
        return data;
    });
};

function bumpVersion() {

    const newVer = getVersion().trim();

// bump versions on package/bower/manifest
    return src(['common.props'])
        .pipe(replace(/<Version>[0-9-\.a-z]+<\/Version>/g, '<Version>' + newVer + '</Version>'))
        .pipe(dest(function(x) {
            return x.base;
        }));
}


export const bump = bumpVersion;

export default bump;
