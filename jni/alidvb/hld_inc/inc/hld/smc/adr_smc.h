#ifndef __ADR_HLD_SMC_H__
#define __ADR_HLD_SMC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <hld/adr_hld_dev.h>
#include <ali_smc_common.h>

/*! @addtogroup smc
 *  @{
 */
#define SMC_IO_ON		1
#define SMC_IO_OFF		0

#define SMC_STATUS_OK			0
#define SMC_STATUS_NOT_EXIST	1
#define SMC_STATUS_NOT_RESET	2
#define BOARD_SUPPORT_CLASS_A		(1<<0)
#define BOARD_SUPPORT_CLASS_B		(1<<1)
#define BOARD_SUPPORT_CLASS_C		(1<<2)


/*! @enum smc_device_ioctrl_command
    @brief ���ܿ� ����IO ���� ����
*/
enum smc_device_ioctrl_command
{
	SMC_DRIVER_SET_IO_ONOFF = 0,	//!<δʵ�֡�	
	SMC_DRIVER_SET_ETU,		//!<�趨����etu��
	SMC_DRIVER_SET_WWT,		//!<�趨���ֽڵȴ���ʱ����λ���롣			
	SMC_DRIVER_SET_GUARDTIME,	//!<δʵ�֡�
	SMC_DRIVER_SET_BAUDRATE,	//!<δʵ�֡�
	SMC_DRIVER_CHECK_STATUS,	//!<��⿨��״̬��
	SMC_DRIVER_CLKCHG_SPECIAL,	//!<δʵ�֡�
	SMC_DRIVER_FORCE_SETTING,	//!<δʵ�֡�
	SMC_DRIVER_SET_CWT,		//!<�趨�ֽڵȴ���ʱ��
	SMC_DRIVER_GET_F,		//!<���ATR F����ֵ�����ڼ�����ETU ��
	SMC_DRIVER_GET_D,		//!<���ATR D����ֵ�����ڼ�����ETU ��
	SMC_DRIVER_GET_ATR_RESULT,	//!<���ܿ�ATR ״̬��
	SMC_DRIVER_GET_ATR,			//!<���ܿ�ATR 
	SMC_DRIVER_GET_HB,		//!<��ȡATR  History Bytes ��
	SMC_DRIVER_GET_PROTOCOL,	//!<��ȡ���ܿ���ǰ����Э�顣
	SMC_DRIVER_SET_WCLK,		//!<�����趨���ܿ�����Ƶ�ʣ���Ƶ����reset ���ܿ�����Ч��
	SMC_DRIVER_SEND_PPS,		//!<����PPS ���
	SMC_DRIVER_SET_PROTOCOL,	//!<�������ܿ���ǰ����Э�飬δʵ�֡�
	SMC_DRIVER_SET_OPEN_DRAIN,	//!<�������ܿ��Ƿ�֧��open drain, bit0 : en_power_open_drain; bit1 : en_clk_open_drain; bit2 : en_data_open_drain; bit3 : en_rst_open_drain.
	SMC_DRIVER_SET_DEBUG_LEVEL,	//!<�������ܿ�����level
	SMC_DRIVER_GET_CLASS,			/*return the currently selected classs*/
	SMC_DRIVER_SET_CLASS			/*setting new class selection if previous select fail*/
};

/*! @enum smc_device_status
    @brief ���ܿ��豸״̬��
*/
typedef enum smc_device_status
{
	SMC_DEV_ATTACH = 0,
	SMC_DEV_OPEN,
	SMC_DEV_CLOSE,
	SMC_DEV_DETACH	
}smc_device_status_e;


#define SMC_FORCE_BASE		0x1
#define SMC_FORCE_TX_RX	(SMC_FORCE_BASE + 1)
struct smc_gpio_info		/* Total 1 byte */
{
	UINT8	polar;	/* Polarity of GPIO, 0 or 1  is enable or for smart card */
	UINT8	io;	/* HAL_GPIO_I_DIR or HAL_GPIO_O_DIR in hal_gpio.h */
	UINT8	position;	/* GPIO index, upto 64 GPIO */
};

struct smc_hw_info
{
	UINT8 io_type;		/*0 uart io; 1 iso_7816 io. Only can be 0 now*/
	UINT8 uart_id;		/*SCI_FOR_RS232 0, SCI_FOR_MDM 1*/
	UINT8 gpio_control;	/*1 gpio control*/
	UINT8 ext_clock;	/*0 internal clock; 1 external clock*/
	UINT8 shared_uart;	/*0 ; 1 shared with rs232 with uart_switch gpio*/
	UINT8 uart_with_appinit : 1;
	UINT8 reserved : 7;
	
	struct smc_gpio_info prest;
	struct smc_gpio_info power;
	struct smc_gpio_info reset;
	struct smc_gpio_info uart_switch;
	//add for external 6MHz clock
	struct smc_gpio_info clock_switch;
	UINT32 clock;			/*external clock*/
	//add for external 6MHz clock
	UINT32 clock_ext;		/*external clock 2*/
	UINT32 to_for_atr;		/*timeout for atr in ms*/
	UINT32 to_for_cmd;	/*timeout for command in ms*/
};

/*!@struct smc_dev_config	
   @brief �ṹ���������ܿ�������ʼ�����á�
*/


/*!@struct smc_device
   @brief ���ܿ�����ģ���豸�ڵ㡣
 */
struct smc_device
{
	struct hld_device *next;		/* Next device structure */
	UINT32 type;					/* Interface hardware type */
	INT8 name[HLD_MAX_NAME_SIZE];	/* Device name */

	UINT16 flags;					/* Interface flags, status and ability */
	UINT32 base_addr;			/* Device IO base addr */
	UINT8  irq;					/*interrupt number using for s3602*/
								/* Hardware privative structure */
	void *priv;					/* pointer to private data */	

    /* If allow block ? */
    UINT8 blockable;
	void	(*callback)(UINT32 param);
};


/*!
@brief �ҽ����ܿ��豸 ��
@param[in] dev_id ��ҽӵ����ܿ��豸�ţ�0 ��1��
@param[in] config_param ���ܿ���ʼ�����ýṹ��ָ�롣
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_dev_attach(int dev_id, struct smc_dev_cfg * config_param);

/*!
@brief ж�����ܿ��豸 ��
@param[in] dev_id ��ҽӵ����ܿ��豸�ţ�0 ��1��
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_dev_dettach(int dev_id);

INT32 smc_attach(int dev_id, int use_default_cfg,
                 struct smc_dev_cfg *cfg);

/*!
@brief �����ܿ��豸 ��
@param[in] dev ��򿪵����ܿ��豸�ڵ㡣
@param[in] callback Ӧ�ò�ע���callback����������֪ͨӦ�ò㿨����γ������
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_open(struct smc_device *dev, void (*callback)(UINT32 param));

/*!
@brief �ر����ܿ��豸 ��
@param[in] dev ��رյ����ܿ��豸�ڵ㡣
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_close(struct smc_device *dev);

/*!
@brief ������ܿ��豸�Ƿ���� ��
@param[in] dev ��������ܿ��豸�ڵ㡣
@return INT32��
@retval  0       �����롣
@retval  ��0  ���γ���
*/
INT32 smc_card_exist(struct smc_device *dev);

/*!
@brief �������ܿ���
@param[in] dev �����������ܿ��豸�ڵ㡣
@param[in] buffer ����ATR ���ݵĵ�ַ��
@param[out] *atr_size ʵ�ʽ��յ�ATR ���ݳ��ȡ�
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_reset(struct smc_device *dev, UINT8 *buffer, UINT16 *atr_size);

/*!
@brief �������ܿ���
@param[in] dev �����ߵ����ܿ��豸�ڵ㡣
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_deactive(struct smc_device *dev);

/*!
@brief �����ܿ���ȡ���ݡ�
@param[in] dev����ȡ���ݵ����ܿ��豸�ڵ㡣
@param[in] buffer �������ܿ� ���ݵĵ�ַ��
@param[in] size ������ȡ�� ���ݳ��ȡ�
@param[out] *actlen ʵ�ʽ��յ� ���ݳ��ȡ�
@return INT32��
@retval  0       �ɹ���
@retval  ��0  δ��ȡ�κ����ݡ�
*/
INT32 smc_raw_read(struct smc_device *dev, UINT8 *buffer, INT16 size, INT16 *actlen);

/*!
@brief �����ܿ��������ݡ�
@param[in] dev���������ݵ����ܿ��豸�ڵ㡣
@param[in] buffer ������ ���ݵĵ�ַ��
@param[in] size �������͵� ���ݳ��ȡ�
@param[out] *actlen ʵ�ʷ��͵� ���ݳ��ȡ�
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ����ʧ�ܡ�
*/
INT32 smc_raw_write(struct smc_device *dev, UINT8 *buffer, INT16 size, INT16 *actlen);
INT32 smc_raw_fifo_write(struct smc_device *dev, UINT8 *buffer, INT16 size, INT16 *actlen);
/*!
@brief ��ѭISO7816 T0 Э������ݴ���ӿڡ�
@param[in] dev���������ݵ����ܿ��豸�ڵ㡣
@param[in] command ������ ��������ݵĵ�ַ��
@param[in] num_to_write �������͵� ��������ݵ��ܳ��ȡ�
@param[in] response ���� ���ݵĵ�ַ��
@param[in] num_to_read �������յ� ���ݳ��ȡ�
@param[out] *actual_size ʵ�ʽ��յ� ���ݳ��ȡ�
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
*/
INT32 smc_iso_transfer(struct smc_device *dev, UINT8 *command, INT16 num_to_write, UINT8 *response, INT16 num_to_read, INT16 *actual_size);
INT32 smc_iso_transfer_t1(struct smc_device *dev, UINT8 *command, INT16 num_to_write, UINT8 *response, INT16 num_to_read,INT32 *actual_size);
INT32 smc_iso_transfer_t14(struct smc_device *dev, UINT8 *command, INT16 num_to_write, UINT8 *response, INT16 num_to_read,INT32 *actual_size);
/*!
@brief ���ܿ� ģ���io contorl ������
@param[in] dev ָ�����ܿ�ģ�� ��ָ�롣
@param[in] cmd ���� ���������͡��ο�smc_device_ioctrl_command���塣
@param[in,out] param �����Ĳ��������ݲ�ͬ��������в�ͬ�Ĳ�����
@return INT32��
@retval  0       �ɹ���
@retval  ��0  ʧ�ܡ�
@note  IO�������:
<table class="doxtable"  width="800" border="1" style="border-collapse:collapse;table-layout:fixed;word-break:break-all;" >
  <tr>
    <th width="200">����</th>
    <th width="200">����</th>
    <th width="80">��������</th>
    <th width="320">��ע</th>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_SET_ETU</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>����ETU</td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_SET_WWT</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>�趨���ֽڵȴ���ʱ����λ����</td>
  </tr>

   <tr align="center">
    <td>SMC_DRIVER_CHECK_STATUS</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>��⿨��״̬(SMC_STATUS_NOT_EXIST, SMC_STATUS_NOT_RESET, SMC_STATUS_OK)</td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_SET_CWT</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>�趨�ֽڵȴ���ʱ</td>
  </tr>

   <tr align="center">
    <td>SMC_DRIVER_GET_F</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>���ATR F����ֵ�����ڼ�����ETU </td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_GET_D</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>���ATR D����ֵ�����ڼ�����ETU</td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_GET_ATR_RESULT</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>���ܿ�ATR ״̬</td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_GET_HB</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>��ȡATR  History Bytes </td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_GET_PROTOCOL</td>    
    <td>UINT32</td>    
    <td>���</td>
    <td>��ȡ���ܿ���ǰ����Э�� </td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_SET_WCLK</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>�����趨���ܿ�����Ƶ�ʣ���Ƶ����reset ���ܿ�����Ч</td>
  </tr>

  <tr align="center">
    <td>SMC_DRIVER_SEND_PPS</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>����PPS ����</td>
  </tr>

   <tr align="center">
    <td>SMC_DRIVER_SET_PROTOCOL</td>    
    <td>UINT32</td>    
    <td>����</td>
    <td>�������ܿ���ǰ����Э�飬δʵ��</td>
  </tr>
*/
INT32 smc_io_control(struct smc_device *dev, INT32 cmd, UINT32 param);
INT32 smc_t1_transfer(struct smc_device*dev, UINT8 dad, const void *snd_buf, UINT32 snd_len, void *rcv_buf, UINT32 rcv_len);


/*!
 @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HLD_SMC_H__ */

