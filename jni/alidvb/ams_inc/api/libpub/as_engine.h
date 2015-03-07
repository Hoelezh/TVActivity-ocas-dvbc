/*
 * Copyright (C) ALi Shanghai Corp. 2004
 *
 * File: lib_autoscan.h
 *
 * Content: auto-scan service implementation for M3327 chip based IRD.
 *
 * History:
 *    Date	Version		Author		Comment
 *    ========	======= 	========	========
 */
#ifndef _AS_EGINE_H
#define _AS_EGINE_H

#include <adr_sys_config.h>
#include <api/libsi/si_search.h>

/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSSIS
 *  @{
 */
 
enum as_state_e
{
	AS_ON_IDLE = 0,
	AS_ON_SEARCH = 1,
	AS_ON_STOPING = 2
};


typedef union
{
    struct
    {
		UINT32 sym;
        UINT8 modulation;        
    }c_info;
    struct //reserve for -T
    {
        UINT32 sym;
    }t_info;
	struct //reserve for -S
    {
        UINT32 sym;
	UINT8 por;
    }s_info;
}amsas_frontend_param;

typedef struct
{
	UINT32 as_from;
	UINT32 as_to;
	UINT32 bandwidth;
	amsas_frontend_param ft_param;
}amsas_band_param;


typedef struct
{
    UINT8 as_frontend_type;
	UINT8 nim_id;
	UINT16 sat_id;
	UINT32 band_cnt; //0 blind scan
	INT32 as_method;//dvv-s
	UINT16 as_sat_cnt;//dvv-s
	UINT16 sat_ids[256];//dvv-s
	amsas_band_param band[AS_BAND_MAX_CNT];
	UINT32 turning_timeout;//ms
    amssearch_config_t search_config;
}amsas_service_param;

enum nit_notify_retval_e
{
	GO_ON_SEARCH,
	RESET_SEARCH	
};


#ifdef __cplusplus
extern "C"{
#endif

/*!
@brief AS serviceע�ᡣ
@details ע��AS service��
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX ʧ��
*/
INT32 amsas_service_register(void);

/*!
@brief AS service��ʼ��
@details ��ʼ�������ú���Ϊ�첽������ֻ����AS(PUB)��task����һ����̨����Ϣ��AS�յ������Ϣ֮�󣬾ͻ�����û��������������������Ƶ�����Ƶ��Ľ�Ŀ��������Ŀ�Ĺ����У���ͨ���ϲ㴫�ݵ�callback֪ͨ�����������Ϣ��Ӧ�ò�����Ӧ�Ĵ���������ʾ���ȡ����˽�Ŀ�ȵȡ�
һ������̨��ʱ����ҪֹͣCA��EPG��TDT�ȣ��ͷű����DMXӲ��filter���Լӿ���̨���ٶȡ�
����̨�Ĵ��������ط�����һЩ��ͬ�Ĺ淶Ҫ�󣬱����е�Ҫ��Ƶ����̨��ʱ����Ҫ�Ѹ�Ƶ��Ľ�Ŀ��ɾ����ȫƵ����̨��ʱ����Ҫ�Ȱ����еĽ�Ŀɾ��������̨֮�󣬽�Ŀ��Ҫ���˺����򣬲����û������Ƿ���Ҫ���浽���ݿ⣬�ȵȡ���Щ���ƻ��Ĺ�����������Ӧ�ò��porting��������AMS�м���ڲ���������
SI Searchģ������ֻ����DVB�淶�����ݼ�Descriptor�������Ҫ����˽�е�Descriptor������̨֮ǰ����������SI Psearch������˽�е�Descriptor��������Ϣ����̨�����л������˽�е�Descriptor parser�������ݣ������������section_info��priv���������ͨ��si_porting_store_program()���ݸ�Ӧ�ó���(�����÷����Բο�SI Parser��˵����as_test.c)
@param[in] asp �ο�as_engine.h��si_search.h�Ķ��塣
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX ʧ��
*/
INT32 amsas_service_start(amsas_service_param *asp);

/*!
@brief AS serviceֹͣ��
@details ֹͣ�������ú���Ϊͬ��������ֱ��AS��SI Search����ֹͣ��̨��
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX ʧ��
*/
INT32 amsas_service_stop(void);

/*!
@brief ��ȡSearch״̬��
@details ��ȡSearch״̬��APPĳЩ�������Ҫ��ȡ��̨��״̬���ж��Ƿ���һЩ��Ϣ����Ӧ�������յ�CA����������Ϣ����������������̨����ô��Щ��Ϣ�Ͳ�����ʾ�ˡ�
@retval SUCCESS ���ǳɹ�
@retval ERR_XXX ʧ��
*/
INT32 amsas_service_query_stat(void);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

/*!
@}
*/

#endif /* _LIB_AS_H */
