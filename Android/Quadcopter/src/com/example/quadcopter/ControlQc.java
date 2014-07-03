package com.example.quadcopter;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;

public class ControlQc extends Activity implements OnTouchListener {
	
	int verty = 0;
	int x = 0;
	int y = 0;
	
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
	
	public boolean onOptionsItemSelected(MenuItem item1)
    {
		switch(item1.getItemId())
    	{
    	case R.id.action_diagnostics:
    		Intent intent = new Intent(getApplicationContext(), Diagnostics.class);
    		startActivity(intent);
    		return true;
    	case R.id.action_connect:
    		
    		
    		return true;
    	default:
    		return true;
    	}		
    }
	
	@Override
    public boolean onTouch(View v, MotionEvent event) {
		switch(v.getId()) {
		case R.id.vertcontrol:
			verty = (int) event.getY();
			break;
		case R.id.horzcontrol:
			x = (int) event.getX();
			y = (int) event.getY();
			break;
		}
		
		return true;
	}


}
