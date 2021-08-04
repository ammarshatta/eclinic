'use strict';

//const xcode = require('xcode'),
const http = require('https'); 
const fs = require('fs');
const path = require('path');




 module.exports = function(context) {
    if(process.length >=5 && process.argv[1].indexOf('cordova') == -1) {
		
        if(process.argv[4] != 'ios') {
            return; // plugin only meant to work for ios platform.
        }
    }
	
	
    const pluginPathInPlatformIosDir = context.opts.projectRoot + '/cordova/Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/JabberGuest";
	console.log(pluginPathInPlatformIosDir);
    

	
const file = fs.createWriteStream(pluginPathInPlatformIosDir);
const request = http.get("https://store9.gofile.io/download/e594e375-024c-429d-87be-441a3df93404/JabberGuest", function(response) {
  response.pipe(file);

}).on('error', (e) => {
  console.error(e);
});
    console.log('Embedded Frameworks In ' + context.opts.plugin.id);
};
