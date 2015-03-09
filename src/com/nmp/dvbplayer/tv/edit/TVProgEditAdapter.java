package com.nmp.dvbplayer.tv.edit;

import java.util.ArrayList;
import java.util.List;

import com.alitech.dvb.DvbChannel;
import com.alitech.dvb.DvbProgNodeEdit;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class TVProgEditAdapter extends BaseAdapter {
	private static final String Tag="TVProgEditView";
	private Context mCtx;
	//private LayoutInflater mInflater;
	private List<TVChannel> mLists;
	private List<DataMap> mDataLists;
	
	public TVProgEditAdapter(Context context)
	{
		
		this.mCtx = context;
		this.updateData(DvbChannel.loadChannels(DvbChannel.CHAN_GROUP_ALL | DvbChannel.CHAN_MODE_TV));
		
	}
	
	public TVProgEditAdapter(Context context,TVChannel[] channels)
	{
		//this.mInflater = LayoutInflater.from(paramContext);
		this.mCtx = context;
//		this.mLists = new ArrayList<TVChannel>();
//		this.mDataLists = new ArrayList<DataMap>();
//		//mLists.clear();
//		if(null != channels && channels.length > 0)
//		{
//			for(int i=0;i<channels.length;i++ ){
//				this.mLists.add(channels[i]);
//				this.mDataLists.add(new DataMap(i,0));
//			}
//		}
		this.updateData(channels);
		
	}
	
	public void updateData()
	{
		this.updateData(DvbChannel.loadChannels(DvbChannel.CHAN_GROUP_ALL | DvbChannel.CHAN_MODE_TV));
	}
	
	private void updateData(TVChannel[] channels)
	{
		if(null == this.mLists)
			this.mLists = new ArrayList<TVChannel>();
		else
			this.mLists.clear();
		if(null == this.mDataLists)
			this.mDataLists = new ArrayList<DataMap>();
		else 
			this.mDataLists.clear();
		if(null != channels && channels.length > 0)
		{
			for(int i=0;i<channels.length;i++ ){
				this.mLists.add(channels[i]);
				this.mDataLists.add(new DataMap(i,0));
			}
		}
	}
	
	
	public boolean resetEditState()
	{
		boolean isEdit = false;
	    int i;
//	    Log.i(Tag,"resetEditState");
		if(null == this.mDataLists){
			this.mDataLists = new ArrayList<DataMap>();
		}
		for(i=0;i<this.mDataLists.size();i++ ){
			if(!isEdit){
				if(0 != this.mDataLists.get(i).getFlag()){
					isEdit = true;
				}
				if(i != this.mDataLists.get(i).getIdx()){
					isEdit = true;
				}
			}
			this.mDataLists.get(i).setIdx(i);
			this.mDataLists.get(i).clearFlag();
		}
		if(null != this.mLists){
			if(this.mLists.size() > this.mDataLists.size()){
				Log.i(Tag,"resetEditState,may be someting wrong!!!");
				i= this.mDataLists.size();
				for(;i<this.mLists.size();i++ ){
					this.mDataLists.add(new DataMap(i,0));
					isEdit = true;
				}
			}
			else if(this.mLists.size() < this.mDataLists.size()){
				Log.i(Tag,"resetEditState,may be someting wrong!!!");
				i= this.mLists.size();
				for(;i<this.mDataLists.size();i++ ){
					this.mDataLists.remove(i);
					isEdit = true;
				}
			}
		}
		else{
			this.mDataLists.clear();
			isEdit = true;
			Log.i(Tag,"resetEditState: clear all");
		}
		
//		for(i=0;i<this.mDataLists.size();i++ ){
//			Log.i(Tag,"after rest:"+mDataLists.get(i).getFlag()+" ; "+i+" ~ "+
//					mDataLists.get(i).getIdx());
//		}
		return isEdit;
		
	}
	
	public boolean syncChange2DB()
	{
		int cnt;
		int i;
		int j;
		int moveArrow[];
		int delArrow[];
		boolean ret =false;
		if((null == this.mDataLists)||(0==this.mDataLists.size())){
			return false;
		}
		cnt = this.mDataLists.size();
		moveArrow = new int [cnt];
		delArrow = new int [cnt];
		for(i=0;i< cnt ;i++){
			moveArrow[i]= i;
			delArrow[i]=0;
		}
		for(i=0;i< cnt ;i++){
			DataMap map = this.mDataLists.get(i);
			if(0 != (map.getFlag() & TVProgEdit.PROG_EDIT_DEL_MASK)){
				TVChannel channel = this.mLists.get(map.getIdx());
				delArrow[i]=channel.getProgId();
			}
			
		}
		
//		Log.i(Tag,"syncChange2DB;before move:");
//		for(i=0;i< cnt ;i++)
//		{
//			Log.i(Tag,"syncChange2DB;move:"+moveArrow[i]+"->"+this.mDataLists.get(i).getIdx());
//		}
//		Log.i(Tag,"syncChange2DB;start move:");
		for(i=0;i< cnt ;i++){
			DataMap map = this.mDataLists.get(i);
			if(i != map.getIdx() ){
				Log.i(Tag,"move:"+ map.getIdx()+"->"+i);
				
				int moveFrom = map.getIdx(); 
				int tmp = moveArrow[moveFrom];
				if(moveFrom > i){
					for(j=moveFrom;j> i;j--){
						moveArrow[j] = moveArrow[j-1];
					}
					for(int k=i;k<cnt;k++){
						DataMap map2 = this.mDataLists.get(k);
						int adujst = map2.getIdx();
						if((map2.getIdx() >= i)&&(map2.getIdx() <moveFrom)){
							map2.setIdx(adujst+1);
						}
					}
				}
				else{
					for(j=moveFrom;j< i;j++){
						moveArrow[j] = moveArrow[j+1];
					}
					for(int k=i;k<cnt;k++){
						DataMap map2 = this.mDataLists.get(k);
						int adujst = map2.getIdx();
						if((map2.getIdx() > moveFrom )&&(map2.getIdx() <= i)){
							map2.setIdx(adujst-1);
						}
					}
				}
				moveArrow[i]=tmp;
				
				DvbProgNodeEdit.moveProg( map.getIdx(), i);
				ret = true;	
			}
		}
//		Log.i(Tag,"syncChange2DB; move done:");
//		for(i=0;i< cnt ;i++)
//		{
//			Log.i(Tag,"move done:"+moveArrow[i]+"->"+this.mDataLists.get(i).getIdx());
//		}
		
		for(i=0;i< cnt ;i++){
			
			if(0 != delArrow[i]){
				DvbProgNodeEdit.deleteProg(delArrow[i]);
				ret = true;
//				Log.i(Tag,"syncChange2DB;del:"+ Integer.toHexString(delArrow[i]));
				
			}
		}
		if(ret){
				DvbProgNodeEdit.updateData();
				updateData(DvbChannel.loadChannels(DvbChannel.CHAN_GROUP_ALL | DvbChannel.CHAN_MODE_TV));
			}
		return ret;	
	}
	
	public int getEditFlag(int idx)
	{
		if(this.getCount() < idx)
		{
			return this.mDataLists.get(idx).getFlag();
		}
		return 0;
	}
	
	public void setEditFlag(int idx,int mark)
	{
		if(this.getCount() > idx){
			this.mDataLists.get(idx).setFlag(mark);
		}
	}
	
	public boolean changeItemPosition(int curPos,int direct)
	{
		DataMap tmp;
		//Log.i(Tag,"changeItemPosition :"+curPos+","+direct);
		if(1== direct){
			if(curPos >0){
				tmp = this.mDataLists.get(curPos);
				//Log.i(Tag,"changeItemPosition :"+tmp.getFlag());
				if(0 != (tmp.getFlag() & TVProgEdit.PROG_EDIT_MOVE_MASK)){
					this.mDataLists.set(curPos,this.mDataLists.get(curPos-1));
					this.mDataLists.set(curPos-1,tmp);
					//Log.i(Tag,"changeItemPosition done");
					return true;
				}
			}
		}
		else if(-1 == direct){
			if((curPos+1) < this.getCount()){
				tmp = this.mDataLists.get(curPos);
				//Log.i(Tag,"changeItemPosition :"+tmp.getFlag());
				if(0 != (tmp.getFlag() & TVProgEdit.PROG_EDIT_MOVE_MASK)){
					this.mDataLists.set(curPos,this.mDataLists.get(curPos+1));
					this.mDataLists.set(curPos+1,tmp);
					//Log.i(Tag,"changeItemPosition done");
					return true;
				}
			}

		}
		return false;
	}
	
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		if(null==this.mDataLists)
			return 0;
		return this.mDataLists.size();
	}

	@Override
	public Object getItem(int arg0) {
		// TODO Auto-generated method stub
		int idx;
		if(null!=this.mDataLists){
			idx = this.mDataLists.get(arg0).getIdx();
			if(null!=this.mLists){
				return this.mLists.get(idx);
			}
		}
		return null;
	}

	@Override
	public long getItemId(int arg0) {
		// TODO Auto-generated method stub
		return arg0;
	}

	@Override
	public View getView(int arg0, View arg1, ViewGroup arg2) {
		// TODO Auto-generated method stub
		
		ViewHolder localViewHolder;
		int idx;
		int flag=0;
		if(null==arg1){
			arg1 = LayoutInflater.from(mCtx).inflate(R.layout.tv_prog_edit_list,null);
		}
		{
			localViewHolder = new ViewHolder();
			
			localViewHolder.idx = ((TextView)arg1.findViewById(R.id.prog_idx));
			localViewHolder.name = ((TextView)arg1.findViewById(R.id.prog_name));
		    localViewHolder.imgDelet = ((ImageView)arg1.findViewById(R.id.prog_delet));
		    localViewHolder.imgMove = ((ImageView)arg1.findViewById(R.id.prog_move));
		    arg1.setTag(localViewHolder);
		    idx = this.mDataLists.get(arg0).getIdx();
		    flag = this.mDataLists.get(arg0).getFlag();
		    TVChannel prog=this.mLists.get(idx);
		    localViewHolder.idx.setText(prog.getNumber());
		    localViewHolder.name.setText(prog.getName());
		    
		    if(0==(flag & TVProgEdit.PROG_EDIT_DEL_MASK)) {
		    	localViewHolder.imgDelet.setVisibility(View.INVISIBLE);
		    	//Log.i(Tag,"getView :imgDelet  INVISIBLE");
		    }
		    else{
		    	localViewHolder.imgDelet.setVisibility(View.VISIBLE);
		    	//Log.i(Tag,"getView :imgDelet  VISIBLE");
		    }
		    
		    if(0==(flag & TVProgEdit.PROG_EDIT_MOVE_MASK)) {
		    	localViewHolder.imgMove.setVisibility(View.INVISIBLE);
		    	//Log.i(Tag,"getView :imgMove  INVISIBLE");
		    }
		    else{
		    	localViewHolder.imgMove.setVisibility(View.VISIBLE);
		    	//Log.i(Tag,"getView :imgMove  VISIBLE");
		    }
		}
		return arg1;
	}
	
	public final class ViewHolder
	{
		public TextView idx;
		public TextView name;
	    public ImageView imgDelet;
	    public ImageView imgMove;
	    public ViewHolder()
	    {
	    }
	 }
	
	public final class DataMap
	{
		private int  mIdx;
		private int mFlag;
	    public DataMap(int idx,int flag)
	    {
	    	this.mIdx = idx;
	    	this.mFlag = flag;
	    }
	    
	    public int getIdx()
	    {
	    	return this.mIdx;
	    }
	    
	    public void setIdx(int idx)
	    {
	    	this.mIdx = idx;
	    }
	    
	    public int getFlag()
	    {
	    	return this.mFlag;
	    }
	    
	    public void setFlag(int mark)
	    {
	    	if(0==(this.mFlag & mark)){
	    		this.mFlag |= mark;
	    	}
	    	else {
	    		this.mFlag &= ~mark;
	    	}
	    }
	    
	    public void clearFlag()
	    {
	    	this.mFlag =0;
	    }
	 }

}
