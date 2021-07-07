/*
 * Copyright (c) 2015 Cisco and/or its affiliates.  All rights reserved.
 */

package com.example.sample.plugin;

import java.util.List;
import android.util.Log;
import android.app.Application;
import android.content.res.Resources;
import android.app.Activity;
import android.os.Bundle;
import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;

import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import android.support.v4.app.ActivityCompat;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;



import com.cisco.jabber.guest.sdk.CallFragment;
import com.cisco.jabber.guest.sdk.JabberGuestCall;
import com.cisco.jabber.guest.sdk.JabberGuestCall.JabberGuestInvalidCertificateCallback;

public class EclinicCallActivity extends Activity {


    // !!! Specify your own Server and Address !!!

   public static  String DEFAULT_SERVER ="";
    //"telemedicine.cchmc.org";
    public static  String DEFAULT_ADDRESS ="";
      
     //  "device.test";
  

	public static final String EXTRA_PARAMS = "params";
    private Uri mCallUri;
    private JabberGuestCall mInstance;

    // Class to handle invalid certificate notifications
    private class JabberGuestCertificateHandler implements JabberGuestInvalidCertificateCallback {

        @Override
        public void onInvalidCertificate(String certFingerprint,
                                         String identifierToDisplay,
                                         String certSubjectCN, String referenceID,
                                         List<String> invalidReason, String subjectCertificateData,
                                         List<String> intermediateCACertificateData,
                                         boolean allowUserToAccept) {

            // For this sample we are accepting all certificates
            JabberGuestCall.getInstance().acceptInvalidCertificate(referenceID, subjectCertificateData);
        }
    }

    JabberGuestCertificateHandler mCertificateHandler = new JabberGuestCertificateHandler();


    private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (JabberGuestCall.ACTION_CALL_STATE_CHANGED.equals(action)) {
                processCallStateChanged(intent);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
		Log.d("Ammar", "onCreate");
		Intent startIntent = getIntent();
            String paramStr = startIntent.getStringExtra(EXTRA_PARAMS);
            JSONObject params;
            try { params = new JSONObject(paramStr); }
            catch (JSONException e) { params = new JSONObject(); }
            DEFAULT_SERVER = params.optString("server");
            DEFAULT_ADDRESS = params.optString("address");
        super.onCreate(savedInstanceState);
		String package_name = getApplication().getPackageName();
        setContentView(getApplication().getResources().getIdentifier("activity_ecliniccall", "layout", package_name));
        //setContentView(R.layout.activity_main);

//      The Jabber Guest SDK for Android uses H.264 AVC video, which requires activation of license agreement
//      by each user. If your application uses any of our included SDK components that use this functionality
//      (SelfView, PreviewView, PreviewFragment, or JabberGuestCallActivity), the user will be prompted to 
//      activate the video license with a DialogFragment. Once the user activates the video license, they will
//      not be prompted to do so again for subsequent calls. If the app is uninstalled or reinstalled, the video 
//      license will need to be reactivated.
//
//      If your application does not use any of those SDK components, you will have to provide the JabberGuestCall
//      instance with a valid activity context where this dialog can be displayed prior to calling start() or 
//      setSelfTextureView(TextureView textureView) on your JabberGuestCall instance; see the documentation for
//      the registerContext(Context context) method of the JabberGuestCall class for more details. Failure to
//      register a context with your JabberGuestCall instance prior to calling start() or 
//      setSelfTextureView(TextureView textureView) will result in an error being logged, and your calls will
//      not be allowed to proceed.
//        
//      If your company has it's own license agreement for H.264 AVC video from MPEG LA, and you wish to disable
//      the display of the video license DialogFragment, place the following code in your app before calls are 
//      made to start() or setSelfTextureView(TextureView textureView) on your JabberGuestCall instance:
//        
    //  JabberGuestCall.disableVideoLicenseActivation(getApplicationContext());

        // ActivityCompat.requestPermissions(EclinicCallActivity.this,
                // new String[] { Manifest.permission.CAMERA
                        // ,Manifest.permission.ACCESS_NETWORK_STATE,
                        // Manifest.permission.BLUETOOTH,
                        // Manifest.permission.INTERNET,
                        // Manifest.permission.MODIFY_AUDIO_SETTINGS,
                        // Manifest.permission.RECORD_AUDIO,
                        // Manifest.permission.READ_PHONE_STATE,
                        // Manifest.permission.BROADCAST_STICKY
                    // },1);


        // Compose a URI to initialize the JabberGuestCall
        mCallUri = JabberGuestCall.createUri(DEFAULT_SERVER, DEFAULT_ADDRESS, null);

        //Always create a new instance for a new call.
        if (checkSelfPermission(Manifest.permission. READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {

            return;
        }
        mInstance = JabberGuestCall.createInstance(this, mCallUri);
        /* 
         * the call won't start unless you register a context in this case.
         * If not, you will see an error from the log.
         * "Failed to display Video License activation dialog. Context not registered!"
         */
        mInstance.registerContext(this);

        // Register the JabberGuestInvalidCertificateCallback
        JabberGuestCall.registerInvalidCertificateHandler(mCertificateHandler);
        showCall();
        // Handle the user clicking the button
       /* findViewById(R.id.callButton).setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                showCall();             
            }

        });     */

    }
    
    @Override
    protected void onResume() {
        super.onResume();
        JabberGuestCall.registerReceiver(getApplicationContext(), mBroadcastReceiver);
    }

    @Override
    protected void onPause() {
        super.onPause();
        JabberGuestCall.unregisterReceiver(mBroadcastReceiver);
    }
    
    protected void processCallStateChanged(Intent intent) {
        JabberGuestCall.State state = (JabberGuestCall.State) intent.getSerializableExtra(JabberGuestCall.ARG_CALL_STATE_VALUE);
        
        if (state == JabberGuestCall.State.GuestCallStateDisconnecting) {
            Toast.makeText(getApplicationContext(), "Ending call......", Toast.LENGTH_LONG).show();
        } else if (state == JabberGuestCall.State.GuestCallStateConnecting) {
            Toast.makeText(getApplicationContext(), "Connecting......", Toast.LENGTH_LONG).show();
        } else if (state == JabberGuestCall.State.GuestCallStateDisconnected) {
            //Intent newIntent = getIntent();
            //newIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
           // startActivity(newIntent);
			super.onBackPressed();
            finish();
        }
        
    }

    /**
     * Show the Jabber Guest Call Fragment.
     */
    private void showCall() {
		Log.d("Ammar-showcall", "ic");
        CallFragment callFragment = new CallFragment();
		
		String package_name = getApplication().getPackageName();
		Resources resources = getApplication().getResources();
		int ic = resources.getIdentifier("placeHolderLinearLayout", "id" ,package_name);
		Log.d("Ammar-ic", "ic");

        
		
        getFragmentManager().beginTransaction().replace(ic, callFragment).commit();

        findViewById(ic).setVisibility(View.VISIBLE);

        if (mInstance != null) {
            mInstance.start();
        }
    }

}
