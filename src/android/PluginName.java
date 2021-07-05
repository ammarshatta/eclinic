package com.example.sample.plugin;

import android.content.Context;
import android.content.Intent;
import android.Manifest;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CordovaInterface;
import android.util.Log;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import android.content.pm.PackageManager;
import org.apache.cordova.PluginResult;


public class PluginName extends CordovaPlugin {

	 // instance of the call back when requesting or checking authorisation
	private CallbackContext authReqCallbackCtx;
  
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        Context context = cordova.getActivity().getApplicationContext();
		authReqCallbackCtx = callbackContext;
			
        if(action.equals("new_activity")) {
			
           
			String [] permissions = { Manifest.permission.ACCESS_NETWORK_STATE,
			Manifest.permission.BLUETOOTH,
			Manifest.permission.CAMERA,
			Manifest.permission.INTERNET,
			Manifest.permission.MODIFY_AUDIO_SETTINGS,
			Manifest.permission.READ_PHONE_STATE,
			Manifest.permission.RECORD_AUDIO,
			Manifest.permission.BROADCAST_STICKY
			};
			if(hasAllPermissions(permissions)){
				this.openNewActivity(context);
			}else{
				cordova.requestPermissions(this, 11, permissions);
			}
			
			PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
			callbackContext.sendPluginResult(pluginResult);
            return true;
        }
		if(action.equals("isAuthorized")) {
			
			String [] permissions = { Manifest.permission.ACCESS_NETWORK_STATE,
			Manifest.permission.BLUETOOTH,
			Manifest.permission.CAMERA,
			Manifest.permission.INTERNET,
			Manifest.permission.MODIFY_AUDIO_SETTINGS,
			Manifest.permission.READ_PHONE_STATE,
			Manifest.permission.RECORD_AUDIO,
			Manifest.permission.BROADCAST_STICKY
			};
			if(hasAllPermissions(permissions)){
			PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
			callbackContext.sendPluginResult(pluginResult);
			return true;
			}else{
				PluginResult pluginResult = new PluginResult(PluginResult.Status.ERROR,"access denied ammar");
			callbackContext.sendPluginResult(pluginResult);
			return false;
			}
			
        }
		
		callbackContext.error("\"" + action + "\" is not a recognized action.");

        return false;
    }

    private void openNewActivity(Context context) {
       // Intent intent = new Intent(context, NewActivity.class);
       // this.cordova.getActivity().startActivity(intent);
	   
	   cordova.getActivity().runOnUiThread(new Runnable() {
        @Override
        public void run() {
			
            Context context = cordova.getActivity()
                    .getApplicationContext();
            Intent intent = new Intent(context, EclinicCallActivity.class);
            cordova.getActivity().startActivity(intent);
        }
    });
	
    }
	
	 private boolean hasAllPermissions(String[] permissions) throws JSONException {

        for (String permission : permissions) {
            if(!cordova.hasPermission(permission)) {
                return false;
            }
        }

        return true;
    }
	
	@Override
  public void onRequestPermissionResult(int requestCode, String[] permissions, int[] grantResults) throws JSONException {
    if (requestCode == 11 ) {
      for (int i = 0; i < grantResults.length; i++) {
        if (grantResults[i] == PackageManager.PERMISSION_DENIED) {
          String errmsg = "Permission denied ";
          for (String perm : permissions) {
            errmsg += " " + perm;
          }
		   Log.i("ammar-denied", permissions[i]);
          authReqCallbackCtx.error("Permission denied: " + permissions[i]);
          return;
        }
      }
      // all dynamic permissions accepted!
      Log.i("ammar-onRequestPermissionResult", "All dynamic permissions accepted");
     
    }
  }
	
}