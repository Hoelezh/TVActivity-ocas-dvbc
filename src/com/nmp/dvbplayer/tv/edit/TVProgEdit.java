package com.nmp.dvbplayer.tv.edit;

import com.alitech.dvb.DvbChannelList;
import com.alitech.dvb.DvbSystem;
import com.nmp.dvbplayer.R;
import com.nmp.dvbplayer.tv.TVActivity;
import com.nmp.dvbplayer.tv.search.TVSearchSetting;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.Button;
import android.widget.ListView;

public class TVProgEdit extends Activity{
	private static final String Tag = "TVProgEdit";
	public static final int PROG_EDIT_DEL_MASK  = 1;
	public static final int PROG_EDIT_MOVE_MASK  = 2;
	//private static final int    ReqCode = 1;
	private ListView mProglistView;
	private TVProgEditAdapter mProgAdpt ;
	private Button mSaveButton;
	private Button mCancleButton;
	private boolean mEditFlag =false;
	private TVProgEdit mActivity;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.setContentView(R.layout.tv_prg_edit);
		//int rid = R.id.tv_prg_edit;
//		RelativeLayout relLayout = (RelativeLayout)this.findViewById(rid);
//		View.inflate(this, R.layout.tv_prog_edit_list, relLayout);
		
		//Log.i(Tag, "onCreate");
		mActivity = this;
		mProglistView = (ListView)findViewById(R.id.tv_prg_listview);
		mProglistView.setOnKeyListener(new OnKeyListener(){
			@Override
			public boolean onKey(View view, int keyCode, KeyEvent event) {
				return listViewKeyEvent(keyCode, event);
			}
		});
		mProgAdpt = new TVProgEditAdapter(this);
		mProglistView.setAdapter(mProgAdpt);
		mSaveButton =  (Button) findViewById(R.id.tv_prg_save_edit);
		mCancleButton =  (Button) findViewById(R.id.tv_prg_cancle_edit);
		
		mSaveButton.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				mEditFlag = mProgAdpt.syncChange2DB();
				if(mEditFlag){
					mProgAdpt.notifyDataSetChanged();
					DvbChannelList.DvbChannels.clear();
					
				}
				Log.i(Tag,"mSaveButton:onClick");
			}
		});
		
		mCancleButton.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				if(mProgAdpt.resetEditState()){
					mProgAdpt.notifyDataSetChanged();
				}
				Log.i(Tag,"mCancleButton:onClick");
			}
		});
		
		Button delall =  (Button) findViewById(R.id.tv_prg_delet_all);
		delall.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				Log.i(Tag,"delallButton:onClick");
				DvbSystem.loadDefault();
				mEditFlag = true;
				mProgAdpt.updateData();
				mProgAdpt.notifyDataSetChanged();
				DvbChannelList.DvbChannels.clear();
				Intent intent = new Intent(mActivity, TVSearchSetting.class);
				mActivity.startActivityForResult(intent, TVActivity.ReqCode);
				
			}
		});
	}
	
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (TVActivity.ReqCode == requestCode && resultCode == Activity.RESULT_OK) {
			int result = data.getIntExtra("result", 0);
			if (result > 0) {
				setResult(RESULT_OK, data);
				finish();
			}
		}
	}
	
	private boolean listViewKeyEvent(int keyCode, KeyEvent event) {
		boolean result = false;
		
		if (event.getAction() != KeyEvent.ACTION_DOWN) {
			return result;
		}
		
		if (keyCode == KeyEvent.KEYCODE_DPAD_UP ||
				keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
			int direct;
			if(KeyEvent.KEYCODE_DPAD_UP == keyCode){
				direct =1;
			}
			else{
				direct = -1;	
			}
			if(mProgAdpt.changeItemPosition(mProglistView.getSelectedItemPosition(), direct)){
				mProgAdpt.notifyDataSetChanged();	
			}
		}		
		else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT ||
				keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
			int mark;
			if(keyCode == KeyEvent.KEYCODE_DPAD_LEFT){
				mark = PROG_EDIT_DEL_MASK;
			}
			else{
				mark =PROG_EDIT_MOVE_MASK;
			}
			mProgAdpt.setEditFlag(mProglistView.getSelectedItemPosition(), mark);
			mProgAdpt.notifyDataSetChanged();
			result = true;
		}		
		
		if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||keyCode == KeyEvent.KEYCODE_ENTER ){
			int curPos= mProglistView.getSelectedItemPosition();
			if(0!= (PROG_EDIT_MOVE_MASK & (mProgAdpt.getEditFlag(curPos)))){
				mProgAdpt.setEditFlag(curPos,PROG_EDIT_MOVE_MASK);
			}
			result = true;	
		}
		
		return result;
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		if(keyCode == KeyEvent.KEYCODE_ESCAPE ||
				keyCode == KeyEvent.KEYCODE_BACK) 
		{
			if(mEditFlag){
				mEditFlag =false;
				changeResult();
			}
		}

//		if(keyCode == KeyEvent.KEYCODE_F11 ) {
//			
//			keyHandled = true;
//		}
		
		if(keyHandled == false)
			keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
	
	private void changeResult()
	{
		Intent intent = new Intent();
		intent.putExtra("result", mProgAdpt.getCount());
		setResult(RESULT_OK, intent);
		//finish();
	}

}
