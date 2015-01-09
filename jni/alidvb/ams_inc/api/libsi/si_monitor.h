/*
 * Copyright (C) ALi Shanghai Corp. 2005.
 *
 * si_monitor.h
 *
 * a SI information tracking utility header file.
 */
#ifndef __SI_MONITOR_H__
#define __SI_MONITOR_H__

#include <adr_sys_config.h>

#define AMSSIM_MONIT_SDT_OTHER	0x00000001
#define AMSSIM_MONIT_BAT		0x00000002
#define AMSSIM_MONIT_NIT_CUR	0x00000004
#define AMSSIM_MONIT_NIT_OTHER	0x00000008
#define AMSSIM_MONIT_PMT_OTHER	0x00000010
#define AMSSIM_MONIT_DEFAULT	0x80000000

#define SIM_MSG_PAT				0x0
#define SIM_MSG_PMT				0x1
#define SIM_MSG_SDT				0x2
#define SIM_MSG_SDT_OTH			0x3
#define SIM_MSG_BAT				0x4
#define SIM_MSG_NIT				0x5
#define SIM_MSG_NIT_OTH			0x6
#define SIM_MSG_DYNAMIC_PID		0x7


/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSSIM
 *  @{
 */

//! @enum AMSSIM_TABLE_TYPE
//! @brief ���������͡�
typedef enum
{
    AMSSIM_TABLE_PAT = 0,
    AMSSIM_TABLE_PMT,
    AMSSIM_TABLE_SDT,
    AMSSIM_TABLE_SDT_OTH,
    AMSSIM_TABLE_BAT,
    AMSSIM_TABLE_NIT,
    AMSSIM_TABLE_NIT_OTH
}AMSSIM_TABLE_TYPE;
 
//! @struct si_monitor_msg
//! @brief SI Monitor message�Ķ��塣
typedef struct
{
    UINT16 cmd_type;
	UINT8 table_id;
	UINT32 ext_id;
	UINT8 sec_num;
	UINT32 crc;
	UINT8 handle;
}si_monitor_msg;

#ifdef __cplusplus
extern "C"{
#endif

typedef void(*sim_notify_t)(si_monitor_msg *msg, UINT32 param);

/*!
@brief ��ʼ��SIM��
@details �˺������ڳ�ʼ��SI monitor�⡣Si monitorģ��ͨ���˺��������ڲ���Ҫ����Դ��
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_init(void);

/*!
@brief �ͷ�SIM��Դ��
@details Si monitorģ��ͨ���˺����ͷ���amssim_init()��������������Դ��
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_uninit(void);

/*!
@brief ��SI���ӡ�
@param[in] dmx_id DMX��index�š�
@param[in] prog_num ��ǰ��Ŀ��program number��
@param[in] table ������Щ���ο���غ궨�塣
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_open_monitor(UINT8 dmx_id, UINT16 prog_num, UINT32 table, UINT8 ignore_crc);

/*!
@brief �ر�SI���ӡ�
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_close_monitor(void);

/*!
@brief ��SI���ӡ�
@param[in] func �ص�����ָ�롣
*/
void  amssim_reg_callback(sim_notify_t func);

/*!
@brief ��SI���ӡ�
@param[in] table_id ���table id��
@param[in] extension_id �ӱ��id��
@param[in] sec_num ��� section number��
@param[in] crc Section���ݵ�CRCֵ��
@param[in] buf ������ݵĴ�ſռ䡣
@param[in/out] len �������ֵ�������Чֵ��
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_get_section(AMSSIM_TABLE_TYPE table_type, UINT32 extension_id, UINT8 sec_num, UINT32 crc, UINT8 *buf, UINT16 *len);

/*!
@brief ���Monitor��ǰ��handle��
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
UINT8 amssim_get_handle(void);

/*!
@brief ���ü�ر��˽��pid��table_id��
@param[in] table_type ������͡�
@param[in] pid ���pid��
@param[in] table_id ���table id��
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amssim_set_table_priv_parm(AMSSIM_TABLE_TYPE table_type, UINT16 pid, UINT8 table_id);

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

/*!
@}
*/

#endif /* __DVB_SIE_MONITOR_H__ */

