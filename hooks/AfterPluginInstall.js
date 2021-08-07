const fs = require('fs');
const util = require('util');
const stat = util.promisify(fs.stat);

module.exports = function(ctx) {
    // Make sure android platform is part of build
   
console.log(ctx.opts.plugin.dir)
const pluginPathInPlatformIosDir = ctx.opts.projectRoot + '/Plugins/' + ctx.opts.plugin.id +"/src/ios/libs/JabberGuest.framework/Versions/A/JabberGuest";
//const pluginPathInPlatformIosDir = "source/platforms/ios/Ministry of Health and Prevention - Shefaa/Plugins/com-linkdev-eclinic-plugin/JabberGuest.framework/src/ios/JabberGuest.framework/Versions/A/JabberGuest"
    return stat(pluginPathInPlatformIosDir).then(stats => {
		console.log("Eclinic size");
      console.log(stats.size);
    });
};