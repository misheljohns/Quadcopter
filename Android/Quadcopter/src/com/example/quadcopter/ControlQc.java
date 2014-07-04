package com.example.quadcopter;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
//import android.widget.EditText;
import android.widget.ImageView;
//import android.widget.TextView;
import android.widget.Toast;

public class ControlQc extends Activity implements OnTouchListener {
	
	float z = 0;
	float x = 0;
	float y = 0;
	
	Handler mHandler = new Handler();
	Thread sender = new Thread(new Runnable() {
        @Override
        public void run() {
           
            while (!Thread.currentThread().isInterrupted()) {
            	
                try {
                    Thread.sleep(50);
                    mHandler.post(new Runnable() {

                        @Override
                        public void run() {
                        	bluetoothSendPos();
                            // Write your code here to update the UI.
                        }
                    });
                } catch (Exception e) {
                    
                }
            }
        }
    });
	
	QcBaseApplication app = (QcBaseApplication) getApplication();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_control_qc);
		ImageView vertcontrolview = (ImageView) findViewById(R.id.vertcontrol);
		vertcontrolview.setOnTouchListener(this);
		ImageView horzcontrolview = (ImageView) findViewById(R.id.horzcontrol);
		horzcontrolview.setOnTouchListener(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.control_qc, menu);
		return true;
	}
	
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		super.onPrepareOptionsMenu(menu);
		MenuItem item = menu.findItem(R.id.action_connect);
		if(mConnectThread != null)
		{
			item.setTitle("Disconnect");
		}
		else
		{
			item.setTitle("Connect");
		}	
		
		MenuItem item2 = menu.findItem(R.id.action_sendm);
		if((mConnectThread != null) && sender.isAlive())
		{
			item2.setTitle("Stop Send");
		}
		else
		{
			item2.setTitle("Start Send");
		}	
		
		return true;
	}
	
	
	public boolean onOptionsItemSelected(MenuItem item1)
    {
		switch(item1.getItemId())
    	{
    	case R.id.action_diagnostics:
    		Intent intent = new Intent(getApplicationContext(), Diagnostics.class);
    		startActivity(intent);
    		return true;
    	case R.id.action_connect:
    		if(mConnectThread != null)
    		{
    			stopBt();
    		}
    		else
    		{
    			startBt();
    		}		
    		return true;
    	case R.id.action_sendm:
    		if(sender.isAlive())
    		{
    			sender.interrupt();
    		}
    		else
    		{
    			sender.start();
    		}		
    		return true;
    	default:
    		return true;
    	}		
    }
	
	@Override
    public boolean onTouch(View v, MotionEvent event) {
		switch(v.getId()) {
		case R.id.vertcontrol:
			z = (int) Math.min(Math.max(event.getY(), 0), 600);
			//Log.v("QuadC", "Z = "+z);//z - 0 - 600
			//bluetoothSendPos();
			break;
		case R.id.horzcontrol:
			x = (int) Math.min(Math.max(event.getX(), 0), 600);
			y = (int) Math.min(Math.max(event.getY(), 0), 600);
			//Log.v("QuadC", "X = "+x);//x - 0 to 600
			//Log.v("QuadC", "Y = "+y);//y - 0 to 600
			//bluetoothSendPos();
			break;
		}
		
		return true;
	}
	
	//***start unclean***//
	private BluetoothAdapter bluetooth = null;
	private ConnectThread mConnectThread;
	private ConnectedThread mConnectedThread;
    public static final int MESSAGE_READ = 1;
    public static final int MESSAGE_DEVICE_NAME = 2;
    public static final int MESSAGE_TOAST = 3;
    public static final String TOAST = "toast";
	private static UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
	private static final String TAG = "MainActivity";
	private String connectedDeviceName = null;


	protected void startBt() {
		
		bluetooth = BluetoothAdapter.getDefaultAdapter();
		
		if (bluetooth == null) {
			Toast.makeText(this, "No Bluetooth adapter detected on device.", Toast.LENGTH_LONG).show();
			finish();
			return;
		}
		
		BluetoothDevice device = bluetooth.getRemoteDevice("00:06:66:4E:48:AA");
		Log.v(TAG, "connecting to 00:06:66:4E:48:AA");
		mConnectThread = new ConnectThread(device);
		mConnectThread.start();
	}

	
	public void bluetoothSendPos() {
		try {
			String send = "X"+x+"Y"+y+"Z"+z;
			//Log.v(TAG, "sending over BT:"+send);
			mConnectedThread.write(send.getBytes("US-ASCII"));
		}
		catch(Exception e) {
			
		}
	}
	
	private class ConnectThread extends Thread {
	    private final BluetoothSocket mmSocket;
	    private final BluetoothDevice mmDevice;
	 
	    public ConnectThread(BluetoothDevice device) {
	        // Use a temporary object that is later assigned to mmSocket,
	        // because mmSocket is final
	        BluetoothSocket tmp = null;
	        mmDevice = device;
	 
			if (mmDevice.getUuids() != null) {
				uuid = mmDevice.getUuids()[0].getUuid();
			} else {
				uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
			}
			
			Log.v(TAG, "Connecting with UUID: " + uuid.toString());

	        // Get a BluetoothSocket to connect with the given BluetoothDevice
	        try {
	            // MY_UUID is the app's UUID string, also used by the server code
	            tmp = device.createRfcommSocketToServiceRecord(uuid);
	        } catch (IOException e) { }
	        mmSocket = tmp;
	    }
	 
	    public void run() {
	        try {
	            // Connect the device through the socket. This will block
	            // until it succeeds or throws an exception
	            mmSocket.connect();
	        } catch (IOException connectException) {
	            // Unable to connect; close the socket and get out
				Log.e(TAG, "couldn't connect device in run()");
	        	try {
	                mmSocket.close();
	            } catch (IOException closeException) { }
	            return;
	        }
	 
	        // Do work to manage the connection (in a separate thread)
			Log.v(TAG, "connected");
	        connected(mmSocket, mmDevice);
	    }
	 
	    /** Will cancel an in-progress connection, and close the socket */
	    public void cancel() {
	        try {
	            mmSocket.close();
	        } catch (IOException e) { }
			
	        Log.v(TAG,"ConnectThread.cancel()");

	    }
	}	
	
	public synchronized void connected(BluetoothSocket socket,
			BluetoothDevice device) {

		if (mConnectedThread != null) {
			mConnectedThread.cancel();
			mConnectedThread = null;
		}
		
		Log.v(TAG, socket.toString());
		
		mConnectedThread = new ConnectedThread(socket);
		mConnectedThread.start();

		// Send the name of the connected device back to the UI Activity
		Message msg = messageHandler.obtainMessage(MESSAGE_DEVICE_NAME);
		Bundle bundle = new Bundle();
		bundle.putString("device_name", device.getName());
		msg.setData(bundle);
		messageHandler.sendMessage(msg);
	}

	private class ConnectedThread extends Thread {
		private final BluetoothSocket mmSocket;
		private final InputStream mmInStream;
		private final OutputStream mmOutStream;

		public ConnectedThread(BluetoothSocket socket) {
			mmSocket = socket;
			InputStream tmpIn = null;
			OutputStream tmpOut = null;

			// Get the input and output streams, using temp objects because
			// member streams are final
			try {
				tmpIn = socket.getInputStream();
				tmpOut = socket.getOutputStream();
			} catch (IOException e) {
			}

			mmInStream = tmpIn;
			mmOutStream = tmpOut;
		}

		public void run() {
			byte[] buffer = new byte[1024]; // buffer store for the stream
			int bytes; // bytes returned from read()

			// Keep listening to the InputStream until an exception occurs
			while (true) {
				try {
					// Read from the InputStream
					bytes = mmInStream.read(buffer);
					// Send the obtained bytes to the UI activity
					messageHandler.obtainMessage(MESSAGE_READ, bytes, -1,
							buffer).sendToTarget();
				} catch (IOException e) {
					break;
				}
			}
		}

		/* Call this from the main activity to send data to the remote device */
		public void write(byte[] bytes) {
			Log.v(TAG,"Sending Bluetooth message");
			try {
				mmOutStream.write(bytes);
			} catch (IOException e) {
			}
		}

		/* Call this from the main activity to shutdown the connection */
		public void cancel() {
			try {
				mmSocket.close();
			} catch (IOException e) {
			}
		}
	}

	private final Handler messageHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
			switch (msg.what) {
            case MESSAGE_READ:
                byte[] readBuf = (byte[]) msg.obj;
                // construct a string from the valid bytes in the buffer
                String readMessage = new String(readBuf, 0, msg.arg1);
                //TextView t = (TextView) findViewById(R.id.textView1);
                //t.setText(readMessage);
                //we can read Arduino input stuff here
                break;
            case MESSAGE_DEVICE_NAME:
                // save the connected device's name
                connectedDeviceName = msg.getData().getString("device_name");
                Toast.makeText(getApplicationContext(), "Connected to "
                               + connectedDeviceName, Toast.LENGTH_LONG).show();
                break;
            case MESSAGE_TOAST:
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                               Toast.LENGTH_SHORT).show();
                break;
            }
        }
    };	
    
    @Override 
	protected void onDestroy() {
		super.onDestroy();
	}
    
    @Override 
  	protected void onStop() {
  		super.onStop();
  		stopBt();
  	}
      
	public synchronized void stopBt() {

		if (mConnectThread != null) {
			mConnectThread.cancel();
			mConnectThread = null;
		}

		if (mConnectedThread != null) {
			mConnectedThread.cancel();
			mConnectedThread = null;
		}

	}
	
	//***end unclean***//


}
