#ifndef __ADF_AVSYNC__
#define __ADF_AVSYNC__

#include "adf_basic.h"
#include "adf_media.h"


/*! @addtogroup avsync
 *  @{
*/

#ifdef __cplusplus
extern "C" {
#endif

#define AVSYNC_IO_ENABLE_DDP_CERTIFICATION 0x01  //!< ʹ�� DDP ��֤
#define AVSYNC_IO_GET_VIDEO_SMOOTHLY_PLAY_CFG   0x02//!< ����video ƽ������
#define AVSYNC_IO_ENABLE_GET_STC 0x03	//!< ����MAIN CPU ��ȡstc
#define AVSYNC_IO_SET_PTS_UNIT_HZ   0x04 //!< ����PTS   ��λ
#define AVSYNC_IO_UNREG_CALLBACK   0x05	//!< ���� callback
#define AVSYNC_IO_REG_CALLBACK   0x06//!< ע�� callback
#define AVSYNC_IO_GET_CURRENT_PLAY_PTS   0x07	//!<��ȡ��ǰ�� PTS
#define AVSYNC_IO_PAUSE   0x08	//!<��ͣ avsync  ģ��
#define AVSYNC_IO_RESUME   0x09	//!<�ָ� avsync ģ��

/*! @enum LLD_AVSYNC_FUNC
@brief  ����remote call ����
*/
enum LLD_AVSYNC_FUNC{
    FUNC_AVSYNC_ATTACH = 0,
};

 
 /*! @enum HLD_AVSYNC_FUNC
 @brief  ����remote call ����
 */
enum HLD_AVSYNC_FUNC{
    FUNC_AVSYNC_OPEN = 0,   
    FUNC_AVSYNC_CLOSE,
    FUNC_AVSYNC_START,   
    FUNC_AVSYNC_STOP,
    FUNC_AVSYNC_RESET,
    FUNC_AVSYNC_IOCTL,
    FUNC_AVSYNC_SET_SYNCMODE,
    FUNC_AVSYNC_GET_SYNCMODE,
    FUNC_AVSYNC_CFG_PARAMS,
    FUNC_AVSYNC_GET_PARAMS,
    FUNC_AVSYNC_CFG_ADV_PARAMS,
    FUNC_AVSYNC_GET_ADV_PARAMS,
    FUNC_AVSYNC_SET_SRCTYPE,
    FUNC_AVSYNC_GET_SRCTYPE,
    FUNC_AVSYNC_GET_STATUS,
    FUNC_AVSYNC_GET_STATISTICS,
    FUNC_AVSYNC_VIDEO_SMOOTHLY_PLAY_ONOFF,
    FUNC_AVSYNC_DBG_SET_PRINT_OPTION,
    FUNC_AVSYNC_DBG_SET_POLL_ONOFF,
    FUNC_AVSYNC_DBG_SET_POLL_OPTION,
    FUNC_AVSYNC_DBG_SET_POLL_INTERVAL,
};

/*! @struct avsync_get_stc_en_t
@brief Main cpu��ȡSTCʱ��ʹ��
*/

typedef struct 
{
	void *sharem_addr;
	UINT8 enable;
}avsync_get_stc_en_t;

/*! @enum AVSYNC_PTS_MODE
@brief ��ǰPTS �Ƿ���Ч
*/
typedef enum  
{
	AVSYNC_PTS_MODE_FREE, //no PTS 
	AVSYNC_PTS_MODE_CNT,//not used
	AVSYNC_PTS_MODE_VALID,// valid pts
	AVSYNC_PTS_MODE_INVALID,	//non valid pts
}AVSYNC_PTS_MODE;


/*! @enum AVSYNC_FRAME_SYNCFLAG_E
@brief ��ǰͬ����־
*/
typedef enum 
{
	AVSYNC_FRAME_PLAY,	 //play Audio/Video frame
	AVSYNC_FRAME_DROP,  // drop Audio/Video frame
	AVSYNC_FRAME_HOLD, // hold Audio by SW
	AVSYNC_FRAME_FREERUN, // free run frame
	AVSYNC_FRAME_HW_HOLD, //hold Audio frame by HW
}AVSYNC_FRAME_SYNCFLAG_E;

/*! @enum AVSYNC_MODE_E
@brief ����Ƶͬ��ģʽ, AVSYNCģ��Ĭ������ΪAVSYNC_MODE_PCR��AVSYNC_MODE_VIDEO�ݲ�֧��
*/
typedef enum 
{
	AVSYNC_MODE_PCR,       //!<��PCRΪ��׼
	AVSYNC_MODE_AUDIO,     //!<����ƵΪ��׼
	AVSYNC_MODE_VIDEO,     //!<����ƵΪ��׼, �ݲ�֧��
	AVSYNC_MODE_V_FREERUN, //!<��Ƶ����ͬ��,ֱ�Ӳ���
	AVSYNC_MODE_A_FREERUN, //!<��Ƶ����ͬ��,ֱ�Ӳ���
	AVSYNC_MODE_AV_FREERUN, //!<����Ƶ����ͬ��,ֱ�Ӳ���
}AVSYNC_MODE_E;

/*! @ enum AVSYNC_SRCTYPE_E
@brief ����Ƶ����Դ���ͣ�AVSYNCģ��Ĭ������ΪAVSYNC_SRC_TURNER
*/
typedef enum 
{
	AVSYNC_SRC_TURNER, //!<��������turner
	AVSYNC_SRC_SWDMX, //!<��������SW DMX
	AVSYNC_SRC_HDD_MP, //!<�������Ա���ý�岥��
	AVSYNC_SRC_NETWORK_MP, //!<������������ý�岥��
}AVSYNC_SRCTYPE_E;
typedef enum 
{
	AVSYNC_H264, // decoder is h.264
	AVSYNC_MPEG2, //decoder is MPEG2
	AVSYNC_MPEG4,  //decoder is MPEG4
	AVSYNC_AVS,  //decoder is AVS
}AVSYNC_CODEC_TYPE;

/*! @ enum AVSYNC_DEVICE_STATUS
@brief AVSYNC�豸״̬
*/
typedef enum 
{
	AVSYNC_ATTACHED, //!<�豸�ѹҽ�
	AVSYNC_OPENED,    //!<�豸�Ѵ�
	AVSYNC_CLOSED,    //!<�豸�ѹر�
	AVSYNC_STARTED,  //!<�豸�ѿ�ʼ����
	AVSYNC_STOPPED,	//!<�豸��ֹͣ����	
}AVSYNC_DEV_STATUS;

/*! @ enum AVSYNC_VIDEO_SMOOTH_LEVEL
@brief ��Ƶƽ�����ŵȼ�
*/
typedef enum 
{
	AVSYNC_VIDEO_SMOOTH_LEVEL1, 
	AVSYNC_VIDEO_SMOOTH_LEVEL2, 
}AVSYNC_VIDEO_SMOOTH_LEVEL;

/*! @ struct avsync_cfg_param_t
@brief ����ͬ��������AVSYNCģ��Ĭ�����òο�����������
*/
typedef struct
{
	UINT32 vhold_thres; //!<��Ƶ�ظ����ޣ�Ĭ��ֵΪ80ms
	UINT32 vdrop_thres; //!<��Ƶ�������ޣ�Ĭ��ֵΪ80ms
	UINT32 ahold_thres; //!<��Ƶ�ظ����ޣ�Ĭ��ֵΪ40ms
	UINT32 adrop_thres; //!<��Ƶ�������ޣ�Ĭ��ֵΪ64ms
	AVSYNC_MODE_E sync_mode; //!<����Ƶͬ��ģʽ��Ĭ��ֵΪAVSYNC_MODE_PCR
	AVSYNC_SRCTYPE_E src_type; //!<����Ƶ����Դ���ͣ�Ĭ��ֵΪAVSYNC_SRC_TURNER
}avsync_cfg_param_t;

/*! @ struct avsync_adv_param_t
@brief �߼�ͬ��������AVSYNCģ��Ĭ�����òο�����������
*/
typedef struct
{
	UINT32 afreerun_thres; //!<��Ƶfree run ���ޣ�Ĭ��ֵΪ10s
	UINT32 vfreerun_thres; //!< ��Ƶfree run ���ޣ�Ĭ��ֵΪ10s
	UINT8  disable_monitor; //!< �ر�monitor ���ܱ�־,��Ĭ��ֵΪ1
	UINT8 disable_first_video_freerun; //!<������Ƶ��һ֡free run���ܱ�־��Ĭ��ֵΪ0
	UINT16  dual_output_sd_delay; //!< ��Ƶ˫�����������ӳ�
	UINT32  pts_adjust_threshold;
	UINT32 rsvd2; 
	UINT32 rsvd3;
}avsync_adv_param_t;


/*! @ struct avsync_vsync_info_t
@brief  video ��ͬ����Ϣ�ṹ������
*/
struct avsync_vsync_info_t
{
	UINT32 vpts;                                   // pts of video frame 
	AVSYNC_PTS_MODE	vpts_mode;    // pts mode of video frame
	UINT32 display_dly;                       // display delay from request avsync flag to real display
	UINT32 remain_esbuf_size;           // remained vbv buffer size
	UINT32 esbuf_size;                         // vbv buffer size
	UINT32 frame_duration;                 // video frame duration
	UINT32 bitrate;                               // video bit rate
	UINT8   stc_id;					//stc id used
	UINT8   bstream_run_back;          //stream run back flag
	UINT8   stc_offset_idx;			//stc offset index used
	UINT8   decode_error;			//decode error flag
	AVSYNC_CODEC_TYPE   CODEC_type;	//video codec used
	BOOL pause_state;				// in pause state
};

 /*! @ struct avsync_vsync_info_t
@brief  audio ��ͬ����Ϣ�ṹ������
*/
struct  avsync_async_info_t
{
	UINT32 cur_apts;                           //pts of audio frame
	UINT32 next_apts;                         //next valid audio pts
	UINT32 frm_num_two_pts;            //frame number between_two_pts
	UINT32 remain_esbuf_size;          // remained audio es buffer size
	UINT32 esbuf_size;                       // audio es buffer size
	UINT32 remain_pcm_time;          // play time in pcm buffer
	UINT32 frame_duration;             // audio frame duration
	UINT32 bitrate;                            // video bit rate
	UINT8   stc_id;				//stc id used
	UINT8   bstream_run_back;//stream run back flag
	UINT8   pts_valid;			//pts valid flag
	UINT8   stc_offset_idx;		//stc offset index used
	UINT32 total_remain_pcm_time;	//pcm time remain in buffer
};


/*! @ struct avsync_status_t
@brief ģ��״̬
*/
typedef struct 
{
	AVSYNC_DEV_STATUS device_status; //!<�豸״̬
	UINT32 vpts_offset; //!<��ƵPTSƫ��
	UINT32 apts_offset; //!<��ƵPTSƫ��	
	UINT8 v_sync_flg; //!<��Ƶͬ����־
	UINT8 a_sync_flg; //!<��Ƶͬ����־
	UINT8 rsvd0; //!<Ԥ��
	UINT8 rsvd1; //!<Ԥ��

	UINT32 cur_vpts;//!< ��ǰ��ƵPTS
	UINT32 cur_apts;//!< ��ǰ��ƵPTS	
}avsync_status_t;

/*! @ struct AVSYNC_SRCTYPE_E
@brief ͬ��ͳ����Ϣ
*/
typedef struct 
{
	UINT32 total_v_play_cnt; //!<ͬ����Ƶ֡��
	UINT32 total_v_drop_cnt; //!<������Ƶ֡��
	UINT32 total_v_hold_cnt; // !<�ظ���Ƶ֡��
	UINT32 total_v_freerun_cnt; // !<free-run ��Ƶ֡��
	UINT32 total_a_play_cnt; //!<ͬ����Ƶ֡��
	UINT32 total_a_drop_cnt; //!<��Ƶ����֡��
	UINT32 total_a_hold_cnt; // !<��Ƶ�ظ�֡��
	UINT32 total_a_freerun_cnt;
}avsync_statistics_t;

/*! @ struct avsync_video_cb_t
@brief  ע��� video  driver�� callback����
*/
struct avsync_video_cb_t
{
	void *get_vync_flg_cb; //��ȡvideoͬ����־
	void *vbv_full_cb;// video buffer ���¼�֪ͨ 
	void *avsync_start;// ��������avsync driver
	void *avsync_stop;// ����ֹͣ avsync driver
};

/*! @ struct avsync_video_cb_t
@brief  ע��� audio  driver�� callback����
*/

struct avsync_audio_cb_t
{
	void *get_async_flg_cb; // ��ȡaudio ͬ����־
};

/*! @ struct avsync_smoothly_play_cfg_t
@brief  ��������video��ƽ������
*/

struct  avsync_smoothly_play_cfg_t
{
	UINT8 onoff;		// 1�򿪣�0�ر�
	UINT8 interval;	//���ʱ��
	AVSYNC_VIDEO_SMOOTH_LEVEL level;//���� 
};

#define AVSYNC_CB_MAX_DEV_NUM 4 //avsync�豸������

/*! @ struct avsync_cb
@brief  �豸ָ������
*/

struct avsync_cb
{
	void *dmx[AVSYNC_CB_MAX_DEV_NUM];//���AVSYNC_CB_MAX_DEV_NUM��dmx�豸ָ��
	void *decv[AVSYNC_CB_MAX_DEV_NUM];//���AVSYNC_CB_MAX_DEV_NUM��decv�豸ָ��
	void *deca[AVSYNC_CB_MAX_DEV_NUM];//���AVSYNC_CB_MAX_DEV_NUM��deca�豸ָ��
	void *snd[AVSYNC_CB_MAX_DEV_NUM];//���AVSYNC_CB_MAX_DEV_NUM��snd �豸ָ��
};

/*! @struct avsync_device
@brief �豸���Ͷ���, �����˳�Ա�����Լ��ṩ�Ĳ����ӿڡ�
*/
struct avsync_device
{
	struct avsync_device  *next;  /*next device */
	/*struct module *owner;*/
	INT32 type;
	INT8 name[32];
	INT32 flags;

	void *priv;		/* Used to be 'private' but that upsets C++ */
	void      (*attach)(void *);
	void      (*detach)(struct avsync_device **);
	RET_CODE	(*open)(struct avsync_device *);
	RET_CODE   	(*close)(struct avsync_device *);
	RET_CODE	(*start)(struct avsync_device *);
	RET_CODE   	(*stop)(struct avsync_device *);
	RET_CODE   	(*ioctl)(struct avsync_device *, UINT32 , UINT32);	
	RET_CODE     (*reset)(struct avsync_device*);
	RET_CODE     (*set_syncmode)(struct avsync_device*, AVSYNC_MODE_E);
	RET_CODE     (*get_syncmode)(struct avsync_device*, AVSYNC_MODE_E *);
	RET_CODE     (*set_sourcetype)(struct avsync_device*, AVSYNC_SRCTYPE_E);
	RET_CODE     (*get_sourcetype)(struct avsync_device*, AVSYNC_SRCTYPE_E *);
	RET_CODE     (*config_params)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*get_params)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*config_adv_params)(struct avsync_device*, avsync_adv_param_t *);
	RET_CODE     (*get_adv_params)(struct avsync_device*, avsync_adv_param_t *);
	RET_CODE     (*get_status)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*get_statistics)(struct avsync_device*, avsync_cfg_param_t *);
	RET_CODE     (*video_smoothly_play_onoff)(struct avsync_device *, UINT8, AVSYNC_VIDEO_SMOOTH_LEVEL, UINT8);
	RET_CODE		(*dbg_set_print_option)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_poll_onoff)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_set_poll_option)(struct avsync_device *, UINT32);
	RET_CODE		(*dbg_set_poll_interval)(struct avsync_device *, UINT32);
};

typedef RET_CODE (*AVSYNC_GET_VIDEO_CTRLLK_CB)(struct avsync_device *, UINT32 , struct control_block *);
typedef RET_CODE (*AVSYNC_APTS_EXTRACT_CB)(struct avsync_device *, UINT32 , struct control_block *);
typedef RET_CODE (*AVSYNC_PROCESS_PCR_CB)(struct avsync_device *, UINT32);


/*! @ struct avsync_dmx_cb
@brief  ��dmxע���callback����
*/
struct avsync_dmx_cb
{
    void *avsync_dev;		// avsync �豸ָ��
	AVSYNC_GET_VIDEO_CTRLLK_CB pvpts_cb; // video control block callback ����
	AVSYNC_APTS_EXTRACT_CB papts_cb;//audio control block callback  ����
	AVSYNC_PROCESS_PCR_CB ppcr_cb; //pcr callback����
};

typedef RET_CODE (*AVSYNC_GET_VSYNC_FLAG)(void *dev, struct avsync_vsync_info_t *, AVSYNC_FRAME_SYNCFLAG_E *, BOOL *);
typedef RET_CODE (*AVSYNC_VBV_BUFF_FULL)(void *dev);
typedef RET_CODE (*AVSYNC_START_CB)(void *dev);
typedef RET_CODE (*AVSYNC_STOP_CB)(void *dev);
typedef RET_CODE (*AVSYNC_GET_ASYNC_FLAG)(void *dev, struct avsync_async_info_t *, AVSYNC_FRAME_SYNCFLAG_E *);
typedef RET_CODE(*AVSYNC_GET_PAUSE_FLAG)(void*dev, UINT32 *, UINT32 *);


/*! @ struct avsync_callback
@brief  avsyncģ���callbck����
*/

struct avsync_callback
{
	struct avsync_device *pavsync_dev; // avsync �豸ָ��?
	AVSYNC_GET_VSYNC_FLAG pget_vync_flg_cb; // video ͬ��callback����
	AVSYNC_VBV_BUFF_FULL pvbv_full_cb;//video buffer ���  callback ����?
	AVSYNC_START_CB pavsync_start;  // ���� avsync callback ����
	AVSYNC_STOP_CB pavsync_stop;	// ֹͣ avsync callback  ����
	AVSYNC_GET_ASYNC_FLAG pget_async_flg_cb;	// audio ͬ��callback����
	AVSYNC_GET_PAUSE_FLAG pget_avsync_pause_flag;// audio ��ͣcallback����
};

/*!
@brief ע���豸avsync��������Դ�ȡ�
@note: ��������AVSYNCģ��ӿں���ǰ�����ȵ��øú�����
*/
RET_CODE avsync_attach(void);

/*!
@brief �Ƴ��豸avsync,������Դ�ȡ�
@param[in] dev ָ���豸avsync��ָ�롣
*/
void avsync_dettach(struct avsync_device*dev);

/*!
@brief ��avsyncģ�顣
@param[in] dev ָ��avsyncģ���ָ�롣
@return RET_CODE��
@retval  RET_SUCCESS       �򿪳ɹ���
@retval  !RET_SUCCESS     ��ʧ�ܣ����������״̬����
*/
RET_CODE avsync_open(struct avsync_device *dev);

/*!
@brief �ر�avsyncģ�顣
@param[in] dev ָ��avsyncģ���ָ�롣
@return RET_CODE��
@retval  RET_SUCCESS       �رճɹ���
@retval  !RET_SUCCESS     �ر�ʧ�ܣ����������״̬����
*/
RET_CODE avsync_close(struct avsync_device *dev);
/*!
@brief ����avsyncģ�顣
@param[in] dev ָ��avsyncģ���ָ�롣
@return RET_CODE��
@retval  RET_SUCCESS       �����ɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
*/

RET_CODE avsync_start(struct avsync_device *dev);

/*!
@brief ֹͣavsyncģ�顣
@param[in] dev ָ��avsyncģ���ָ�롣
@return RET_CODE��
@retval  RET_SUCCESS       ֹͣ�ɹ���
@retval  !RET_SUCCESS    ֹͣʧ�ܣ����������״̬����
*/

RET_CODE avsync_stop(struct avsync_device *dev);

/*!
@brief �豸avsync�ṩ��ioctl�����ӿڡ� 
@param[in] dev ָ���豸avsync ��ָ�롣
@param[in] io_code ��������
@param[in] param ���������
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
*/
RET_CODE avsync_ioctl(struct avsync_device *dev, UINT32 io_code, UINT32 param);

/*!
@brief ��λͬ��ģ��, ����ͬ�� 
@param[in] dev ָ���豸avsync��ָ�롣
@return RET_CODE��
@retval  RET_SUCCESS       ��λ�ɹ���
@retval  !RET_SUCCESS     ��λʧ�ܣ����������״̬����
*/RET_CODE avsync_reset(struct avsync_device *dev);

/*!
@brief ����ͬ��ģʽ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[in] mode ͬ��ģʽ��ͬ��ģʽ�ο�AVSYNC_MODE_E���塣
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
@note: ��Ӧ�ò㲻���øýӿڣ�AVSYNCģ���ڲ�ʹ��Ĭ�����ã����AVSYNC_MODE_E����
*/
RET_CODE avsync_set_syncmode(struct avsync_device *dev, AVSYNC_MODE_E mode);

/*!
@brief ��ȡͬ��ģʽ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] pmode ��ȡ����ͬ��ģʽ��
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_syncmode(struct avsync_device *dev, AVSYNC_MODE_E *pmode);

/*!
@brief ��������Դ����,��ͬ������Դ����ͬ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[in] type ����Դ����,�ο�AVSYNC_SRCTYPE_E���塣
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
@note: ��Ӧ�ò㲻���øýӿڣ�AVSYNCģ���ڲ�ʹ��Ĭ�����ã����AVSYNC_SRCTYPE_E����
*/
RET_CODE avsync_set_sourcetype(struct avsync_device *dev, AVSYNC_SRCTYPE_E type);

/*!
@brief ��ȡ����Դ���� 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] ptype ��ȡ��������Դ���͡�
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_sourcetype(struct avsync_device *dev, AVSYNC_SRCTYPE_E *ptype);

/*!
@brief ���û���ͬ������ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[in] pcfg_params ����ͬ���������á�
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
@note: ��Ӧ�ò㲻���øýӿڣ�AVSYNCģ���ڲ�ʹ��Ĭ�����ã����avsync_cfg_param_t����
*/
RET_CODE avsync_config_params(struct avsync_device *dev,  avsync_cfg_param_t *pcfg_params);

/*!
@brief ��ȡ����ͬ������ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] pcfg_params ��ȡ����ͬ��������
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_params(struct avsync_device *dev,  avsync_cfg_param_t *pcfg_params);

/*!
@brief ���ø߼�ͬ������ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[in] pcfg_params �߼�ͬ���������á�
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
@note: ��Ӧ�ò㲻���øýӿڣ�AVSYNCģ���ڲ�ʹ��Ĭ�����ã����avsync_adv_param_t����
*/
RET_CODE avsync_config_advance_params(struct avsync_device *dev,  avsync_adv_param_t *pcfg_params);

/*!
@brief ��ȡ�߼�ͬ������ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] pcfg_params ��ȡ�߼�ͬ��������
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_advance_params(struct avsync_device *dev,  avsync_adv_param_t *pcfg_params);

/*!
@brief ��ȡģ��״̬ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] pstatus ��ȡ����ģ��״̬��
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_status(struct avsync_device *dev, avsync_status_t *pstatus);

/*!
@brief ��ȡͬ��ͳ����Ϣ 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] pstatistics ��ȡ����ͬ��ͳ����Ϣ��
@return RET_CODE��
@retval  RET_SUCCESS       ��ȡ�ɹ���
@retval  !RET_SUCCESS     ��ȡʧ�ܣ����������״̬����
*/
RET_CODE avsync_get_statistics(struct avsync_device *dev, avsync_statistics_t *pstatistics);

/*!
@brief ����/�ر���Ƶƽ�����Ź��� 
@param[in] dev ָ���豸avsync��ָ�롣
@param[in] onoff ����/�ر�ƽ�����Ź���
@param[in] level ƽ�����ŵȼ�
@param[in] interval ƽ�����ż��(��λΪ֡��)
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܣ����������״̬����
*/
RET_CODE avsync_video_smoothly_play_onoff(struct avsync_device *dev, UINT8 onoff, AVSYNC_VIDEO_SMOOTH_LEVEL level, UINT8 interval);

/*==========================================
 *  AVSYNC Debug Start
 *==========================================*/
 
//ʵʱ��ӡѡ�� 
#define AVSYNC_DBG_PRINT_DEFAULT 1 //!<��ӡSTC����������Ƶ��ͬ����Ϣ
#define AVSYNC_DBG_PRINT_PCR	2  //!<��ӡPCR��PCR���
#define AVSYNC_DBG_PRINT_APTS	4  //!<��ӡ��ƵPTS��PTS���
#define AVSYNC_DBG_PRINT_VPTS 8  //!<��ӡ��ƵPTS��PTS���
#define AVSYNC_DBG_PRINT_A_SYNC 0x10 //!<��ӡ��Ƶ֡ͬ��ʱPTS/STCֵ
#define AVSYNC_DBG_PRINT_A_UNSYNC_PTS_STC 0x20 //!<��ӡ��Ƶ֡��ͬ��ʱPTS/STCֵ
#define AVSYNC_DBG_PRINT_A_UNSYNC_STCID_OFFSET 0x40 //!<��ӡ��Ƶ֡��ͬ��ʱSTCƫ��
#define AVSYNC_DBG_PRINT_A_UNSYNC_ESBUF 0x80 //!<��ӡ��Ƶ֡��ͬ��ʱ����ES buffer����
#define AVSYNC_DBG_PRINT_V_SYNC 0x100 //!<��ӡ��Ƶ֡ͬ��ʱPTS/STCֵ
#define AVSYNC_DBG_PRINT_V_UNSYNC_PTS_STC 0x200 //!<��ӡ��Ƶ֡��ͬ��ʱPTS/STCֵ
#define AVSYNC_DBG_PRINT_V_UNSYNC_STCID_OFFSET 0x400 //!<��ӡ��Ƶ֡��ͬ��ʱSTCƫ��
#define AVSYNC_DBG_PRINT_V_UNSYNC_VBVBUF 0x800 //!<��ӡ��Ƶ֡��ͬ��ʱ����VBV buffer����
#define AVSYNC_DBG_PRINT_PTS_OFFSET  0x1000    //!<��ӡPTSƫ�Ƶ�����Ϣ
#define AVSYNC_DBG_PRINT_STREAM_LOOP 0x2000    //!<��⵽����ͷʱ��ӡ

#define AVSYNC_DBG_PRINT_VESBUF_OF_UR 0x4000   //!<��ӡ��ƵES buffer�ջ���
#define AVSYNC_DBG_PRINT_AESBUF_OF_UR 0x8000   //!<��ӡ��ƵES buffer�ջ���

#define AVSYNC_DBG_FORCE_SYNCMODE_FREERUN 0x10000   //!<ͬ��ģʽǿ�Ƴ�AVSYNC_MODE_AV_FREERUN
#define AVSYNC_DBG_FORCE_SYNCMODE_PCR 0x20000   //!<ͬ��ģʽǿ�Ƴ�AVSYNC_MODE_AV_PCR
#define AVSYNC_DBG_FORCE_SYNCMODE_AUDIO 0x40000   //!<ͬ��ģʽǿ�Ƴ�AVSYNC_MODE_AUDIO
#define AVSYNC_DBG_FORCE_SYNCMODE_INVALID 0x80000   //!<����ͬ��ģʽ��Ч

#define AVSYNC_DBG_PRINT_API	0x10000000     //!<��ӡAPI����
#define AVSYNC_DBG_PRINT_LOG	0x20000000	//!<LOG  ��ӡ
#define AVSYNC_DBG_PRINT_ERR	0x40000000     //!<��ӡģ�������Ϣ

//��ѯ����ѡ��
#define AVSYNC_DBG_POLL_V_SYNC_STATISTICS  0x01	 //!<��video ͳ����Ϣ
#define AVSYNC_DBG_POLL_A_SYNC_STATISTICS  0x02  //!<��audio ͳ����Ϣ
#define AVSYNC_DBG_POLL_PCR_STATISTICS  0x04//!<��pcrͳ����Ϣ
#define AVSYNC_DBG_POLL_VBV_FULL_CNT  0x08 //!<video buffer �������
#define AVSYNC_DBG_POLL_PTS_OFFSET  0x10	//!<pts offsetͳ����Ϣ
#define AVSYNC_DBG_POLL_SYNC_MODE 0x20	//!<ͬ��ģʽ��Ϣ


/*!
@brief ����ʵʱ���Դ�ӡѡ�� 
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] option ��ӡѡ�
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܡ�
*/
RET_CODE avsync_dbg_set_print_option(struct avsync_device *dev, UINT32 option);

/*!
@brief ����/�ر���ѯ����
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] on_off ����/�ر���ѯ���ԡ�
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܡ�
*/
RET_CODE avsync_dbg_polling_onoff(struct avsync_device *dev, UINT32 on_off);

/*!
@brief ������ѯ����ѡ��
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] option ��ѯ����ѡ�
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܡ�
*/
RET_CODE avsync_dbg_set_polling_option(struct avsync_device *dev, UINT32 option);

/*!
@brief ������ѯ���Դ�ӡ���
@param[in] dev ָ���豸avsync��ָ�롣
@param[out] interval_ms ��ѯ��ӡ�������λΪ����
@return RET_CODE��
@retval  RET_SUCCESS       ���óɹ���
@retval  !RET_SUCCESS     ����ʧ�ܡ�
*/
RET_CODE avsync_dbg_set_polling_interval(struct avsync_device *dev, UINT32 interval_ms);


#ifdef __cplusplus
}
#endif

/*!
@}
*/

#endif


