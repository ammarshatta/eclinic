// var exec = require('cordova/exec');

// function plugin() {

// }

// plugin.prototype.new_activity = function() {
    // exec(function(res){}, function(err){}, "PluginName", "new_activity", []);
// }

// module.exports = new plugin();



// Empty constructor
function EclinicPlugin() {}

// The function that passes work along to native shells
// Message is a string, duration may be 'long' or 'short'
EclinicPlugin.prototype.new_activity = function(message, duration, successCallback, errorCallback) {
  var options = {};
  options.message = message;
  options.duration = duration;
  cordova.exec(successCallback, errorCallback, 'PluginName', 'new_activity', [options]);
}

// The function that passes work along to native shells
// Message is a string, duration may be 'long' or 'short'
EclinicPlugin.prototype.isAuthorized = function(message, duration, successCallback, errorCallback) {
  var options = {};
  options.message = message;
  options.duration = duration;
  cordova.exec(successCallback, errorCallback, 'PluginName', 'isAuthorized', [options]);
}


// Installation constructor that binds EclinicPlugin to window
EclinicPlugin.install = function() {
  if (!window.plugins) {
    window.plugins = {};
  }
  window.plugins.eclinicPlugin = new EclinicPlugin();
  return window.plugins.eclinicPlugin;
};
cordova.addConstructor(EclinicPlugin.install);
