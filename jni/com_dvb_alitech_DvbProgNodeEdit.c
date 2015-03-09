#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <api/libdb/db_config.h>
#include "com_dvb_alitech_DvbProgNodeEdit.h"

#define  LOG_TAG    "libdvbProgNodeEdit"
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  LOGE(...)	__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


/*
 * Class:     com_dvb_alitech_DvbProgNodeEdit
 * Method:    deleteProg
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbProgNodeEdit_deleteProg
  (JNIEnv *env, jclass cls, jint prog_id) {
  	int ret = 0;

	ret = ALiDVB_DeleteNodeExt(TYPE_PROG_NODE ,prog_id);
	//ret = ALiDVB_DeleteNode(TYPE_PROG_NODE ,prog_id);

	if(ret)
		return 0;
	else
		return 1;
}


/*
 * Class:     com_dvb_alitech_DvbProgNodeEdit
 * Method:    moveProg
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_DvbProgNodeEdit_moveProg
  (JNIEnv *env, jclass cls, jint src_pos,jint dst_pos) {
  	int ret = 0;

	ret = ALiDVB_ProgMove(src_pos ,dst_pos);

	if(ret)
		return 0;
	else
		return 1;
}


/*
 * Class:     com_dvb_alitech_DvbProgNodeEdit
 * Method:    updateData
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_DvbProgNodeEdit_updateData
  (JNIEnv *env, jclass cls) {
  	int ret = 0;

	ret = ALiDVB_DbUpdateData();

	if(ret)
		return 0;
	else
		return 1;
}



