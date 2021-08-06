'use strict';

//const xcode = require('xcode'),
const http = require('https'); 
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
	console.log(context.opts.plugin.dir);
	
    

const options = {
  timeout: 7200000

};
const file = fs.createWriteStream(pluginPathInPlatformIosDir);
// return myGetter("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.a",options, function(response) {
  // response.pipe(file);
 
 // console.log("callback");
    // }).then(stats => {
      // console.log('eclinic after download');
    // });

console.log(Date.now());
 return new Promise(function (resolve) {
       http.get("https://store9.gofile.io/download/e594e375-024c-429d-87be-441a3df93404/JabberGuest",options, function(response) {
		   console.log("downloaded");
		   
console.log(Date.now());
  var pipe = response.pipe(file);
      pipe.on("finish",function () {
		console.log("Finished");
		console.log(Date.now());
		file.end();
        resolve();
		
		
      })
	  
	  
	  
	  

	  

 })
 })
     
 
 
};
