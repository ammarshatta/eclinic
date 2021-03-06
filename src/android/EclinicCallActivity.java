/*
 * Copyright (c) 2015 Cisco and/or its affiliates.  All rights reserved.
 */

package com.linkdev.eclinic.plugin;

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
import android.content.res.Configuration;
import java.util.Locale;

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
import android.media.AudioManager;
import android.media.MediaPlayer;


public class EclinicCallActivity extends Activity {


    // !!! Specify your own Server and Address !!!

	public static  String DEFAULT_SERVER ="";
    //"telemedicine.cchmc.org";
    public static  String DEFAULT_ADDRESS ="";
      
     //  "device.test";
  

	public static final String EXTRA_PARAMS = "params";
    private Uri mCallUri;
    private JabberGuestCall mInstance;
	AudioManager audioManager;
    MediaPlayer mPlayer;

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
			if(JabberGuestCall.ACTION_CALL_CONTROL_EVENT.equals(action) )
			{
				CallControlChanged(intent);
			}
            
		
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
		Log.d("Ammar", "onCreate");
		Intent startIntent = getIntent();
            String paramStr = startIntent.getStringExtra(EXTRA_PARAMS);
			Log.d("Ammar-paramStr", paramStr );
            JSONObject params;
            try { params = new JSONObject(paramStr); }
            catch (JSONException e) { params = new JSONObject(); Log.d("Ammar-errorjson","" );}
            DEFAULT_SERVER = params.optString("server");

            DEFAULT_ADDRESS = params.optString("address");
	Log.d("Ammar-DEFAULT_SERVER", DEFAULT_SERVER );
	Log.d("Ammar-DEFAULT_ADDRESS", DEFAULT_ADDRESS );
        super.onCreate(savedInstanceState);
		
		  //force locale lang
	  String localeLang = params.optString("language");
	  String languageToLoad  = "ar";
	  if(localeLang.toLowerCase().contains("en")){
		  
		  //add arabic always for test locale
		
		 languageToLoad  = "en"; // your language
		
	  }
	    Locale locale = new Locale(languageToLoad); 
		Locale.setDefault(locale);
		Configuration config = new Configuration();
		config.locale = locale;
		getBaseContext().getResources().updateConfiguration(config, 
		  getBaseContext().getResources().getDisplayMetrics());
	  //end locale
		
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
		    if(mPlayer!=null)
                mPlayer.start();
			
        }else if (state == JabberGuestCall.State.GuestCallStateConnected) {
            Toast.makeText(getApplicationContext(), "Connected", Toast.LENGTH_LONG).show();
            if(mPlayer!=null && mPlayer.isPlaying())
                mPlayer.stop();

        } else if (state == JabberGuestCall.State.GuestCallStateDisconnected) {
            //Intent newIntent = getIntent();
            //newIntent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
           // startActivity(newIntent);
		   if(mPlayer!=null && mPlayer.isPlaying())
                mPlayer.stop();
		   
			super.onBackPressed();
            finish();
        }
        
    }


    protected void CallControlChanged(Intent intent) {
        JabberGuestCall.CallControlEvent event = (JabberGuestCall.CallControlEvent) intent.getSerializableExtra(JabberGuestCall.ARG_CALL_CONTROL_EVENT_VALUE);
        if (event == JabberGuestCall.CallControlEvent.audioRouteUpdated){
          if(  JabberGuestCall.getAudioRouteManager().getActiveAudioRouteType() == JabberGuestCall.AudioRouteType.earphone)
              audioManager.setSpeakerphoneOn(false);
          else
              audioManager.setSpeakerphoneOn(true);
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
			
			audioManager = (AudioManager)
                    this.getSystemService(Context.AUDIO_SERVICE);
            audioManager.setMode(AudioManager.MODE_IN_COMMUNICATION);
          //  if( JabberGuestCall.getAudioRouteManager().getActiveAudioRouteType() == JabberGuestCall.AudioRouteType.speaker)
            audioManager.setSpeakerphoneOn(true);

            mPlayer = MediaPlayer.create(this,resources.getIdentifier("r", "raw", package_name) );
            mPlayer.setLooping(true);

            mInstance.start();
        }
    }

}
