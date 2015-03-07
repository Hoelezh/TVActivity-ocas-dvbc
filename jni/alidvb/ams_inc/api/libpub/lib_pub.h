/*========================================================================================
 *
 * Copyright (C) 2011 ALi Shanghai Corp.
 *
 * Description:
 *
 * History
 *
 *   Date	    Author		Comment
 *   ========	===========	========================================
 *
 *=========================================================================================*/
 
#ifndef _LIB_PUB_H_
#define _LIB_PUB_H_

#include <adr_basic_types.h>
#include <adr_mediatypes.h>
#include <adr_sys_config.h>
#include <osal/osal.h>
#include <api/libpub/lib_as.h>
#include <hld/nim/adr_nim_dev.h>
#include <api/libpub/lib_frontend.h>

/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSCC
 *  @{
 */

/********************************************/
/*      libpub channel change notify        */
/********************************************/
#define CC_EVENT_PRE_PLAY	1
#define CC_EVENT_POST_PLAY	2
#define CC_EVENT_PRE_TUNER	3
#define CC_EVENT_POST_TUNER	4
#define CC_EVENT_PRE_STOP	5
#define CC_EVENT_POST_STOP	6

/********************************************/
/*        libpub cmd bit pattern            */
/********************************************/
#define LIBPUB_CMD_MAIN_TYPE_MASK	0xFF00
#define LIBPUB_CMD_SUB_TYPE_MASK	0x00FF

#define LIBPUB_CMD_NULL				0x0000
#define LIBPUB_CMD_CC				0x0100
#define LIBPUB_CMD_AS				0x0300


/****!! NOTE: 0x01xx is reserved for channel change!!***/
#define LIBPUB_CMD_CC_PLAY			0x0101
#define LIBPUB_CMD_CC_RESET			0x0102
#define LIBPUB_CMD_CC_STOP			0x0103
#define LIBPUB_CMD_CC_PAUSE_VIDEO	0x0104
#define LIBPUB_CMD_CC_RESUME_VIDEO	0x0105
#define LIBPUB_CMD_CC_SWITCH_APID	0x0106
#define LIBPUB_CMD_CC_SWITCH_ACH	0x0107
#define LIBPUB_CMD_CC_SHOW_LOGO		0x0108
#define LIBPUB_CMD_CC_SET_FRONTEND	0x0109
#define LIBPUB_CMD_CC_RESUME_LOGO	0x010A


/****!! NOTE: 0x03xx is reserved for channel scan!!*****/
#define LIBPUB_CMD_AS_START		0x0301
#define LIBPUB_CMD_AS_STOP		0x0302


/****!!channel change cmd bit!!****/
#define CC_CMD_NULL					0x00000000
#define CC_CMD_CLOSE_VPO			0x00000001
#define CC_CMD_STOP_AUDIO			0x00000002
#define CC_CMD_STOP_VIDEO			0x00000004
#define CC_CMD_STOP_DMX				0x00000008
#define CC_CMD_FILL_FB				0x00000010
#define CC_CMD_START_AUDIO			0x00000020
#define CC_CMD_START_VIDEO			0x00000040
#define CC_CMD_START_DMX			0x00000080
#define CC_CMD_DMX_CHG_APID			0x00000100
#define CC_CMD_AUDIO_SWITCH_CHAN	0x00000200
#define CC_CMD_SET_FRONTEND			0x00000400
#define CC_CMD_PAUSE_VIDEO			0x00000800
#define CC_CMD_RESUME_VIDEO			0x00001000
#define CC_CMD_SET_ANTENNA			0x00002000
#define CC_CMD_SET_XPOND			0x00004000
#define CC_CMD_START_SI_MONITOR		0x00008000
#define CC_CMD_INFO_VPO_CHANCHNG	0x00100000
#define CC_CMD_STOP_MCAS_SERVICE	0x00200000
#define CC_CMD_CHANNEL_CHANGE		0x00400000


/********************************************/
/*          libpub flag bit patterns        */
/********************************************/
/* change channel related flag bit pattern */
#define LIBPUB_FLG_CC_PLAY_BIT			0x00000001
#define LIBPUB_FLG_CC_STOP_BIT			0x00000002
#define LIBPUB_FLG_CC_PAUSE_BIT			0x00000004
#define LIBPUB_FLG_CC_SWITCH_APID_BIT	0x00000008
#define LIBPUB_FLG_CC_SWITCH_ACH_BIT	0x00000010
#define LIBPUB_FLG_CC_LOGO_BIT			0x00000020

#define LIBPUB_CMD_DATA_SIZE				80

//! @struct libpub_cmd
//! @brief libpub������Ϣ��
struct libpub_cmd
{
    UINT16 cmd_type;
    UINT8 sync;
    UINT8 reserve;
    UINT32 cmd_bit;
    UINT32 para1;	
    UINT32 para2;
    UINT8 data1[LIBPUB_CMD_DATA_SIZE];
    UINT8 data2[LIBPUB_CMD_DATA_SIZE];
};

//! @struct pub_module_config
//! @brief libpubģ�����á�
struct pub_module_config
{
	BOOL dm_enable;
};


#ifdef __cplusplus
extern "C" {
#endif 

//! @typedef libpub_cmd_handler
//! @brief libpub��Ϣ��������
typedef void(*libpub_cmd_handler)(struct libpub_cmd *);

BOOL libpub_cmd_handler_register(UINT16 cmd_main_type, libpub_cmd_handler handler);
BOOL libpub_overlay_cmd_register(UINT16 repeat_cmd);

/*!
@brief libpub��ʼ����
@details ��ʼ��PUB(CC��AS)ģ�飬����PUB task��ע��CC��AS�Ĳ�̨����̨���������ͺʹ������ȡ���ϵͳ��ʼ����ʱ�������SDKģʽ����Ҫ���øú�����ʼ���м���PUB(CC&AS)ģ�顣�����DDKģʽ������Ҫʹ���м���PUBģ�顣
@param[in] config config
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
RET_CODE libpub_init(struct pub_module_config *config);

INT32 libpub_send_cmd(struct libpub_cmd* cmd,UINT32 tmout);
INT32 libpub_wait_cmd_finish(UINT32 cmd_bit,UINT32 tmout);
void libpub_declare_cmd_finish(UINT32 cmd_bit);

void  chchg_init(void);

/*!
@brief ���Ž�Ŀ��
@details �첽��ʽ����һ����Ŀ����������NIM��DMX��AV decoder�ȵȡ��ú�����CC task����һ����Ϣ���������в���ͨ����Ϣ����CC֮�����̷��ء�
@param[in] ft �ο�lib_frontend.h��struct ft_frontend�Ķ��壺<br>
struct ft_frontend
{
    struct nim_device *nim;
    struct ft_antenna antenna;
    union ft_xpond xpond;
    struct ft_ts_route ts_route;
};<br>
���У�Cableʹ�õ��Ĳ����У�<br>
	- nim��IN����������ǰ��NIM���豸�����һ��Cable��ֻ��1��NIM������ͨ��dev_get_by_id(HLD_DEV_TYPE_NIM, 0(nim_id))��ȡNIM�豸�ľ����
	- xpond��IN���ο�frontend_set_nim()�Ľ��ܡ�
@param[in] param ����ṹ����Ĵ�����������Ǻͽ�Ŀ���ݿ��P_NODE��Ӧ�ģ�������Щ����������Ҫת��һ�¡��������������ǲ��Ž�Ŀ��ʱ��Ŀ��Ʋ��������绻̨��ʱ�򣬱�������PVR¼�ƽ�Ŀ������ͣ��DMX�ȵȡ���ɫ���ֱ�ʾ�ж��壬����Cable�г��ò����Ĳ�����
@param[in] blk_scrn ��̨�Ƿ���ʾ������<br>
	- TRUE - ��ʾ����
	- FALSE - ����ʾ������������һ����Ŀ�����һ֡���档
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
@note chchg_play_channel
*/
INT32 chchg_play_channel(struct ft_frontend *ft, struct cc_param *param, BOOL blk_scrn);

/*!
@brief ֹͣ��Ŀ��
@details ֹͣ����һ����Ŀ�������ڽ�menu��ʱ����Ҫ��ȫֹͣ���Ž�Ŀ���ú�����һ��ͬ���Ľӿں�������CC task����ֹͣ���Ž�Ŀ����Ϣ֮�󣬻�ȵ�CC task�����������Ϣ������һ��flag֮�󣬲Ż᷵�ء�
@param[in] es �ο�chchg_play_channel()�Ľ��ܡ�
@param[in] dev_list �ο�chchg_play_channel()�Ľ��ܡ�
@param[in] blk_scrn ֹͣ����ʱ�Ƿ���ʾ������<br>
		TRUE - ��ʾ����
		FALSE - ����ʾ������������Ŀ�����һ֡���档
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_stop_channel(struct cc_es_info *es, struct cc_device_list *dev_list, BOOL blk_scrn);

/*!
@brief ��ͣ��Ŀ��
@details ��ͣ���Ž�Ŀ��Video������ͣ������Audio��Ȼ���ڲ��ź������
@param[in] vdec Video decoder��������ڲ��ŵĽ�Ŀʹ�õ�Video decoder��������DECV0��DECV1��AVC Video DEC�ȡ�
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_pause_video(struct vdec_device *vdec);

/*!
@brief �ָ���Ŀ��
@details �ָ�����Video���档����ֱ����Ŀ��˵����Ȼ��ͣ�˲��Ž�Ŀ����ʵʱ��Ŀ������Ȼ�ڷ��ͣ������ڻָ����ŵ�ʱ��ʵ���Ѿ��ǵ�ʱ��ʵʱ�Ļ����ˣ��������Ǵ���ͣ��������ŵĻ��档
@param[in] vdec Video decoder��������ڲ��ŵĽ�Ŀʹ�õ�Video decoder��������DECV0��DECV1��AVC Video DEC�ȡ�
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_resume_video(struct vdec_device *vdec);

/*!
@brief �л�Audio������
@details �л���ǰ��Ŀ���ŵ�Audio������һ�����һ����Ŀ�ж�������Ļ����ͻ��ж��Audio ES�����û�����ѡ���л���ͬ���Ե��������ײ�ֻ��Ҫ����DMX��Audio Channel��������Audio DEC���ɣ�����Video/VPO�ȵȶ�����Ҫ������
@param[in] es �ο�chchg_play_channel()�Ľ��ܡ�
@param[in] dev_list �ο�chchg_play_channel()�Ľ��ܡ�<br>
    ���������������л�Audio������ʱ��ʵ��ֻ�õõ�Audio DEC��Sound��DMX�豸��Audio��PID��type��channel��volume�ȵȣ�����Video DEC�ȵ��ǲ���Ҫ�ġ�
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_switch_audio_pid(struct cc_es_info *es, struct cc_device_list *dev_list);

/*!
@brief �л�Audio����������
@details �л���Ƶ������������
@param[in] snd Sound�豸��������԰����´����ȡ��<br>
struct snd_device *snd = dev_get_by_id(HLD_DEV_TYPE_SND, 0)��
@param[in] audio_chan ����ȡdb_node.h���������4��ֵ��<br>
	- #define AUDIO_CH_L			0x00
	- #define AUDIO_CH_R			0x01
	- #define AUDIO_CH_STEREO		0x02
	- #define AUDIO_CH_MONO			0x03
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_switch_audio_chan(struct snd_device *snd, UINT8 audio_chan);

/*!
@brief ��ʾLogo��
@details ͨ��Videc DEC��ʾһ��MPEG I֡��LogoͼƬ���ú���Ҳ��һ��ͬ����ʾlogo�ĺ���������ȵ�CC�յ���Ϣ��������ʾlogo�ɹ�֮��Ż᷵�ء�
@param[in] plogo logo�ĵ�ַ�ʹ�С������struct cc_logo_info��lib_frondend.h�����¶��壺<br>
struct cc_logo_info
{
    UINT8 *addr;
    UINT32 size;
};<br>
��Ҫע�����Logo�����ݱ�����load��memory���ٵ��øú�������ʾlogo��CCģ�鲻���flash�϶�ȡlogo�����ݡ�
@param[in] dev_list �ο�chchg_play_channel()�Ľ��ܡ�Show Logo��ʱ����õ�Video DEC��Audio DEC��DMX��VPO���豸��
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX	ʧ��
*/
INT32 chchg_show_logo(struct cc_logo_info *plogo, struct cc_device_list *dev_list);

typedef INT32 (*amscc_play_event)(UINT32 event, struct ft_frontend *ft, struct cc_param *param);
void amscc_reg_callback(amscc_play_event handle);

//to be deleted
#define DM_NIMCHECK_ON	6	
#define dm_set_onoff(a) do{PRINTF("DM (%d):________ <%s>\n", a, __FUNCTION__);}while(0)
 
#ifdef __cplusplus
}
#endif 

/*!
 * @}
 */

/*!
@}
*/

#endif


