/****************************************************************************
 *
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2004 (C)
 *
 *  File: lib_hde.h
 *
 *  Description: This file implement the hardware display engine on
 *               ALi M3327 chip.
 *
 *  History:
 *      Date		Author		Version  	Comment
 *      ==========	==========  =======		=============================		
 *  1.  2004.10.21	Tom Gao		0.1.000		Initial
 ****************************************************************************/

#ifndef __LIB_PUB27_HDE_H__
#define __LIB_PUB27_HDE_H__

#include <adr_basic_types.h>

/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSCC
 *  @{
 */

#define VIEW_MODE_FULL			0
#define VIEW_MODE_PREVIEW		1
#define VIEW_MODE_MULTI		2
#define VIEW_MODE_SML			3

/*!
@brief ���ñ���ɫ��
@details ����VPO�ĵ�ɫ����ɫ����VPO Window Off֮ǰ��Ҫ������VPO Off��ı���ɫ��һ�㶼������Ϊ��ɫ��
@param[in] bY �Ҷȷ���ȡֵ����ɫ�ɸ�ֵ16(����0) ��
@param[in] bCb Cb����ȡֵ����ɫ�ɸ�ֵ�м�ֵ128��
@param[in] bCr Cr����ȡֵ����ɫ�ɸ�ֵ�м�ֵ128��
*/
void hde_back_color(UINT8 bY, UINT8 bCb, UINT8 bCr);

/*!
@brief ���ñ���ɫ��
@details ����VPO�ĵ�ɫ����ɫ����VPO Window Off֮ǰ��Ҫ������VPO Off��ı���ɫ��һ�㶼������Ϊ��ɫ��
@param[in] bY �Ҷȷ���ȡֵ����ɫ�ɸ�ֵ16(����0) ��
@param[in] bCb Cb����ȡֵ����ɫ�ɸ�ֵ�м�ֵ128��
@param[in] bCr Cr����ȡֵ����ɫ�ɸ�ֵ�м�ֵ128��
*/
void hde_set_mode(UINT32);

/*!
@brief ����previewλ�ü���С��
@details ����preview���ڵ�λ�úʹ�С����������hde_set_mode() preview֮ǰ����Ҫ������λ�ò�����
@param[in] x preview������ʼ����λ�á�ȡֵ��Χ��0-720(����720)��
@param[in] y preview������ʼ����λ�á�ȡֵ��Χ����PAL�ƣ�0-576(����576)����NTSC�ƣ�0-480(����480)��
@param[in] w preview���ڵĴ�С��ȡֵ��Χ��0-720���������720�����ʾ�Ŵ��ȡ�
@param[in] h preview���ڵĴ�С��ȡֵ��Χ����PAL�ƣ�0-576����NTSC�ƣ�0-480�����h����576(480)�����ʾ�Ŵ�߶ȡ�
@param[in] IsPAL ��ǰ���ŵĽ�Ŀ�Ƿ���PAL�ƵĽ�Ŀ�� ����PAL�ƺ�NTSC�ƵĽ�Ŀ��preview��Ҫ���ò�ͬ��scale������
@note ���x��y��ֵ����720x576(480)��������Ļ�Ͽ������κλ��档���w��h����һ��Ϊ0�Ļ����򲻻���ʾ�κλ��档��x��y��w��hû�ж����Ҫ�󣬿���������������ż����
*/
void hde_config_preview_window(UINT16 x, UINT16 y, \
      UINT16 w, UINT16 h, BOOL IsPAL);

/*!
@brief ��ȡ��ǰVPO���ڵ���ʾģʽ��
@details ��ȡ��ǰVPO���ڵ���ʾģʽ��
@retval 0 VIEW_MODE_FULL
@retval 1 VIEW_MODE_PREVIEW
@retval 2 VIEW_MODE_MULTI
@retval 3 VIEW_MODE_SML
*/
UINT32 hde_get_mode(void);


/*!
 * @}
 */

/*!
@}
*/

#endif /* __LIB_PUB27_HDE_H__ */

