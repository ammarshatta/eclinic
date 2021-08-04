'use strict';

//const xcode = require('xcode'),
const http = require('http'); 
const fs = require('fs');
const path = require('path');
const util = require('util');
const myGetter = util.promisify(http.get);
const stat = util.promisify(fs.stat);




 module.exports = function(context) {
    if(process.length >=5 && process.argv[1].indexOf('cordova') == -1) {
		
        if(process.argv[4] != 'ios') {
            return; // plugin only meant to work for ios platform.
        }
    }
	
	
    const pluginPathInPlatformIosDir = context.opts.projectRoot + '/Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/JabberGuest";
	console.log(pluginPathInPlatformIosDir);
    

const options = {
  timeout: 3600000

};
const file = fs.createWriteStream(pluginPathInPlatformIosDir);
return myGetter("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.a",options, function(response) {
  response.pipe(file);
 
    }).then(stats => {
   return  stat(pluginPathInPlatformIosDir);

    }).then(stats => {
      console.log('Size of ${pluginPathInPlatformIosDir} is ${stats.size} bytes');
    });

 



if (!fs.existsSync(pluginPathInPlatformIosDir)){
            console.log("no dir ", pluginPathInPlatformIosDir);
            return;
    }
	
	
	
	
var stats = fs.statSync(pluginPathInPlatformIosDir)
var fileSizeInBytes = stats.size;
// Convert the file size to megabytes (optional)
var fileSizeInMegabytes = fileSizeInBytes / (1024*1024);
console.log("File size Eclinic"+fileSizeInMegabytes);
    console.log('Embedded Frameworks In ' + context.opts.plugin.id);
};
