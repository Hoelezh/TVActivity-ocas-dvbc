package com.alitech.dvb;

public class DvbProgNodeEdit {
	
	public static native boolean deleteProg(int prog_id);
	
	public static native boolean moveProg(int src_pos, int dst_pos);
	
	public static native boolean updateData();
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}
}
