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

#ifndef __LIB_EPG_H__
#define  __LIB_EPG_H__

#include <adr_sys_config.h>
#include <api/libsi/si_tdt.h>

/*! @addtogroup ALi�м��
 *  @{
 */

typedef INT32 (*EitCallback) (UINT32  CbParam,//!<�û�ע��Ļص�������
                            INT32  ErrCode,//!<�����롣
                            UINT8  *SecBuf,//!<section���ݵ���ʼ��ַ��
                            UINT32  SecLen);//!<section�ĳ��ȡ�

/*! @addtogroup AMSEPG
 *  @{
 */

//! @enum COMPARE_MODE
//! @brief 	����amsepg_del_service����Ҫɾ��service��ʱ���ж���ɾ������һ����Ŀ�б���Ľ�Ŀ��EPG������ɾ��������һ����Ŀ�б�Ľ�Ŀ��EPG��
//! @see amsepg_del_service
enum COMPARE_MODE
{
	EQUAL,          //!< ɾ������һ����Ŀ�б���Ľ�Ŀ��EPG
	NOT_EQUAL,      //!< ɾ��������һ����Ŀ�б�Ľ�Ŀ��EPG��
};

//! @enum EPG_NODE_STATUS
//! @brief 	Event Node��״̬��
//! @details Event���»��߱�ɾ����ʱ�򣬻ᱻ�ó�,<b>EPG_NODE_DIRTY</b>״̬��
//!   �����µ�<b>Event</b>��Ҫ��ӵ�ʱ�������ȴ�<b>EPG_NODE_FREE</b>�б�˳����䣻��<b>EPG_NODE_FREE</b>�б������ʱ�򣬲Ż�ȥ����EPG_NODE_DIRTY״̬��Node���滻֮��
//! @see struct EPG_DB_NODE
enum EPG_NODE_STATUS
{
	EPG_NODE_FREE	= 0,
	EPG_NODE_ACTIVE = 1,
	EPG_NODE_DIRTY	= 2, //!< event node deleted
};

//! @enum EPG_DB_EVENT_TYPE
//! @brief EPGģ��ͨ��callback����Ӧ�ò����Ϣ���͡�
//! @see typedef EIT_CALL_BACK
enum EPG_DB_EVENT_TYPE
{
	PRESENT_EVENT 	= 0,
	FOLLOWING_EVENT = 1,
	SCHEDULE_EVENT 	= 2,

	EPG_PF_VERSION_UPDATE = 101,
	EPG_SCH_VERSION_UPDATE,
	EPG_SERVICE_SECTION_HIT_ALL,
	EPG_SERVICE_NOT_EXIST,
	EPG_SERVICE_EXIST,
	EPG_TP_OVERFLOW,
	EPG_SERVICE_OVERFLOW,
	EPG_EVENT_OVERFLOW,
	EPG_MEM_OVERFLOW,
};

//! @struct TIME
//! @brief Event��ʼʱ��ͳ���ʱ��Ķ��塣
//! @see struct EPG_DB_NODE
struct TIME
{
	UINT8 hour: 5;		//!< 0-23
	UINT8 minute: 6;	//!< 0-59
	UINT8 second: 6;	//!< 0-59
} __attribute__((packed));

//! @struct EPG_DB_NODE
//! @brief EPG Event�Ķ��塣
struct EPG_DB_NODE
{
#ifdef EPG_MULTI_TP
	UINT32 tp_id;
#endif
	UINT16 service_id;
	UINT16 event_id;

#ifdef NVOD_FEATURE
	UINT16 ref_service_id;		//!< Add for NVOD time shifted event
	UINT16 ref_event_id;
#endif

	UINT8 tab_num: 4;		//!< Table_id & 0x0F

	UINT8 event_type: 2;		//!< see enum EPG_DB_EVENT_TYPE
	UINT8 status: 2;		//!< see enum EPG_NODE_STATUS

	UINT8  nibble: 4;		//!< Content descriptor: content_nibble1
#ifdef EPG_NIBBLE2_SUPPORT
	UINT8  nibble2: 4;		//!< Content descriptor: content_nibble2
#endif

#ifdef EPG_PARENTAL_SUPPORT
//	struct EPG_MULTI_RATING
//	{
//		UINT8 country_code[3];	//ISO 3166
		UINT8 rating: 4;		//!< 0-0xF, Parent Rating Descriptor: rating & 0x0F
//	} parental[1];
#endif

#ifdef EPG_COMPONENT_SUPPORT
	//!< video/audio stream componet type, see EN300468 "Component descriptor"
	struct STREAM_COMPONENT
	{
		UINT8 stream_content: 4;	//!< see Component descriptor
		UINT8 component_type;
	} stream_component[2];
#endif

	UINT16 mjd_num;
	struct TIME time;
	struct TIME duration;

	struct EPG_MULTI_LANG
	{
		UINT8 *text_char;	//!< [event name] + [short event text char] + [ext event text char]
		UINT16 text_length;
//		UINT8 lang_code[3];	//!< ISO_639_language_code of event name, etc.
		UINT16 lang_code2;	//!< converted from 3 byte of ISO_639_language_code
	}lang[EPG_LANGUAGE_COUNT];
	/*
	{
		UINT8 event_name_length;
		UINT8 event_name[0];
		UINT8 short_text_length;
		UINT8 short_text_char[0];
		UINT16 extend_text_length;
		UINT8 extend_text_char[0];
	}
	*/
} __attribute__((packed));

//! @typedef eit_event_info_t
//! @brief �ɵ�code����ʹ��eit_event_info_t�ṹ���塣
typedef struct EPG_DB_NODE eit_event_info_t;

//! @typedef epg_db_filter_t
//! @brief EPG View�Ĺ��˺����Ķ��塣
//! @see amsepg_create_view
typedef BOOL (*epg_db_filter_t)(struct EPG_DB_NODE *, void *);

//! @struct epg_service_t
//! @brief Active Service�Ķ��塣
//! @see amsepg_set_active_service
typedef struct ACTIVE_SERVICE_INFO
{
	UINT32 tp_id;
	UINT16 service_id;

} epg_service_t;

//! @typedef EIT_CALL_BACK
//! @brief EPGģ��Callback�Ķ��塣
//! @see struct epg_config_t
typedef void (*EIT_CALL_BACK)(UINT32 tp_id, UINT16 service_id, enum EPG_DB_EVENT_TYPE event_type);

//! @enum epg_eit_mode_e
//! @brief EIT Filter������ѡ�ȱʡ��������amsepg_on��ʱ���õ�ǰƵ�����н�Ŀ��PF��SCH������ݡ�
//! @see amsepg_on
typedef enum
{
	EIT_SINGLE_SERVICE = 0x01,		//!< single service id's mask/value enabled
	EIT_OTHER_PF_SCH   = 0x02,		//!< Table ID: 0x4F, 0x60~0x60+EPG_SCHEDULE_TABLE_ID_NUM-1 enabled

} epg_eit_mode_e;

//! @struct epg_config_t
//! @brief Ӧ�ò����amsepg_init()��ʼ��EPGģ��ʱ�������EPGģ������ò�����
//! @see amsepg_init
typedef struct
{
	UINT16 max_tp_count;		//!< TP(��Ƶ��)����������һ��cable��Ƶ�ʷ�Χ��48-859MHz������8M���������Ҳ��(859-48)/8+1=103��Ƶ�㡣���������Ҳ���Բο����ݿ��TP�������á�
	UINT16 max_service_count;	//!< ��Ŀ����������һ��300-500��������TV/Radio/NVOD�ȵ��������͵Ľ�Ŀ��
	UINT32 max_event_count;		/*!<  ����EPG Event�ĸ����������Ҫ���ݸ����ط���ʵ����������У�һ��һ��Ƶ���Event��������2000-3000������Ҫ֧�ִ洢����Ƶ���Event�Ļ���������                                  Ҫ֧��12000�����ϵ�Event��
                                    ��Ȼ��Ҫ�洢��EventԽ�࣬��Ҫ��bufferҲ��Խ�ࡣ
                                    ����bufferֻ��1M���������������Ϊ3000-5000��������2M��buffer�����������Ϊ10000-12000����*/

	UINT32 max_view_event_count;

	EIT_CALL_BACK call_back;

} epg_config_t;


#ifdef __cplusplus
extern "C"{
#endif


/*!
@brief ��ʼ��EPGģ�飬��Ҫ��buffer��һЩ����������á�
@param[in] buf EPGģ��ʹ�õ�buffer��<br>
���buf == NULL����ʾ����EPGģ���Լ��������һ��buffer��������release��ʱ�����ͷŸ�buffer��
���buf != NULL����ʾ�����ⲿ�����EPGģ��ʹ�õ�buffer����release EPG��ʱ��EPGģ�鲻�����ͷŸ�buffer����Ҫ���ⲿ�Լ��ͷŸ�buffer��

@param[in] len buffer�Ĵ�С��һ�����EPG�����ر��ĵط���������Ϊ1M���ɣ����Ƕ���EPG�ǳ���ĵط����������Ҫ2M���ϵ�buffer��
@param[in] cfg ���ò���

@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ��������󣬻���״̬���󣬻���buffer���㡣

*/
INT32 amsepg_init(UINT8* buf, UINT32 len, epg_config_t *cfg);


/*!
@brief �ͷ�EPGģ���������Դ������buffer��Event�ȵȡ�
@note ���buffer����EPGģ���Լ�����ģ�����ͷŸ�buffer��������Ҫ�ⲿ�ڵ��øú���֮�������ͷš�
@note �ú���ֻ����EPG OFF��״̬�µ��ã�Ҳ����ֻ����amsepg_off()֮����á�
*/
INT32 amsepg_unreg_callback();

/*!
@brief ��EPGģ��ע��callback��
@details �ú�������������ʱ�̵��ã�����֮���µ�callback������Ч�����������amsepg_init()֮ǰ���ã���ע���callback�����ᱻamsepg_init()�����amsepg_init()����Ѿ�����callback����������Ҫ�ٵ��øú���ע��callback�������ڽ���NVOD��Ŀ�˵���ʱ��NVOD��Ҫ����ע���Լ���callback���滻ԭ����callback�����Ե��øú�����
@param[in] callback ��Ҫע���callback������
@retval SUCCESS ���ǳɹ�
*/
INT32 amsepg_reg_callback(EIT_CALL_BACK callback);

/*!
@brief ȡ��ע���callback��������������Ч��
@details �ڽ�NVOD��ʱ��Ӧ�������������ȵ���amsepg_unreg_callback()ȡ��ԭ��ע���callback���ٵ���amsepg_reg_callback()ע���Լ���callback��ͬ�������˳�NVOD��ʱ��ҲӦ�������������ȵ���amsepg_unreg_callback()ȡ����ע���callback���ٵ���amsepg_reg_callback()�ָ�ע��ԭ�е�callback��
@retval SUCCESS ���ǳɹ�
@see amsepg_reg_callback
*/
INT32 amsepg_release();

/*!
@brief ����EPGģ�飬������е�Event��Service�б�TP�б�����memory�ȡ�
@details ���û�load default����ɾ�����н�Ŀ��ʱ����Ҫ���øú������������û��л�������ģʽ������NVOD������Ҫ����Service��Event��ֻ��Ҫ������NVOD��Ŀ��Event��Ҳ���Ե��øú�������һ��EPGģ�顣�ú���ֻ����EPG OFF��״̬�µ��á�
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amsepg_reset(void);

/*!
@brief ��EPGģ���Service�б���Ӷ��Service
@details EPGģ�������amsepg_on()��ʱ�򣬿��Ը������ݿ�ĵ�ǰTV/Radio/NVOD�Ƚ�Ŀ�б�����EPG��Service�б�Ҳ������EPG OFF��״̬�£��ⲿͨ�����øú�����EPGģ������µĲ��ڵ�ǰ��Ŀ�б��Service��
�����NVOD����TV/Radio��Channel list�¶�������NVOD�Ľ�Ŀ��NVODֻ���Լ�ͨ�����ݿ��ȵõ�NVOD�Ľ�Ŀ�б��ٵ��øú�������ЩNVOD�Ľ�ĿҲ��ӵ�EPG��Service�б��Ӷ��ﵽEPGģ��Ҳȥ��ȡNVOD��Ŀ��EIT���ݵ�Ŀ�ġ�

@param[in] service_list ��Ҫ��ӵ�Service�б�����������ο�epg_service_t�Ķ��塣
@param[in] cnt   Service�ĸ�����

@retval SUCCESS 	�ɹ�
@retval ERR_XXX	    ʧ�ܣ������������״̬����
*/
INT32 amsepg_add_service(epg_service_t *service_list, INT32 cnt);


/*!
@brief ��ʼ��SIM��
@details �˺������ڳ�ʼ��SI monitor�⡣Si monitorģ��ͨ���˺��������ڲ���Ҫ����Դ��
@param[in] service_list Service�б�����������ο�epg_service_t�Ķ��塣
@param[in] count   Service�ĸ���
@param[in] mode ɾ��ģʽ����2��ģʽ����ο�COMPARE_MODE�Ķ���
@retval SUCCESS �ɹ�
@retval ERR_XXX ʧ�ܣ�״̬����
*/
INT32 amsepg_del_service(epg_service_t *service_list, INT32 count, enum COMPARE_MODE mode);

/*!
@brief Switch On EPGģ�飬Ҳ������DMX���벢��һ��EIT��filter��ץȡEIT��actual/other present/following/schedule�����ݡ�
@details �ú������ȸ��ݵ�ǰ�û����ڹۿ���TV����Radio�ȵĽ�Ŀ�б���EPGģ���ڲ�����һ��Service�б��Լ�����Service��EIT section hitmap��EPGģ���������Service�б��hitmap���˴�     DMX�յ���EIT section���ݣ�ֻ�������Service�б�Ĳ���hitmapû�����е�section���ݲ���Ҫ��Parser�������������浽���ݿ⡣
    �����Ҫ֧��other��EIT���ݵĻ�������Ҫ����һ������TP���б�ͨ��TS ID���ж��յ���other EIT section�����������ĸ�TP��Service�����ݡ�

@param[in] dmx_id   ���ĸ�DMX����filter��DMX ID��һ����0������Ƕ��DMX�Ļ��� ���ܻ��õ�DMX 1/DMX 2�ȵȡ�
@param[in] sat_id   ����Satellite��ID���ڽ�Ŀ���ݿ���һ������Satellite�ĸ������Ƶ��ͽ�Ŀ�����������Satellite����Cable���ԣ�����1��
@param[in] tp_id    ��ǰ���ŵ�Ƶ���ID�����ID�������ݿ��ÿһ��Ƶ������Ψһ��ID����������TS ID����ͬһ�����壬��ע�����֡�<br>
                    ��DVB-S�г���һ�����������ж��ת������������ת�����������ͬ��ʹ�÷�����Щת���������ŵ�������TS ID�ȵ���ȫ�п����ص��������޷���TS IDΨһ����һ��Ƶ�㣬ֻ�������ݿ��TP ID���������ǡ�<br>
                    ����Cable�г���һ���û��������⣬��һ���ط�(������)����TS IDҲ����Ψһ����������һ��Ƶ�㡣

@param[in] service_id   ��ǰ���ڲ��ŵĽ�ĿID�������ֻҪ��ĳ��service��EIT���ݣ���Ҫ����ȷ��service_id��������ʵ������DMX����filterʱ������ȷ��service ID��mask��value������
                    �����������Ƶ�����н�Ŀ��EIT��������Ҫ��other��EIT����service_idû���ô���
@param[in] mode     �ο�epg_eit_mode_e�Ķ��塣ȱʡֵ��EIT_DEFAULT����ʾҪ�����е�ǰƵ���Ŀ��present/following/schedule EIT���ݣ�Ҳ����table IDΪ0x4E��0x50~0x5x������service��                      EIT���ݡ�
*/
void amsepg_on(UINT32 dmx_id, UINT16 sat_id, UINT32 tp_id, UINT16 service_id, epg_eit_mode_e mode, UINT8 ignore_crc);

/*!
@brief ֹͣ��EIT���ݣ����ͷ�DMX��filter��
@details amsepg_off()��amsepg_on()��Ҫ���ʹ�á���������service��EIT���ݵ�ģʽ�£���̨��ʱ�򣬿��Բ��õ���amsepg_off()��amsepg_on()��ֻ��Ҫ�ڻ�Ƶ���ʱ�����һ��amsepg_off()��            amsepg_on()���ɡ����Ǽ�ʹ����ͬƵ�㻻̨֮ǰ��EPGģ��Ҳ��֪���û�����ʲô������������ӻ���ɾ���˽�Ŀ�ȵȣ����������amsepg_off()��amsepg_on()�Ļ���EPGģ�鲻֪����Ŀ���˸���         ��Ҳ�޷���Ӧ���¡���ΪEPGģ�����ڶ���ͨ����amsepg_on()�����ڸ��µ�ǰ�Ľ�Ŀ�б��TP�б����Դ������˵�����ǽ���ÿ�λ�̨��ʱ�򣬶���Ҫ����һ��amsepg_off()��amsepg_on()��
@see amsepg_on
*/
void amsepg_off(void);

/*!
@brief ��EPG���ݿⴴ��View������ȡĳ��service��preset/following/schedule��ĳ��ʱ��ε�Event����������ṩ�˳��õĻ�ȡ����serviceĳ��ʱ��ε�Event�Ľӿڣ��佫����View�ͻ�ȡEvent���������������������ˡ�
@param[in] tp_id ��Ŀ���ڵ�TP ID��
@param[in] service_id   ��Ŀ��Service ID��
@param[in] type ��Ҫ��ȡ��Event�����ͣ��ο�EPG_DB_EVENT_TYPE�Ķ��壬���������������ֻ��ʹ������3�����ͣ�<br>
	- PRESENT_EVENT,
	- FOLLOWING_EVENT,
	- SCHEDULE_EVENT<br>
    ���ú���ֻ�ܻ�ȡService��present/following/schedule���͵�Event��
@param[in] start_dt Event����ʼʱ�����ƣ�����ʱ�䡣
@param[in] end_dt   Event�Ľ���ʱ�����ƣ�����ʱ�䡣
@param[out] num     ����������View��Event��������Ŀ��amsepg_init()��cfg���ò�����max_view_event_count��������ơ�
@param[in] force_update ������Event View��Service��ʱ�������һ����ʱ���Ƿ�ǿ�Ƹ���View��
    - TRUE ǿ�Ƹ���View��
    - FALSE  ������View��<br>
    Ӧ�ò��ڶ�η������øú�����ȡEvent��ʱ�򣬿���service��ʱ���������ȫû�иı䣬��ôEPG���ݿ���Բ���Ҫ����View��ֱ�ӽ�ǰһ�εĽ�����ظ�Ӧ�á�<br>
    ������EPGģ���յ�ĳ��Service���µ�Event��ͨ��callback֪ͨӦ�õ�ʱ��Ӧ��Ҫ�õ���Service��Щ�µ�Event����������������ȫһ��������Ҫͨ����force_update��ΪTRUE��ǿ��EPG���ݿ����View��

@return ����һ��struct EPG_DB_NODE�ṹָ��
@retval ��NULL  ��ʾEPG���ݿ��з���������Event����������View�����ص�һ��Event��
@retval NULL ��ʾû�з���������Event��ViewҲΪ�ա�
*/
struct EPG_DB_NODE *amsepg_get_service_event(UINT32 tp_id, UINT16 service_id, UINT32 type,
							date_time *start_dt, date_time *end_dt,
							INT32 *num,
							BOOL force_update);

/*!
@brief EPG���ݿⴴ������ĳ��������Event View��
@details ������amsepg_create_view()����amsepg_get_service_event()��EPGģ��Ŀǰ����ֻ֧�ִ���1��View����֧��ͬʱ�������View�����View���������ڵײ�EPG Event���ݸ��µ�ʱ��View����ͬ�����¡�
@param[in] filter  �ο�epg_db_filter_t�Ķ���
@param[in] priv ˽�����ݣ�EPG���ݿ��ڴ���View��ʱ�򣬻Ὣ�䴫�ݸ�filter���������Ͷ����ʹ�÷�ʽ������Filter�����ġ�
@return INT32��View Event�ĸ�����ͬ���ܵ�amsepg_init()��cfg���ò�����max_view_event_count��������ơ�
@note EPG���ݿ��ڴ���View��ʱ�򣬻�����洢��ÿһ��Event Node���������˽�����ݴ��ݸ�filter����filter�ж��Ƿ��Ƿ���View���������������TRUE����ʾ����������EPG���ݿ�ͻὫ����뵽View�������򲻻����View��
*/
INT32 amsepg_create_view(epg_db_filter_t filter, void *priv);

/*!
@brief ��ȡView���Event��
@details ��amsepg_get_service_event()��amsepg_create_view()�ɹ�֮�󣬿���ͨ���ú��������ȡView���Event��
@param[in] index    Event��View��λ�ã���0��ʼ��ֱ��View Event����-1��
@return ����һ��EPG_DB_NODE�ṹָ��
@retval ��NULL  ��ʾ��ȡ����Index��Event��
@retval	NULL    ��ʾû�ж�����index��Event������index���Ϸ��ȵ�ԭ��
@note EPG���ݿ��ڲ���һ��ȱʡ��Event Node��buffer��amsepg_get_event()��amsepg_get_service_event()�ὫEvent��EPG���ݿ⿽������buffer��������EPG���ݿ�ײ���������ڸ��¸�Event�Ļ�     ������Ӱ�쵽�ⲿ�û���<br>
    �������bufferֻ��һ�����ⲿ�û��ڻ�ȡ�����Event֮����Ҫ������ʾ��ʹ�����е���Ϣ���ڵ���amsepg_get_event()��ȡ��һ��Event֮��ǰһ��Event�Ͳ������ˡ�<br>
    Present/Following Event����ռ��4k��buffer�����Բ��棻����Schedule Event��ռ������8k��buffer��������Present/Following/Schedule Event���ܲ��档<br>
    amsepg_get_event()��amsepg_get_event2()��Ҫ��amsepg_get_service_event()��amsepg_create_view()�������ʹ�ã���amsepg_get_service_event()��amsepg_create_view()������һ��View֮�󣬿��Է���ʹ��amsepg_get_event()��amsepg_get_event2()��ȡView��ĸ���Event��

*/
struct EPG_DB_NODE *amsepg_get_event(INT32 index);

/*!
@brief ��ȡView���Event��
@details ��amsepg_get_service_event()��amsepg_create_view()�ɹ�֮�󣬿���ͨ���ú��������ȡView���Event��
@param[in] buf  ���ڴ��Event��buffer��<br>
                ���buffer���ⲿ���룬EPG���ݿ�ὫEvent���������buffer������ⲿÿ�δ���buffer���Զ���������ЩEvent�Ϳ��Գ�ʱ�䱣�����ⲿ��
@param[in] len  buffer�Ĵ�С��<br>
                EPG���ݿ��ڽ�Event���������buffer��ʱ�򣬻��ж����buffer�Ĵ�С�Ƿ��á����ȻὫEvent Node�̶����ȵĲ��ֿ������������ż��������������ȵ�Event Name��short detail��extend detail�ȡ����buffer��С�����������û��Event Name��short detail��extend detail����Ϣ��
@param[in] index    Event��View��λ�ã���0��ʼ��ֱ��View Event����-1��
@retval SUCCESS	    �ɹ�
@retval ERR_XXX	    ʧ�ܣ�ViewΪ�գ�����bufferΪNULL��
*/
INT32 amsepg_get_event2(UINT8 *buf, INT32 len, INT32 index);

/*!
@brief ��ȡEvent����ʼʱ�䡣
@details ��EPG Event Node�ṹ�Event��ʱ����MJD Number��ʱ���룬��Ҫ��MJD Numberת��Ϊ�����ա�
@param[in] event    Event Node
@param[out] start_dt    ��ʼʱ�䣬����ṹ����ο�date_time�Ķ��塣
@return ��õ���ʼʱ�䣬Ҳ���Ǵ����start_dt��ַ��
*/
date_time *amsget_event_start_time(struct EPG_DB_NODE *event, date_time *start_dt);

/*!
@brief ��ȡEvent�Ľ���ʱ�䡣
@details ��EPG Event Node�ṹ�Event����ʼʱ����MJD Number��ʱ���롣û�н���ʱ�䣬ֻ�г���ʱ�䣬��Ҫ����ʼʱ����ϳ���ʱ�䣬���ǽ���ʱ�䡣
@param[in] event    Event Node
@param[out] end_dt    ����ʱ�䣬����ṹ����ο�date_time�Ķ��塣
@return ��õĽ���ʱ�䣬Ҳ���Ǵ����end_dt��ַ��
*/
date_time *amsget_event_end_time(struct EPG_DB_NODE *event, date_time *end_dt);

/*!
@brief ��2���ֽڵ�language codeת����3���ֽڵ�ISO 639 language code��
@details
DVB SIһ�㶼��ʹ��3���ֽ�ISO 639 language code����ʾ�������ͣ����硱chi��,��eng���ȵȡ���Event Node�ṹ��Ϊ�˽�ʡһ���ֽڵĴ洢�ռ䣬��3���ֽڵ�ISO 639 language codeת������2���ֽڵ�code��ת����ʽ���£�<br>
 @code Lang2 = ((lang3[0]-��a��)<<10)  |  ( (lang3[1] -��a��)<<5)  |  (lang3[2] -��a��);@endcode <br>
��֮����Ӧ�ò�����Ҫ����ת��Ϊ3���ֽڵ�ISO 639 language code�Ա���ʾ��ת����ʽ���£�<br>
@code
	Lang3[0] = (lang_code2>>10) + 'a';
	Lang3[1] = ((lang_code2>>5) & 0x1F) + 'a';
	Lang3[2] = (lang_code2 & 0x1F) + 'a';
@endcode

@param[in] lang_code2   2���ֽڵ�language code��
@return 3���ֽڵ�ISO 639 language code��
*/
UINT8* lang2tolang3(UINT16 lang_code2);
UINT8* lang2tolang3_2(UINT16 lang_code2, UINT8 *lang3);	//2 byte to 3 byte

/*!
@brief ����Active Service�б�
@details Active Service�ĺ��壬�ο���3�º�EPG_ACTIVE_SERVICE_CNT��˵����ÿ�λ�̨��ʱ�򣬻�����EPG�˵���鿴һ��������Ŀ��EPG��Ϣ��ʱ����Ҫ���øú�������Active Service��
@param[in] service   Active Service�б�
@param[in] cnt      Service������
@return ʵ�����óɹ���Active Service�ĸ��������cnt > EPG_ACTIVE_SERVICE_CNT�������ֻ������ǰ��EPG_ACTIVE_SERVICE_CNT��Active Service��
*/
INT32 amsepg_set_active_service(epg_service_t *service, INT32 cnt);

/*!
@brief ���ĳ��Service�Ƿ���Active Service�б���Ľ�Ŀ��
@details �������һ������callback��ȼ��Service�ǲ���Active Service������ǣ�����Ҫ��Ӧ�ò㷢����Ϣ��
@param[in] tp_id    ��Service���ڵ�TP ID��
@param[in] service_id   Service ID��
@retval TRUE	��Active Service
@retval FALSE   ��Active Service
*/
BOOL  amsepg_check_active_service(UINT32 tp_id, UINT16 service_id);

/*!
@brief ��ӡ��EPGģ���״̬��
@details ����ʹ�õ�buffer�ĵ�ַ�ʹ�С�����TP֧�ָ�����ʵ��TP���������Service������ʵ��Service���������Event������ʵ��Event������memoryʣ���С��������amsepg_init()֮����ܵ��á�
*/
INT32 amsepg_get_module_status(void);

/*!
@brief ��ȡĳ��Service��״̬����Ҫ�Ǹ�Service����section�Ƿ������С�
@param[in] tp_id ��Service���ڵ�TP ID��
@param[in] service_id Service ID��
@retval 1 ��Service������EIT section�������ˡ�
@retval 0 ��Service��EIT section���ݻ�û����ȫ���С�
@retval EPG_SERVICE_NOT_EXIST ��Service�����ڡ�
*/
INT32 amsepg_get_service_status(UINT32 tp_id, UINT16 service_id);


#ifdef __cplusplus
}
#endif



/*!
 * @}
 */

/*!
@}
*/

#endif //__LIB_EPG_H__

