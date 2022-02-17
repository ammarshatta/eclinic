package com.linkdev.eclinic.plugin;

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


public class EclinicPlugin extends CordovaPlugin {

	 // instance of the call back when requesting or checking authorisation
	private CallbackContext authReqCallbackCtx;
	
	private String [] permissions = { Manifest.permission.ACCESS_NETWORK_STATE,
			Manifest.permission.BLUETOOTH,
			Manifest.permission.CAMERA,
			Manifest.permission.INTERNET,
			Manifest.permission.MODIFY_AUDIO_SETTINGS,
			Manifest.permission.READ_PHONE_STATE,
			Manifest.permission.RECORD_AUDIO,
			Manifest.permission.BROADCAST_STICKY
			};
	private static final int REQUEST_CODE = 1;
	

  
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        Context context = cordova.getActivity().getApplicationContext();
		authReqCallbackCtx = callbackContext;
			
        if(action.equals("new_activity")) {
			
           
			Log.i("ammar-first-args", args.toString());
			if(hasAllPermissions(permissions)){
				
				this.openNewActivity(context,args);
			}else{
			PluginResult pluginResult = new PluginResult(PluginResult.Status.ERROR ,"Please Accept Permissions");
			callbackContext.sendPluginResult(pluginResult);
			return false;
			}
			
			PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
			callbackContext.sendPluginResult(pluginResult);
            return true;
        }
		if(action.equals("isAuthorized")) {
			
			
			if(hasAllPermissions(permissions)){
			PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
			callbackContext.sendPluginResult(pluginResult);
			return true;
			}else{
			PluginResult pluginResult = new PluginResult(PluginResult.Status.ERROR ,"Not Authorized");
			callbackContext.sendPluginResult(pluginResult);
			return false;
			}
			
        }
		
		if(action.equals("requestPermissions")) {
			
			if(hasAllPermissions(permissions)){
			PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, true);
			callbackContext.sendPluginResult(pluginResult);
			
			return true;
			}else{
			cordova.requestPermissions(this, REQUEST_CODE, permissions);
			
			return true;
			}
			
        }
		
		callbackContext.error("\"" + action + "\" is not a recognized action.");

        return false;
    }

    private void openNewActivity(Context context,JSONArray args) {
       // Intent intent = new Intent(context, NewActivity.class);
       // this.cordova.getActivity().startActivity(intent);
	JSONObject options;
      try {
         options = args.getJSONObject(0);
      } catch (JSONException e) {
        authReqCallbackCtx.error("Error encountered: " + e.getMessage());
        return ;
      }
	
		 try {
        Context cordovaContext = cordova.getActivity()
                    .getApplicationContext();
            Intent intent = new Intent(cordovaContext, EclinicCallActivity.class);
			intent.putExtra(EclinicCallActivity.EXTRA_PARAMS, options.toString());
            cordova.getActivity().startActivity(intent);
      } catch (Exception  e) {
		Log.i("ammar-create plugin",e.getMessage());
		
        authReqCallbackCtx.error("Error encountered: " + e.getMessage());
        return ;
      }
			
	  // cordova.getActivity().runOnUiThread(new Runnable() {
        // @Override
        // public void run() {
			
            // Context context = cordova.getActivity()
                    // .getApplicationContext();
            // Intent intent = new Intent(context, EclinicCallActivity.class);
			// intent.putExtra(EclinicCallActivity.EXTRA_PARAMS, options.toString());
            // cordova.getActivity().startActivity(intent);
        // }
    // });
	
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
    if (requestCode == REQUEST_CODE ) {
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
	  PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, true);
	  authReqCallbackCtx.sendPluginResult(pluginResult);
      Log.i("ammar-onRequestPermissionResult", "All dynamic permissions accepted");
     
    }
  }
	
	
	
	
}