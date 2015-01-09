package com.nmp.dvbplayer.tv;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.res.Resources;
import android.os.Environment;
import android.provider.ContactsContract.CommonDataKinds.Email;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.alitech.dvb.DvbUdrm;
import com.alitech.dvb.DvbUdrmInfo;
import com.nmp.dvbplayer.R;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;


public class TVUdrmView extends TVWidget implements OnClickListener, OnItemClickListener {
	private static final int viewIndex_info = 0;
	private static final int viewIndex_emaillist = 1;
	private static final int viewIndex_ppclist = 2;
	private static final int viewIndex_setting = 3;
	private TVActivity mActivity;
	private ArrayList<View> mSelfView;
	private View   mInfoView;
	private String TAG = "TVUdrmView";
	private TextView textView;
	private int viewIndex;
	private DvbUdrmInfo dvbUdrmInfo;

	public TVUdrmView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_udrm_info, (RelativeLayout)view);
		

		this.mInfoView = this.mActivity.findViewById(R.id.tv_udrm_info);
		
		mSelfView = new ArrayList<View>();
		mSelfView.add(mInfoView);

		this.mActivity.dvbUdrm = new DvbUdrm();

		this.hide();	
	}
	private String do_exec(String cmd) { 
            String ret = "\n"; 
            try { 
                        Process p = Runtime.getRuntime().exec(cmd); 
                        BufferedReader in = new BufferedReader( 
                                                                new InputStreamReader(p.getInputStream())); 
                        String line = null; 
                        while ((line = in.readLine()) != null) { 
                                ret += line + "\n";                                 
                        } 
                } catch (IOException e) { 
                        // TODO Auto-generated catch block 
            Log.e(TAG, e.getMessage()); 
                } 
            Log.d(TAG, ret); 
                return ret;             
    } 
        
	public String getLocalMacAddress() {	 
	//		  WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);	   
	//		  WifiInfo info = wifi.getConnectionInfo(); 	
	//		  String mac = info.getMacAddress(); 
				String mac = null; 
		
			if(mac == null){ 
					String netcfg = do_exec("netcfg"); 
					String[] result= netcfg.split("\n"); 
					for(int i = 0;i<result.length;i++){ 
							if(result[i].startsWith("eth0")){ 
									String eth0 = result[i]; 
									int p=eth0.indexOf(":"); 
									mac = eth0.substring(p-2); 
									mac=mac.replace(":", "-").toUpperCase(); 
							} 
					} 
			} 
			
			
			return mac; 
		} 
			
		
	private void load_info() {
		dvbUdrmInfo = DvbUdrm.getUdrmInfo();

		textView = (TextView) this.mActivity.findViewById(R.id.tv_udrm_sn);
		textView.setText(""+dvbUdrmInfo.getUdrm_user_sn());
		
		textView = (TextView) this.mActivity.findViewById(R.id.tv_mac);
		textView.setText(getLocalMacAddress());

	}

	@Override
	protected View getView() {
		return mSelfView.get(viewIndex);
	}

	@Override
	public boolean accept(int keyCode) {

			if (KeyEvent.KEYCODE_ENTER == keyCode) 
			{
				
				Log.i(TAG, "aaaa->"); 
				return true;
			}
			return false;
	}

	@Override
	public boolean onKeyDown(int keyCode) {

			if (KeyEvent.KEYCODE_ENTER == keyCode) 
			{
				
				return true;
			}
			
			return false;
	}

	@Override
	public void focus(boolean f) {
	
	}

	
	
	 
	
	 
		// 写文件
	 
		void writerTxt() {
	 
			BufferedWriter fw = null;
	 
			try {
	 
				File file = new File("/mnt/usb1/sn.txt");
	 
				fw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file, true), "UTF-8")); // 指定编码格式，以免读取时中文字符异常
	 
				fw.append("我写入的内容");
	 
				fw.newLine();
	 
				fw.append("我又写入的内容");
	 
				fw.flush(); // 全部写入缓存中的内容
	 
			} catch (Exception e) {
	 
				e.printStackTrace();
	 
			} finally {
	 
				if (fw != null) {
	 
					try {
	 
						fw.close();
	 
					} catch (IOException e) {
	 
						e.printStackTrace();
	 
					}
	 
				}
	 
			} 
	 
	}
	public boolean write_to_usb(){  
		String s = new String();  
		String s1 = new String();  
		
		if(Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED) == false){
			
			this.mActivity.showUdrmOsd("u盘不存在",1000);
			Log.i(TAG, "aaaa11222->"); 
			return false;
		}
		
		try {   
				File f = new File("/mnt/usb1/sn.txt");   
				if(f.exists()){    
					Log.i(TAG, "aaaa11->"); 
				}
				else{    
					Log.i(TAG, "file not exist->"); 
						f.createNewFile();//不存在则创建 
				}  
				@SuppressWarnings("resource")
				BufferedReader input = new BufferedReader(new FileReader(f));      
				while((s = input.readLine())!=null){    
					s1 += s+"\n";   
					
					Log.i(TAG, "aaa3333->"); 
				}   
				Log.i(TAG, s1);
				s1 += "TEST";
				
				Log.i(TAG, s1);
				
				
				BufferedWriter output = new BufferedWriter(new FileWriter(f));   
				output.write(s1);   
				output.close();  
			} 
			catch (Exception e){
				e.printStackTrace();  
			} 
			return true;
		} 
	public int getViewIndex() {
		return viewIndex;
	}
	public void setViewIndex(int Index) {
		this.hide();
		this.viewIndex = Index;
		mSelfView.get(viewIndex).setVisibility(View.VISIBLE);
	}
	@Override
	public void show() {
		// TODO Auto-generated method stub
		load_info();
		super.show();
	}
	
	@Override
	public void hide() {
		this.viewIndex = viewIndex_info;
		for (int i = 0; i <mSelfView.size(); i++) {
			if(View.VISIBLE == mSelfView.get(i).getVisibility())
				mSelfView.get(i).setVisibility(View.GONE);
		}		
	}

	@Override
	public void onClick(View v) {
	
	}
	@Override
	public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
		
	}
	
	private boolean onKeyDown_setting(int keyCode) {
		
		return false;
	}
	private boolean onKeyDown_info(int keyCode) {
	
		return false;
	
	}



}
