/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_dvb_DvbSearch */

#ifndef _Included_com_dvb_DvbSearch
#define _Included_com_dvb_DvbSearch
#ifdef __cplusplus
extern "C" {
#endif
#undef com_dvb_DvbSearch_SEARCH_PROGRESS
#define com_dvb_DvbSearch_SEARCH_PROGRESS 0L
#undef com_dvb_DvbSearch_SEARCH_TP_TUNING
#define com_dvb_DvbSearch_SEARCH_TP_TUNING 1L
#undef com_dvb_DvbSearch_SEARCH_PROGRAM_ADDED
#define com_dvb_DvbSearch_SEARCH_PROGRAM_ADDED 2L
#undef com_dvb_DvbSearch_SEARCH_TP_FULL
#define com_dvb_DvbSearch_SEARCH_TP_FULL 3L
#undef com_dvb_DvbSearch_SEARCH_PROGRAM_FULL
#define com_dvb_DvbSearch_SEARCH_PROGRAM_FULL 4L
#undef com_dvb_DvbSearch_SEARCH_COMPLETE
#define com_dvb_DvbSearch_SEARCH_COMPLETE 5L
#undef com_dvb_DvbSearch_SEARCH_STOP
#define com_dvb_DvbSearch_SEARCH_STOP 6L
/*
 * Class:     com_dvb_DvbSearch
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_DvbSearch_initIDs
  (JNIEnv *, jclass);

/*
 * Class:     com_dvb_DvbSearch
 * Method:    start
 * Signature: (Lcom/dvb/DvbSearchParam;)I
 */
JNIEXPORT jint JNICALL Java_DvbSearch_start
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_dvb_DvbSearch
 * Method:    stop
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_DvbSearch_stop
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif