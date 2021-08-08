'use strict';

//const xcode = require('xcode'),
const http = require('http'); 
const fs = require('fs');
const path = require('path');
const util = require('util');
const myGetter = util.promisify(http.get);
const stat = util.promisify(fs.stat);
var AdmZip = require("adm-zip");




 module.exports = function(context) {
    if(process.length >=5 && process.argv[1].indexOf('cordova') == -1) {
		
        if(process.argv[4] != 'ios') {
            return; // plugin only meant to work for ios platform.
        }
    }
	
	// const pluginPathInPlatformIosDir = context.opts.projectRoot + '/Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/JabberGuest";
    const pluginPathInPlatformIosDir = 'Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/JabberGuest";
	const extractTo = 'Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/";
	const tmpZipPath ='Plugins/'+ context.opts.plugin.id +'tmpFile.zip';
	console.log(pluginPathInPlatformIosDir);
	console.log(context.opts.plugin.dir);
	
    

const options = {
  timeout: 7200000

};
const file = fs.createWriteStream(tmpZipPath);
// return myGetter("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.a",options, function(response) {
  // response.pipe(file);
 
 // console.log("callback");
    // }).then(stats => {
      // console.log('eclinic after download');
    // });

console.log(Date.now());
 return new Promise(function (resolve) {
       http.get("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.zip",options, function(response) {
		   console.log("downloaded");
		   
console.log(Date.now());
  var pipe = response.pipe(file);
      pipe.on("finish",function () {
		console.log("Finished");
		console.log(Date.now());
		file.end();
		
	var linkPath = "plugins/com-linkdev-eclinic-plugin/src/ios/JabberGuest.framework/";
    var targetPath = "Versions/A/";

    if(!fs.existsSync(linkPath + 'JabberGuest')){
		console.log('creating  symlinkSync');
        fs.symlinkSync(targetPath + 'Headers/', linkPath + 'Headers', 'dir');
        fs.symlinkSync(targetPath + 'JabberGuest', linkPath + 'JabberGuest', 'file');
    }
		var zip = new AdmZip(tmpZipPath);
		zip.extractAllTo(extractTo, true);
        resolve();
		
		
      })
	  
	  
	  
	  

	  

 })
 })
     
 
 
};
