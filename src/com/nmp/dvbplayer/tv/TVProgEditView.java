package com.nmp.dvbplayer.tv;

import com.alitech.dvb.DvbChannelList;
import com.nmp.dvbplayer.R;
import com.nmp.dvbplayer.tv.data.ChannelList;
import com.nmp.dvbplayer.tv.edit.TVProgEdit;
import com.nmp.dvbplayer.tv.edit.TVProgEditAdapter;
import com.nmp.dvbplayer.tv.search.TVSearchSetting;

import android.content.Intent;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class TVProgEditView  extends TVWidget {
	private TVActivity mActivity;
	private TextView   mSelfView;
	public TVProgEditView(TVActivity activity)
	{
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_prog_edit_view, (RelativeLayout)view);
		this.mSelfView = (TextView)this.mActivity.findViewById(R.id.tv_prog_edit_view);
		this.hide();
	}
	@Override
	protected View getView() {
		// TODO Auto-generated method stub
		return this.mSelfView;
	}
	@Override
	public boolean accept(int keyCode) {
		// TODO Auto-generated method stub
		if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
				keyCode == KeyEvent.KEYCODE_ENTER) {
			Intent intent = new Intent(this.mActivity, TVProgEdit.class);
			this.mActivity.startActivityForResult(intent, TVActivity.ReqCode);
		}
		return false;
	}
	@Override
	public boolean onKeyDown(int keyCode) {
		// TODO Auto-generated method stub
		return true;
	}
	@Override
	public void focus(boolean f) {
		// TODO Auto-generated method stub
		
	}
	
	

}
