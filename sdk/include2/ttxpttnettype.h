#ifndef _TTX_PTT_NET_TYPE_H_
#define _TTX_PTT_NET_TYPE_H_

/******************************************************************************
  Author        : afu
  Created       : 2017/08/30
  Last Modified :
  Description   : ��Ⱥ�Խ������ͨ����Ϣ����
  History       :
	  1.	Date        : 2017/08/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/


#define TTX_PTT_GROUP_TYPE_NORMAL					1	//��ͨС��
#define TTX_PTT_GROUP_TYPE_TEMPORARY				2	//��ʱС��

#define TTX_PTT_STATUS_LEAVE						0	//�����ڵ�ǰ��С����
#define TTX_PTT_STATUS_ENTER						1	//���ڵ�ǰС����

#define TTX_PTT_TALK_MAX_SECOND						30	//ÿ�ν����30��
#define TTX_PTT_TALK_MAX_MIN_SECOND					30000	//ÿ�ν����30��

//PTT��صĽṹ�嶨��
//_T_��ʾ�豸�ϱ��ģ�ͨ��MDVRPTT_RegPttMessageCB�ӿڷ��ص�
#define TTX_PTT_MESSAGE_T_CHECK_PWD					101	//У�����룬inParam��szParam1Ϊmd5ֵ������, outParam������
#define TTX_PTT_MESSAGE_T_LOGIN						102	//�ն˵�¼��inParam������, outParam, szParam1�����û�������IP(IP1|IP2|IP3)
//nParam1����Ⱥ��ID, nParam2�����ն�ID, nParam3�����û��������˿�
#define TTX_PTT_MESSAGE_T_LOGOUT						103	//�ն�ע����inParam������, outParam������
#define TTX_PTT_MESSAGE_T_REQUIRE_TALK				104	//����Խ���inParam��nParam1=0��ʾֹͣ��1��ʾ��ʼ����, nParam2��ʾ�ն�ID, outParam������
#define TTX_PTT_MESSAGE_T_SWITCH_GROUP				105	//�л�Ⱥ��, inParam��nParam1��ʾȺ��ID, nParam2��ʾ�ն�ID, nParam3��ʾ��������뿪 
//nTerminalIDΪ0ʱΪ�Լ��л�Ⱥ��(ֻ�н���ĳ��Ⱥ�飬û���뿪ĳ��Ⱥ��)
#define TTX_PTT_MESSAGE_T_CREATE_TEMP_GROUP			106	//������ʱȺ�飬inParam��nParam1��ʾ�ն�ID����ĳ���ն˽�����ʱȺ�飩,nParam2��ʾȺ�������Ƿ�Ϊutf8��ʽ,szParam1��ʱȺ������֣�outParam��nParam1��ʾȺ��ID
#define TTX_PTT_MESSAGE_T_ADD_TEMP_GROUP_NEMBER		107	//�����ʱС���Ա��inParam��szParam1Ϊ�ն�ID�б� 1234|1235��, ���128��Ⱥ�飬nParam1��ʾȺ��ID, nParam2��ʾ�ն���Ŀ
#define TTX_PTT_MESSAGE_T_DEL_TEMP_GROUP_NEMBER		108	//�Ƴ���ʱС���Ա��inParam��szParam1Ϊ�ն�ID�б� 1234|1235��, ���128��Ⱥ�飬nParam1��ʾȺ��ID, nParam2��ʾ�ն���Ŀ
#define TTX_PTT_MESSAGE_T_REMOVE_TEMP_GROUP			109	//�Ƴ���ʱȺ�飬inParam��nParam1ΪȺ��ID
#define TTX_PTT_MESSAGE_T_TALK_AUDIO				110	//���յ��������ݣ�inParam��szParam1Ϊ��Ƶ���ݣ�nParam1Ϊ��Ƶ֡��ţ�nParam2Ϊ���ݳ���, outParam������
#define TTX_PTT_MESSAGE_T_TTS						111	//����TTS���֣�inParam��szParam1Ϊ�������ݣ�nParam1Ⱥ��ID(��Ϊ0��ʾ��ĳ��Ⱥ����Ϣ��Ϣ),nParam2�ն�id(nParam1Ϊ0ʱ��Ч����ʾ1��1����������Ϣ),nParam3����

//_S_��ʾ�������·��ģ�ͨ��MDVRPTT_SendPttMessage�·����豸
#define TTX_PTT_MESSAGE_S_TALK_EVENT				201	//֪ͨĳ���û������¼���inParam��nParam1��ʾȺ��ID��nParam2��ʾ�ն�ID��nParam3=0��ʾֹͣ��1��ʾ��ʼ����, outParam������
#define TTX_PTT_MESSAGE_S_SWITCH_GROUP				202	//�л�Ⱥ��, inParam��nParam1��ʾȺ��ID, nParam2��ʾ�ն�ID, nParam3��ʾ��������뿪, nParam4=1ǿ��ǿ���0�����뿪  
#define TTX_PTT_MESSAGE_S_TALK_AUDIO				203	//���յ��������ݣ�inParam��szParam1Ϊ��Ƶ���ݣ�nParam1Ϊ��Ƶ֡��ţ�nParam2Ϊ���ݳ���, nParam3ΪȺ��ID, nParam4Ϊ�ն�ID, outParam������
#define TTX_PTT_MESSAGE_S_UPDATE_GROUP_INFO			204	//ЭͬС����Ϣ�������ƣ������仯��inParam��nParam1ΪȺ��ID��szParam1Ϊutf8Ⱥ�����ƣ�szParam2ΪansiȺ������, outParam������
#define TTX_PTT_MESSAGE_S_UPDATE_GROUP_MEMBER		205	//Эͬ��Ա�仯�����ӡ�ɾ����Ա����inParam��nParam1ΪȺ��ID, outParam������
#define TTX_PTT_MESSAGE_S_APPEND_TO_GROUP			206	//�û���ӵ�ЭͬС�飬inParam��nParam1ΪȺ��ID, nParam2��ʾ�Ƿ�Ϊ��ʱȺ��
#define TTX_PTT_MESSAGE_S_REMOVE_FROM_GROUP			207	//��ЭͬС�����Ƴ���inParam��nParam1ΪȺ��ID, nParam2��ʾΪ��ʱȺ�飬nParam3��ʾ�������ն�id
#define TTX_PTT_MESSAGE_S_TTS						208	//����TTS���֣�inParam��szParam1Ϊ�������ݣ�nParam1Ⱥ��ID(��Ϊ0��ʾ��ĳ��Ⱥ����Ϣ��Ϣ),nParam2�ն�id(nParam1Ϊ0ʱ��Ч����ʾ1��1����������Ϣ),nParam3����
#define TTX_PTT_MESSAGE_S_UPLOAD_FILE				209	//�ϴ��ļ���inParam��szParam1Ϊurl��ַ��nParam1Ⱥ��ID(��Ϊ0��ʾ��ĳ��Ⱥ����Ϣ��Ϣ),nParam2�ն�id(nParam1Ϊ0ʱ��Ч����ʾ1��1����������Ϣ),nParam3����

#define TTX_PTT_SUC								0	//�ɹ�
#define TTX_PTT_ERR_PASSWORD					200	//�������
#define TTX_PTT_ERR_ALREADY_LOGIN				201	//�Ѿ���¼
#define TTX_PTT_ERR_NETWORK						202	//�������
#define TTX_PTT_ERR_NO_TALK_RIGHT				203	//δȡ�ý���Ȩ
#define TTX_PTT_ERR_OTHER_TALKING				204	//�����û����ڽ���
#define TTX_PTT_ERR_GROUP_IDLE					205	//û�д���ĳ��Ⱥ��(����״̬)
#define TTX_PTT_ERR_GROUP_NO_EXIST				206	//Ⱥ�鲻����
#define TTX_PTT_ERR_NO_GROUP_MEMBER				207	//��Ⱥ���Ա
#define TTX_PTT_ERR_TEMP_GROUP_EXIST			208	//�Ѿ�������ʱС�飨�û�ͬʱֻ�ܽ���һ����ʱȺ�飩
#define TTX_PTT_ERR_NO_TEMP_GROUP				209	//����ʱȺ�飨Ŀǰֻ����ʱȺ�������ӳ�Ա��
#define TTX_PTT_ERR_NO_RIGHT					210	//��Ȩ��
#define TTX_PTT_ERR_DATABASE					211	//�������ݿ�
#define TTX_PTT_ERR_UNKOWN						212	//δ֪����
#define TTX_PTT_ERR_OFFLINE						213	//����״̬
#define TTX_PTT_ERR_TERMINAL_NO_EXIST			214	//�ն˲�����
#define TTX_PTT_ERR_TERMINAL_OFFLINE			215	//�ն˲�����
#define TTX_PTT_ERR_TERMINAL_TALKING			216	//�ն����ڽ�����ǿ������ǿ���ʧ��
#define TTX_PTT_ERR_IN_TEMP_GROUP				217	//�ն˴�����ʱȺ����

//PTT��صĽṹ�嶨��
typedef struct _tagPTTMsgParam
{
	int		nParam[8];		//����
	char	szParam1[2048];	//����1
	char	szParam2[512];	//����2
	char	szParam3[512];	//����2
	char	szParam4[1024];	//����2
}PTTMsgParam_S;


#endif

