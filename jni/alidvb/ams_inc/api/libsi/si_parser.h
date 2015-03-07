/**********************************************************************
*    Copyright (C)2011 Ali Corporation. All Rights Reserved.
*
*    File:    si_parser.h
*
*    Description:    Header file in XXX.
*    History:
*       Date            Athor        Version          Reason
*    ============   =============   =========    =================
*     1. Oct.30.2011   Guoping.Chen	Ver 0.1			Creat file
*     2. Dec.05.2011   Linge.Chen        Ver 0.2                  Review file
************************************************************************/


#ifndef __SI_PARSER_H_
#define __SI_PARSER_H_

#include <api/libtsi/si_descriptor.h>


/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSSIP
 *  @{
 */

//#define SI_PARSER_DEBUG

//! @enum amssip_front_type_e
//! @brief ����tsǰ�����͡�DVB-Cʹ��AMSSIP_CABLE���͡�
typedef enum
{
	AMSSIP_CABLE			= 0,
	AMSSIP_SATTLITE			= 1,
	AMSSIP_TERRITIAL		= 2,
}amssip_front_type_e;

//! @enum amspmt_es_type_e
//! @brief ����PMT���е�es���͡�
typedef enum 
{
	MPEG1_VIDEO_STREAM				= 0x01,
	MPEG2_VIDEO_STREAM				= 0x02,
	MPEG1_AUDIO_STREAM				= 0x03,
	MPEG2_AUDIO_STREAM				= 0x04,
	PRIVATE_DATA_STREAM				= 0x06,

	ISO13818_6_TYPE_A				= 0x0a,
	ISO13818_6_TYPE_B				= 0x0b,
	ISO13818_6_TYPE_C				= 0x0c,
	ISO13818_6_TYPE_D				= 0x0d,

    MPEG_ADTS_AAC_STREAM            = 0x0F,//!< ADTS_AAC
	MPEG4_VIDEO_STREAM				= 0x10, //!< (ISO/IEC 14496-2 Visual)
	MPEG_AAC_STREAM					= 0x11, //!< (ISO/IEC 14496-3 Audio withe LATM transport syntax)
	H264_VIDEO_STREAM				= 0x1b, //!< (AVC video as define in ITU Rec. H.264 |ISO/IEC 14496-10 Video)
	DC_II_VIDEO_STREAM				= 0x80,
	AC3_AUDIO_STREAM				= 0X81,

	AVS_VIDEO_STREAM				= 0x42, //AVS Video
	AVS_AUDIO_STREAM				= 0x43, //AVS Audio	

	//for private stream
	PRIVATE_EAC3_AUDIO				= (PRIVATE_DATA_STREAM<<8)|ENHANCED_AC3_DESCRIPTOR,	//!< 0x0106,
	PRIVATE_AC3_AUDIO				= (PRIVATE_DATA_STREAM<<8)|AC3_DESCRIPTOR,	//!< 0x8106,
}amspmt_es_type_e;

//type define for descripter parser function
typedef INT32 (*amssip_descripter_t)(UINT8 tag, UINT8 len, UINT8* buf, UINT32 param1, UINT32 param2);

//! @struct sip_descripter_vector_t
//! @brief ����˽����������ؽṹ��
typedef struct
{
	UINT8 tag;		        //!< descripter tag
	UINT32 bit;
	amssip_descripter_t func;	//!< ����˽�������������������͡�
	UINT8 loop;
	UINT8* buffer;
	UINT32 buf_size;
}sip_descripter_vector_t;

//! @struct amssip_pat_info_t
//! @brief ����PAT����Ϣ�洢�ṹ��
typedef struct
{
	UINT16 ts_id;
	UINT16 nit_pid;
	UINT32 prog_count;
	UINT16 prog_number[AMSSIP_TP_MAX_PROG_NUM];
	UINT16 pmt_pid[AMSSIP_TP_MAX_PROG_NUM];
	UINT8  version_number;
	UINT8  last_sec_numb;
}amssip_pat_info_t;

//! @struct amssip_cat_info_t
//! @brief ����CAT����Ϣ�洢�ṹ��
typedef struct
{
	UINT8 emm_count;
	UINT16 ca_sysid [AMSSIP_CAT_EMM_MAX_CNT];
	UINT16 emm_pid [AMSSIP_CAT_EMM_MAX_CNT];
	UINT8  version_number;
	UINT8  last_sec_numb;
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_cat_info_t;

//! @struct amssip_ca_info_t
//! @brief ����PMT����Ϣ�洢�ṹ��ֻ����һ���ӱ����Ϣ�����У�ca_pidΪecm pid��
typedef struct
{
	UINT16 ca_system_id;  //!< CA system id
	UINT16 ca_pid;        //!< ECM PID
}amssip_ca_info_t;

//! @struct amssip_pmt_info_t
//! @brief store PMT parser
typedef struct
{
	UINT16	prog_number; //!< ��Ŀprogram number
	UINT8	audio_count; //!< ��Ŀ��������Ƶ������
	UINT16  audio_pid[AMSSIP_PMT_MAX_AUDIO_NUM]; //!< ��Ŀ��������Ƶ��PID
	UINT16	audio_stream_type[AMSSIP_PMT_MAX_AUDIO_NUM]; //!< ��Ŀ�����ĸ���Ƶ������
	UINT8	audio_lang[AMSSIP_PMT_MAX_AUDIO_NUM][AMSSIP_PMT_AUDIO_639LANG_MAX_CNT][3]; //!< ��Ŀ����Ƶ���Ķ����԰���
	UINT16	video_pid; //!< ��Ŀ����ƵPID
	UINT16 video_stream_type; //!< ��Ŀ����Ƶ������
	amssip_ca_info_t ca_info[AMSSIP_PMT_MAX_CA_NUM]; //!< ��Ŀ������Ϣ 
	UINT8 ca_count; //!< ��Ŀͬ��CA����
	UINT16 pcr_pid; //!< PCR PID
	//av�����es stream��Ϣ
	UINT16 es_pid_cnt; //!< ES����
	UINT16 es_pid[AMSSIP_PMT_MAX_ES_CNT]; //!< ES PID
	UINT8 es_type[AMSSIP_PMT_MAX_ES_CNT]; //!< ES����
	UINT8  version_number; //!< version number
	UINT8  last_sec_numb; //!< last section number
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT]; //!< PMT˽����������Ϣ
	UINT8 desc_cnt;
}amssip_pmt_info_t;

//! @union amssip_ts_info_t
//! @brief ����NIT����Ϣ�洢�ṹ������ȫ���ӱ����Ϣ�����У�network_service_param��¼����NIT����Я����SERVICE_LIST_DESCRIPTOR��������Ϣ(Ҳ����û��)��
typedef union
{
	struct 
    {
        UINT8 type;  //!< amssip_front_type_e
    }common;
    struct
    {
        UINT8 type;
		UINT32 frq;
		UINT8 fec_outer;
        UINT8 modulation;
        UINT32 sym;
		UINT8 fec_inner;
    }c_info;
    struct //reserve for -T
    {
        UINT8 type;
		UINT32 frq;
    }t_info;
	struct //reserve for -S
    {
        UINT8 type;
		UINT32 frq;
    }s_info;
}amssip_ts_info_t;

//! @struct amssip_nit_service_t
//! @brief NIT service
typedef struct
{
	UINT16 org_network_id; //!< ԭʼ����ID
	UINT16 ts_id;          //!< TS ID
	UINT16 service_id;     //!< Service ID
	UINT8  service_type;   //!< Service Type
}amssip_nit_service_t;

//! @struct amssip_netwrok_ts_param_t
//! @brief Network PMT parser
typedef struct
{
	UINT32 ts_cnt;                                  //!< �����е�TS����
	UINT16 ts_id[AMSSIP_NIT_MAX_TS_NUM];            //!< TS ID
	UINT16 org_network_id[AMSSIP_NIT_MAX_TS_NUM];   //!< TS��ԭʼ����ID
	amssip_ts_info_t ts_info[AMSSIP_NIT_MAX_TS_NUM];//!< TS��ǰ��������Ϣ	
}amssip_netwrok_ts_param_t;

//! @struct amssip_network_service_param_t
//! @brief Network serviceparameter
typedef struct
{
	amssip_nit_service_t nit_service[AMSSIP_MAX_PROG_NUM];//!< �����е�service����service_list_descriptorЯ�� 
	UINT16 nit_service_cnt;                               //!< �����е�service����
}amssip_network_service_param_t;

//! @struct amssip_nit_info_t
//! @brief store NIT parser
typedef struct
{
	//Network
	UINT32 cur_network_id; //!< ��������ID
	UINT32 network_cnt; //!< �������
	UINT16 network_id[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< ����ID
	UINT8 network_name[AMSSIP_NIT_MAX_NETWORK_NUM][AMSSIP_NET_NAME_MAX_LEN]; //!< ��������
	UINT8  version_number[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< version number 
	UINT8  last_sec_numb[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< last section number 
	//TS of network
	amssip_netwrok_ts_param_t network_ts_param[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< �����е�TS��Ϣ
	//Service of network
	amssip_network_service_param_t network_service_param[AMSSIP_NIT_MAX_NETWORK_NUM]; //!< �����е�Service��Ϣ
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT]; //!< NIT˽����������Ϣ
	UINT8 desc_cnt;
}amssip_nit_info_t;

//! @struct amssip_bat_service_list_t
//! @brief ����BAT����Ϣ�洢�ṹ������ȫ���ӱ����Ϣ��
typedef struct
{
	UINT16 service_cnt; //!< �����Ŀ����
	UINT16 ts_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< ��Ŀ���ڵ�TS ID
	UINT16 org_network_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< ��Ŀ���ڵ�ԭʼ����ID
	UINT16 service_id[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< ��Ŀ��Service ID
	UINT8 service_type[AMSSIP_BAT_BQT_MAX_PROG_NUM]; //!< ��Ŀ��Service Type
}amssip_bat_service_list_t;

//structure for store BAT parser
//! @struct amssip_bat_info_t
//! @brief store BAT parser��
typedef struct
{
	//Bouquet
	UINT32 bouquet_cnt; //!< �������
	UINT16 bouquet_id[AMSSIP_BAT_MAX_BQT_NUM]; //!< �����Bouquet ID
	UINT16 bouquet_name[AMSSIP_BAT_MAX_BQT_NUM][AMSSIP_BQT_NAME_MAX_LEN]; //!< ��������
	UINT8  version_number[AMSSIP_BAT_MAX_BQT_NUM]; //!< version number
	UINT8  last_sec_numb[AMSSIP_BAT_MAX_BQT_NUM]; //!< last section number
	//Service
	amssip_bat_service_list_t service[AMSSIP_BAT_MAX_BQT_NUM]; //!< ����Ľ�Ŀ�б�
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_bat_info_t;

//! @struct amssip_sdt_ref_service_t
//! @brief sdt ref service
typedef struct
{
	UINT8 ref_cnt;
	UINT16 ts_id[AMSSIP_SDT_MAX_REF_NUM];
	UINT16 org_network_id[AMSSIP_SDT_MAX_REF_NUM];
	UINT16 service_id[AMSSIP_SDT_MAX_REF_NUM];
}amssip_sdt_ref_service_t;

//! @struct amssip_sdt_service_t
//! @brief ����SDT����Ϣ�洢�ṹ������һ��tsȫ���ӱ����Ϣ�����У�free_addr��char_buffΪSiParser�ڲ�ʹ�����û���ֹʹ�á�����NVOD�ο�ҵ��SiParser������nvod_reference_descriptor������������ҵ��Ҳ��������mosaic_descriptor ��
typedef struct
{
	UINT16 service_cnt; //!< Service����
	UINT16 service_id[AMSSIP_TP_MAX_PROG_NUM]; //!< Service ID
	UINT16 ref_service_id[AMSSIP_TP_MAX_PROG_NUM];//!< ʱ��ҵ�������Ĳο�ҵ�� ID.  (NVOD timeshift service descriptor)
//NOVD need or not NVOD_reference_descriptor???
//	amssip_sdt_ref_service_t refed_service[AMSSIP_TP_MAX_PROG_NUM];//NVOD_reference_descriptor
	UINT8 service_type[AMSSIP_TP_MAX_PROG_NUM]; //!< Service Type
	UINT8 name_len[AMSSIP_TP_MAX_PROG_NUM]; //!< ��Ŀ������
	UINT8 *service_name[AMSSIP_TP_MAX_PROG_NUM]; //!< ��Ŀ����
	UINT8 provider_name_len[AMSSIP_TP_MAX_PROG_NUM]; //!< ��Ŀ��Ӧ�����Ƴ���
	UINT8 *provider_name[AMSSIP_TP_MAX_PROG_NUM]; //!< ��Ŀ��Ӧ������
}amssip_sdt_service_t;

//! @struct amssip_sdt_info_t
//! @brief store SDT parser
typedef struct
{
    //TS
	UINT16 ts_cnt; //!< TS������ Actual + Other��
	UINT16 cur_ts_id; //!< ����TS ID
	UINT16 ts_id[AMSSIP_SDT_MAX_TS_NUM]; //!< ȫ���ӱ�TS ID
	UINT16 org_network_id[AMSSIP_SDT_MAX_TS_NUM]; //!< ȫ���ӱ�ԭʼ����ID
	UINT8  version_number[AMSSIP_SDT_MAX_TS_NUM]; //!< version number
	UINT8  last_sec_numb[AMSSIP_SDT_MAX_TS_NUM]; //!< last section number
    //Service
	amssip_sdt_service_t service[AMSSIP_SDT_MAX_TS_NUM]; //!< Service��Ϣ
	UINT32 free_addr; //!< ���еĽ�Ŀ���洢��ַ��Parser�ڲ�ʹ�á�
	UINT8 char_buff[AMSSIP_SDT_NAME_BUF_LEN]; //!< ��Ŀ���ƴ洢��ַ��Parser�ڲ�ʹ�á�
	sip_descripter_vector_t priv_desc[AMSSIP_PRIV_DESC_MAX_CNT];
	UINT8 desc_cnt;
}amssip_sdt_info_t;

//! @struct amssip_pmt_es_info
//! @brief ����PMT�ӱ���������Ϣ�ṹ�������ڷ���PMTЯ����������ʱ����section��������Ϣ��
typedef struct
{
	UINT8 cnt; //!< �����԰�������
	UINT8 lan_639[AMSSIP_PMT_AUDIO_639LANG_MAX_CNT][3]; //!< �����԰���������Ϣ
	UINT8 audio_type[AMSSIP_PMT_AUDIO_639LANG_MAX_CNT]; //!< ��������
}amssip_pmt_es_info;

//! @struct amssip_pmt_context_t
//! @brief PMT context informateion for descripter parser
typedef struct
{
	UINT16	prog_number; //!< ��Ŀprogram number
	UINT8 version_num; //!< version number
	UINT8 stream_type; //!< ES ����  (for loop2 descripter)
	UINT16 es_pid; //!< ES PID   (for loop2 descripter)
	amssip_pmt_es_info es; //!< ES ������Ϣ
	UINT8 loop; //!< ���������ڵ�loop�㼶
}amssip_pmt_context_t;

//! @struct amssip_nit_context_t
//! @brief ����NIT�ӱ���������Ϣ�ṹ�������ڷ���NITЯ����������ʱ����section��������Ϣ��
typedef struct
{
	UINT8 table_id;  //!< Table ID
	UINT16 network_id; //!< Network ID
	UINT16 ts_id; //!< TS ID (��loop2�����ӷ���ʹ��)
	UINT16 org_network_id; //!< ԭʼ����ID (��loop2�����ӷ���ʹ��)
	UINT8 version_num;//!< �汾��
	UINT8 loop; //!< ���������ڵ�loop�㼶
}amssip_nit_context_t;

//! @struct amssip_bat_context_t
//! @brief ����BAT�ӱ���������Ϣ�ṹ�������ڷ���BATЯ����������ʱ����section��������Ϣ��
typedef struct
{
	UINT16 table_id; //!< Table ID
	UINT8 version_num; //!< �汾��
	UINT16 bouquet_id; //!< ����Bouquet ID
	UINT16 ts_id; //!< TS ID (��loop2�����ӷ���ʹ��)
	UINT16 org_network_id; //!< ԭʼ����ID (��loop2�����ӷ���ʹ��)
	UINT8 loop; //!< ���������ڵ�loop�㼶
}amssip_bat_context_t;

//! @struct amssip_sdt_context_t
//! @brief ����SDT�ӱ���������Ϣ�ṹ�������ڷ���SDTЯ����������ʱ����section��������Ϣ��
typedef struct
{
	UINT8 table_id; //!< Table ID
	UINT16 ts_id; //!< TS ID
	UINT16 org_network_id; //!< ԭʼ����ID (��loop2�����ӷ���ʹ��)
	UINT16 service_id;  //!< Service ID (��loop2�����ӷ���ʹ��)
	UINT8 version_num; //!< �汾��
	UINT8 loop; //!< ���������ڵ�loop�㼶
}amssip_sdt_context_t;


/*!
@brief PAT�ӱ�section������
@details PAT�ӱ�section��������������洢��info�ṹ�С�
@param[in] buf ��������PAT section buffer��
@param[in] buf_len ��������PAT section buffer����(byte)��
@param[out] info ������ŷ��������buffer��
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_pat_section(UINT8 *buf, UINT32 buf_len,  amssip_pat_info_t *info);

/*!
@brief CAT�ӱ�section������
@details CAT��section��������������洢��infoָ��Ľṹ�С�
@param[in] buf ��������CAT section buffer��
@param[in] buf_len ��������CAT section buffer����(byte)��
@param[in/out] info ������ŷ��������buffer�����Ҫ����˽�������ӣ���ôinfo�е�priv_desc��desc_cnt������ȷ��д����ο�sip_descripter_vector_t����˵����Sample���롣
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_cat_section(UINT8 *buf, UINT32 buf_len,  amssip_cat_info_t *info);

/*!
@brief PMT�ӱ�section������
@details PMT�ӱ�section��������������洢��info�ṹ�С�
@param[in] buf ��������CAT section buffer��
@param[in] buf_len ��������CAT section buffer����(byte)��
@param[in/out] ������ŷ��������buffer�����Ҫ����˽�������ӣ���ôinfo�е�priv_desc��desc_cnt������ȷ��д����ο�sip_descripter_vector_t����˵����Sample���롣
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_pmt_section(UINT8 *buf, UINT32 buf_len,  amssip_pmt_info_t *info);

/*!
@brief NIT�ӱ�section������
@details NIT�ӱ�section��������������洢��info�ṹ�С�
@param[in] buf ��������CAT section buffer��
@param[in] buf_len ��������CAT section buffer����(byte)��
@param[in/out] info ������ŷ��������buffer�����Ҫ����˽�������ӣ���ôinfo�е�priv_desc��desc_cnt������ȷ��д����ο�sip_descripter_vector_t����˵����Sample���롣
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_nit_section(UINT8 *buf, UINT32 buf_len,  amssip_nit_info_t *info);

/*!
@brief BAT�ӱ�section������
@details BAT�ӱ�section��������������洢��info�ṹ�С�
@param[in] buf ��������CAT section buffer��
@param[in] buf_len ��������CAT section buffer����(byte)��
@param[in/out] info ������ŷ��������buffer�����Ҫ����˽�������ӣ���ôinfo�е�priv_desc��desc_cnt������ȷ��д����ο�sip_descripter_vector_t����˵����Sample���롣
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_bat_section(UINT8 *buf, UINT32 buf_len,  amssip_bat_info_t *info);

/*!
@brief SDT�ӱ�section������
@details SDT�ӱ�section��������������洢��info�ṹ�С�
@param[in] buf ��������CAT section buffer��
@param[in] buf_len ��������CAT section buffer����(byte)��
@param[in/out] info ������ŷ��������buffer�����Ҫ����˽�������ӣ���ôinfo�е�priv_desc��desc_cnt������ȷ��д����ο�sip_descripter_vector_t����˵����Sample���롣
@retval SUCCESS ���ǳɹ�
@retval ����ֵ ʧ�ܣ��������󣬽�Ŀ��������֧�ֵ��������ȡ�
*/
INT32 amssip_sdt_section(UINT8 *buf, UINT32 buf_len,  amssip_sdt_info_t *info);

/*!
 * @}
 */

/*!
@}
*/

#endif

