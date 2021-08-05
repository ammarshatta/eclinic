const fs = require('fs');
const util = require('util');
const stat = util.promisify(fs.stat);

module.exports = function(ctx) {
    // Make sure android platform is part of build
    if (!ctx.opts.platforms.includes('android')) return;

    const pluginPathInPlatformIosDir = context.opts.projectRoot + '/Plugins/' + context.opts.plugin.id +"/src/ios/JabberGuest.framework/Versions/A/JabberGuest";

    return stat(pluginPathInPlatformIosDir).then(stats => {
		console.log("Eclinic size");
      console.log(stats.size);
    });
};