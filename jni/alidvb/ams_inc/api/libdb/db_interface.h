#ifndef __DB_INTERFACE_H__
#define __DB_INTERFACE_H__

#include <adr_basic_types.h>

/*! @addtogroup ALi�м��
 *  @{
 */

/*! @addtogroup AMSDB
 *  @{
 */
 
/************************************************************************************************/
/*amsdb function prototype and structure define*/

/*callback function protorype define*/
typedef BOOL (*amsdb_filter_func)(UINT8 node_type, const UINT8 *node, UINT16 filter_mode, UINT32 param);

typedef INT32 (*amsdb_node_pack_func)(UINT8 node_type, const UINT8*src_node, UINT32 src_len,UINT8*packed_node,UINT32 *packed_len);
typedef INT32 (*amsdb_node_unpack_func)( UINT8 node_type,const UINT8 *src_node,UINT32 src_len, UINT8 *unpack_node, UINT32 unpack_len);

typedef BOOL (*amsdb_node_compare_func)(UINT8 n_type, const void* old_node, const void* new_node);

typedef BOOL (*amsdb_node_find_func)(UINT8 n_type, const void* node, UINT8 *name,UINT32 name_len);

typedef struct
{
	UINT16 max_sat_cnt;
	UINT16 sat_node_len;
	UINT16 max_tp_cnt;
	UINT16 tp_node_len;
	UINT16 max_prog_cnt;
	UINT16 prog_node_len;

	amsdb_filter_func filter_callbak;
	amsdb_node_pack_func pack_callbak;
	amsdb_node_unpack_func unpack_callbak;
	amsdb_node_compare_func compare_callbak;
	amsdb_node_find_func find_callbak;	
}amsdb_param_t;

#define DB_INVALID_POS	0xFFFF


/* create view group flag */
#define VIEW_ALL        0x0100
#define VIEW_SINGLE_SAT     0x0200
#define VIEW_SINGLE_TP      0x0300
#define VIEW_FAV_GROUP      0x0400
#define VIEW_BOUQUIT_ID		0x0500
#define VIEW_CAS		0x0600
#define VIEW_PROVIDER		0x0700
#define VIEW_FAV_GROUP_ALL      0x0800

/* create view service type flag */
#define PROG_RADIO_MODE	    0x00
#define PROG_TV_MODE		    0x01
#define PROG_TVRADIO_MODE	    0x02
#define PROG_DATA_MODE		0x03
#define PROG_NVOD_MODE		0x04
#define PROG_ALL_MODE               0x05
#define PROG_PRIVATE_MODE       0x06
#define PROG_TVRADIODATA_MODE       0x07
#define PROG_TVDATA_MODE		0x08
#define PROG_MOSAIC_MODE		0x09

/*load default db node flag*/
#define DEFAULT_DVBC_PROG			0x01
#define DEFAULT_ALL_PROG			0x02

/* for cal program num */
#define SAT_PROG_NUM			0x01
#define FAV_PROG_NUM			0x02
#define TP_PROG_NUM				0x04
#define NVOD_PROG_NUM			0x08
#define DATA_PROG_NUM			0x10

/* flag for sort program */
enum {
	//sort node in view by key value in ascend order
	DB_SORT_ORDER_ASCEND		= 0x01,
	//sort node in view by key value in descend order
	DB_SORT_ORDER_DESCEND	= 0x02,
};

#ifdef __cplusplus
extern "C"{
#endif

/*amsdb external interface*/

/*!
@brief ����DBԤ�����ݡ�
@details �˺�������DB��Ԥ��node���ݣ���DVBC��˵��ֻ�ǽ���һ������ĸ�node�ڵ㡣
@param[in] set_mode ��Ԥ��node���ݵ�ģʽ��
@param[in] default_addr Ԥ��DB���ݵĵ�ַ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_set_default(UINT8 set_mode,UINT32 default_addr);

/*!
@brief ��ʼ�����ݿ⡣
@details �˺�����ʼ�����ݿ⡣
@param[in] db_addr DB���ⲿ�洢������ʼ��ַ��������������ַ��offsetƫ�ơ�
@param[in] len DB���ⲿ�洢����ռ�Ŀռ䳤�ȡ�<br>
DB5��Ҫ����Сflash�ռ䣺<br>
 - ����������ʹ���ڴ汸��ʱ����Сflash�ռ�Ϊ64KB*3��
 - ���������ղ�ʹ���ڴ汸��ʱ����Сflash�ռ���Ҫ������64KB*2��
@param[in] config DB�����ò�������ϸ�����amsdb_param_t���Ͷ��塣
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_init_db(UINT32 db_addr, UINT32 len, amsdb_param_t *config);

/*!
@brief ����DB���ݡ�
@details �˺�������DB�����е��������ݡ��ظ�Ĭ��Ԥ��ֵ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_clear_db(void);

/*!
@brief ͨ��λ�û�õ�ǰ�ڵ����ݡ�
@details �˺���ͨ��λ�ò�����õ�ǰview�е�һ��node�ڵ����ݡ�
@param[in] type Node�����͡�
@param[in] pos Node�ڵ�ǰview�е�λ�á�
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_get_node_at(UINT8 type ,UINT16 pos,  UINT8* node, INT32 len);

/*!
@brief ͨ��id��õ�ǰ�ڵ����ݡ�
@details �˺���ͨ��id������õ�ǰview�е�һ��node�ڵ����ݡ�
@param[in] type Node�����͡�
@param[in] id Node��id��
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_get_node_byid(UINT8 type ,UINT32 id,  UINT8* node, INT32 len);

/*!
@brief ����ӽڵ����ݡ�
@details �˺�����õ�ǰview��ĳһ�����ڵ���λ��Ϊpos��һ����node�ڵ����ݡ��ú��������ڻ��һ��S_NODE��λ��Ϊpos��ĳ��T_NODE��
@param[in] type Node�����͡�
@param[in] parent_���ڵ�Node��id��
@param[in] pos �ӽڵ��ڸ��ڵ��µ�λ�á�
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_get_node_at2(UINT8 type ,UINT32 parent_id, UINT16 pos, UINT8* node, INT32 len);

/*!
@brief ��ӽڵ����ݡ�
@details �˺������һ��node�ڵ㵽DB��
@param[in] type Node�����͡�
@param[in] parent_id Node�ĸ��ڵ��id��
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_add_node(UINT8 type, UINT32 parent_id,UINT8*node, INT32 len);

/*!
@brief �޸Ľڵ����ݡ�
@details �˺�������id�����޸ĵ�ǰview�е�һ��node�ڵ㡣
@param[in] type Node�����͡�
@param[in] id Node��id��
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_modify_node(UINT8 type, UINT32 id,  UINT8*node, INT32 len);

/*!
@brief ɾ���ڵ����ݡ�
@details �˺�����λ�ò���ɾ����ǰview�е�һ��node�ڵ㡣
@param[in] type Node�����͡�
@param[in] pos Node�ڵ�ǰview�е�λ�á�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_del_node_at(UINT8 type, UINT16 pos);

/*!
@brief ��idɾ���ڵ����ݡ�
@details �˺�����id����ɾ����ǰview�е�һ��node�ڵ㡣
@param[in] type Node�����͡�
@param[in] id Node��id��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_del_node_byid(UINT8 type, UINT32 id);

/*!
@brief ɾ��ȫ���ӽڵ㡣
@details �˺����ڵ�ǰview�а����ڵ�idɾ������ȫ���ӽڵ㡣
@param[in] node_type Node�����͡�
@param[in] parent_type ���ڵ�Node�����͡�
@param[in] parent_id ���ڵ�Node��id��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_del_child(UINT8 node_type, UINT8 parent_type, UINT32 parent_id);

/*!
@brief �ƶ��ڵ����ݡ�
@details �˺����ڵ�ǰview�а�һ���ڵ��ԭ��λ���ƶ���ָ����λ�á�
@param[in] type �ڵ�Node�����͡�
@param[in] dest_pos �ýڵ��Ŀ��λ�á�
@param[in] src_pos �ýڵ�ԭ����λ�á�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_move_node(UINT8 type, UINT16 dest_pos,UINT16 src_pos);

/*!
@brief ��ȡ�ڵ�λ�á�
@details �˺�����id��������view�д�node�ڵ��λ�á�
@param[in] type �ڵ�Node�����͡�
@param[in] id Node��id��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
UINT16 amsdb_get_node_pos(UINT8 type, UINT32 id);

/*!
@brief ���ҽڵ�������
@details �˺����ڵ�ǰview�в��ҷ���ĳ�������Ľڵ�ĸ�����
@param[in] type �ڵ�Node�����͡�
@param[in] filter_mode ��Ϊ2���֣����ֽڱ�ʾ�Խڵ��groupҪ�󣬵��ֽڱ�ʾ�Խڵ������Ҫ��
@param[in] param ��Ӧfilter_mode�Ĳ�����
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
UINT16 amsdb_get_node_cnt(UINT8 type, UINT16 filter_mode, UINT32 param);

/*!
@brief ����view��
@details �˺�������ĳ�����͵Ľڵ㰴���û����ƵĹ��˺�������һ���Ӽ�����Ϊview�������Ĳ������������view��
@param[in] type �ڵ�Node�����͡�
@param[in] create_mode ����view��ģʽ����Ϊ2���֣����ֽڱ�ʾ�Խڵ��groupҪ�󣬵��ֽڱ�ʾ�Խڵ������Ҫ�󡣾���ʵ�ֹ��˵ĺ�����Ӧ�ó���Ļص�����ʵ�֡�
@param[in] param ��Ӧ��viewģʽ�Ĳ�����
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_create_view(UINT8 type, UINT16 create_mode, UINT32 param);

/*!
@brief ��õ�ǰview��ģʽ�Ͳ�����
@details �˺�����õ�ǰview��ģʽ�Ͳ������Ա㱣���ģʽ�Ͳ�����Ȼ�󴴽��µ�view����һЩ������֮�������������ģʽ�Ͳ����ظ�֮ǰ��view��
@param[in] type �ڵ�Node�����͡�
@param[in] filter_mode ���淵�ص�ǰview��ģʽ��bufָ�롣
@param[in] param ���淵�ص�ǰview��ģʽ������bufָ�롣
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_get_view_param(UINT8 type, UINT16 *filter_mode, UINT32 *param);

/*!
@brief ������ͬ�ڵ㡣
@details �˺����ڵ�ǰview�в����Ƿ����һ����ͬ�Ľڵ㡣
@param[in] type �ڵ�Node�����͡�
@param[in] node_id Node��id��
@param[in] node ָ��ýڵ����ݵ�ָ�룬���ݽڵ����ݾ��������ж��Ƿ���ͬ�ĺ�����Ӧ�ó���Ļص�����ʵ�֡�
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_lookup_node(UINT8 type, UINT32 node_id, UINT8 *node, UINT32 len);

/*!
@brief ����DB���ݡ�
@details �˺�����֮ǰ�Ե�ǰview��node���������Ĳ���������ⲿ�洢���������ػ�ʱ��node���ݲ��ᶪʧ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_update_data(void);

/*!
@brief ���DB�����Ƿ���ġ�
@details �˺������ĳ�����͵�node�Ƿ����˲��������޸ģ�ɾ������ӣ�����ȣ�������򷵻�TRUE��Ӧ�ÿ��Ե��ô˺���������Ƿ��ĳ�����͵�node���˲�����Ȼ������Ƿ�Ҫ�ѸĶ����浽flash����
@param[in] type Node���͡�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
BOOL amsdb_check_node_modify(UINT8 type);

/*!
@brief ���ýڵ��־��
@details �˺����ڵ�ǰview�ж�ĳ��λ�õĽڵ�����flag��־��
@param[in] type �ڵ�Node�����͡�
@param[in] pos �ýڵ��ڵ�ǰview�е�λ�á�
@param[in] flag �ض���flag����V_NODE_DEL_FLAG, V_NODE_FIND_FLAG�ȡ�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_set_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief ����ڵ��־��
@details �˺��������ǰview�ж�ĳ��λ�õĽڵ��flag��־��
@param[in] type �ڵ�Node�����͡�
@param[in] pos �ýڵ��ڵ�ǰview�е�λ�á�
@param[in] flag �ض���flag����V_NODE_DEL_FLAG, V_NODE_FIND_FLAG�ȡ�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_clear_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief ���ڵ��־��
@details �˺�����鵱ǰview�ж�ĳ��λ��node�Ƿ��������ض���flag��־��
@param[in] type �ڵ�Node�����͡�
@param[in] pos �ýڵ��ڵ�ǰview�е�λ�á�
@param[in] flag �ض���flag����V_NODE_DEL_FLAG, V_NODE_FIND_FLAG�ȡ�
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
BOOL amsdb_check_node_flag(UINT8 type, UINT16 pos, UINT16 flag);

/*!
@brief ���ҽڵ㡣
@details �˺����ڵ�ǰview�а���ĳ���ַ������ҷ��ϵĽڵ㣬�����������
@param[in] type �ڵ�Node�����͡�
@param[in] str ָ��һ���ַ�����ָ�롣����ڵ����ݵ��ĸ���͸��ַ��������Ƚ���Ӧ�ó���ʵ�ֵ�find�ص�������������
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
UINT16 amsdb_find_node(UINT8 type, char *str, UINT8*node, UINT32 len);

/*!
@brief ����λ�û�ýڵ����ݡ�
@details �˺����ڲ��ҵ��ڵ�Ļ����ϣ�����λ�ò�����ýڵ����ݡ�
@param[in] type �ڵ�Node�����͡�
@param[in] pos ���ҵ��Ľڵ�λ�ã������ҵ��ĵڼ����ڵ㡣
@param[in] node �洢node���ݵ�buffer��ַ��
@param[in] len �洢node���ݵ�buffer��С����byteΪ��λ��
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_get_find_node(UINT8 type, UINT16 pos, UINT8 *node, UINT32 len);

/*!
@brief ����ڵ����ݡ�
@details �˺����Ե�ǰview�еĽڵ㰴��ĳ���ؼ��ֽ�������
@param[in] type �ڵ�Node�����͡�
@param[in] sort_mode ��������͡�
@param[in] key ָ������ؼ��ֵ������ָ�롣��������Ҫ���ÿ���ڵ�Ĺؼ��֣����һ���ؼ������鴫�롣
@param[in] cnt ����ؼ��ֵĸ���������view�нڵ�ĸ�����
@retval DB_SUCCESS �ɹ�
@retval DBERR_XXX ʧ��
*/
INT32 amsdb_sort_node(UINT8 type, UINT8 sort_mode, UINT32 *key, INT32 cnt);

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

