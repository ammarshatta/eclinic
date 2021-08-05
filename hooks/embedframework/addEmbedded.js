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
  timeout: 7200000

};
const file = fs.createWriteStream(pluginPathInPlatformIosDir);
// return myGetter("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.a",options, function(response) {
  // response.pipe(file);
  
 // console.log("callback");
    // }).then(stats => {
      // console.log('eclinic after download');
    // });


 return new Promise(function (resolve) {
       http.get("http://ws2019-02.uaenorth.cloudapp.azure.com/JabberGuest.a",options, function(response) {
		   console.log("downloaded");
  var pipe = response.pipe(file);
      pipe.on("finish",function () {
		console.log("Finished");
        resolve();
      });
	   pipe.on("end",function () {
		console.log("ended");
        resolve();
      });
	   pipe.on("error",function () {
		console.log("error");
        reject("file error");
      });
	  pipe.on("close",function () {
		console.log("error");
        reject("file error");
      });
	  
	  

	  

 })
 }).finally(() => file.close();
	console.log("finally")
 );
     
 
 
};
