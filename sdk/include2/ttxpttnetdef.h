#ifndef _TTX_PTT_NET_DEF_H_
#define _TTX_PTT_NET_DEF_H_

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

#ifdef WIN32

	#ifdef LIBTTXPTT_EXPORTS
	#define LIBTTXPTT_API __declspec(dllexport)
	#else
	#define LIBTTXPTT_API __declspec(dllimport)
	#endif

#else

	#define LIBTTXPTT_API

#endif

#include "ttxdvrnetdef.h"
#include "ttxpttnettype.h"

#define TTX_PTT_VERSION 		"V6.1.5 20180613"

#define TTX_PTT_READ_DATA_TYPE_FINISH			1	//���ݶ�ȡ����
#define TTX_PTT_READ_DATA_TYPE_FAILED			2	//���ݶ�ȡʧ��
#define TTX_PTT_READ_DATA_TYPE_GROUP_INFO		3	//Ⱥ����Ϣ
#define TTX_PTT_READ_DATA_TYPE_GROUP_MEMBER		4	//Ⱥ���Ա
#define TTX_PTT_READ_DATA_TYPE_AUDIO_FILE_BUFFER	5	//��Ƶ�ļ���������


#pragma pack(4)

typedef struct _tagTTXPttGroupInfo
{
	int nGroupID;		//����ID
	char szName[64];	//��������
	int nCompanyID;		//�Ǹ���˾��Ⱥ��
	char cType;			//����1��ͨС�飬2��ʱС��
	char cReserve[3];	//�����ֶ�
	int nCreater;		//������
	char szRemarks[64];	//��ע��Ϣ
}TTXPttGroupInfo_S, *LPTTXPttGroupInfo_S;

typedef struct _tagTTXPttGroupMember
{
	int nGroupID;		//�����Ǹ�Ⱥ��
	int nTerminalID;	//��ԱID
	char szDevIDNO[64];	//�豸��ţ����Ϊ����Ա����Ϊ����Ա���˺ţ�
	char szName[64];	//��Ա����
	char bDefault;		//�Ƿ�ΪĬ��Ⱥ��
	char cLevel;		//����
	char cTerminaType;	//�ն�����, 4��Ա��5�����û���0Ϊ����
	char cReserve[9];	//�����ֶ�
}TTXPttGroupMember_S, *LPTTXPttGroupMember_S;

typedef struct _tagTTXPttAudioFileBuffer
{
	const char* pBuffer;
	int	nBufLen;
	char cReserve[32];
}TTXPttAudioFileBuffer_S, *LPTTXPttAudioFileBuffer_S;


#pragma pack()

//��ȡ��Ϣ�����ݻص�����ȡȺ���б��Ⱥ���Աʱʹ�ô˻ص�
//TTXPTT_Read ��ͷ�ĺ���ʹ�ô˻ص�
//@nDataType	TTX_PTT_READ_DATA_TYPE_GROUP_INFO ʱpData = TTXPttGroupInfo_S
//				TTX_PTT_READ_DATA_TYPE_GROUP_MEMBER ʱpData = TTXPttGroupMember_S
//				TTX_PTT_READ_DATA_TYPE_FINISH��ȡ����,���Ե���TTXPTT_CloseReadHandle�رջ�ȡ����
//				TTX_PTT_READ_DATA_TYPE_FAILED��ȡʧ��,���Ե���TTXPTT_CloseReadHandle�رջ�ȡ����
//@pUsr		�û��Զ�������
typedef void(* TTXPTTPfnReadInformationCB)(int nDataType, void* pData, void* pUsr);

/**
 * @Description:����������
 * @Author: afu	2017-08-30
 */

class LIBTTXPTT_API CTTXPttWork
{
public:
	CTTXPttWork() 
	{
		m_nTerminalID = 0;
		m_nPttHeartInterval = 10;
	}
	virtual ~CTTXPttWork(){}

public:
	//
	//ptt ��Ϣ֪ͨ
	//@nMessage: ��Ϣ����,��ͬ����Ϣ��������һ�����������Ϣ����
	//@nParam1: ��Ϣ����1
	//@nParam2: ��Ϣ����2
	//@pParam3: ��Ϣ����3
	//virtual void DoPttMsg(int nMessage, int nParam1, int nParam2, void* pParam3) {}

	//��¼��Ϣ
	//@bSuc: ��¼�ɹ�����ʧ��
	//@nGroupID����Ӧ�ĵ�ǰ��Ⱥ��ID
	//@nTerminalID: ��Ϊ��¼�ɹ�ʱ, Ϊ���ն������ID
	//@nError: ��ʾ����ԭ�򣬵�Ϊ����ʱ��ЧTTX_PTT_ERR_PASSWORD\TTX_PTT_ERR_NETWORK\TTX_PTT_ERR_ALREADY_LOGIN
	virtual void DoLogin(bool bSuc, int nGroupID, int nTerminalID, int nError) {}


	//���յ�������Ƶ
	//@nTerminalID: �ն�ID����ʾ�Ǹ��ն��ڽ���
	//@bStart: true��ʾ��ʼ,false��ʾֹͣ
	virtual void DoTalk(int nGroupID, int nTerminalID, bool bStart) {}

	//���յ�������Ƶ
	//@nGroupID: Ⱥ��ID
	//@nTerminalID: �ն�ID
	//@nAudioIndex: ��Ƶ������ÿ�ν���ʱ����0��ʼ
	//@pAudio: ��Ƶ����
	//@nLength: ��Ƶ����
	virtual void DoRecvAudio(int nGroupID, int nTerminalID, int nAudioIndex, const char* pAudio, int nLength, _u64long u64Stamp) {}

	//�л�Ⱥ��(��ǿ������ǿ��)
	//@nGroupID: Ⱥ��ID
	//@nTerminalID: �ն�ID������ն�IDΪ0��ʾ���ն��л�Ⱥ��
	//@nEnter: ��������뿪
	//@bForce: 1Ϊǿ��ǿ��0Ϊ�����뿪
	virtual void DoSwitchGroup(int nGroupID, int nTerminalID, int nEnter, int bForce) {}
	
	//Ⱥ����Ϣ����
	//@nGroupID: Ⱥ��ID
	//@szUtf8Name: Ⱥ������
	virtual void DoUpdateGroupInfo(int nGroupID, const char* szUtf8Name, const char* szAnsiName) {}

	//Ⱥ���Ա�����仯����Ҫ����ȥ��̨��ȡȺ���Ա��Ϣ
	//���Ⱥ��ID�����ڣ�����Ҫȥ�������ϰ�Ⱥ����Ϣ����ˢ�»�����������ʱȺ��ʱ�������������
	//@nGroupID: Ⱥ��ID
	virtual void DoUpdateGroupMember(int nGroupID) {}

	//���û���ӵ�ĳ��С�� ����Ҫ����ȥ��̨��ȡȺ���Ա��Ϣ
	//@nGroupID: Ⱥ��ID
	//@bTempGroup: �Ƿ�Ϊ��ʱȺ��
	virtual void DoAppendToGroup(int nGroupID, int bTempGroup) {}

	//��ЭͬС�����Ƴ�����Ⱥ����ɾ��
	//@nGroupID: Ⱥ��ID
	//@bTempGroup: �Ƿ�Ϊ��ʱȺ��
	//@nTerminalID: �Ǹ��ն�ɾ����Ⱥ��
	virtual void DoRemoveFromGroup(int nGroupID, int bTempGroup, int nTerminalID) {}

	//���յ�������Ϣ
	//@nGroupID: Ϊ0ʱ��ʾ1��1������Ϣ����Ϊ0ʱ����ʾ��ĳ��Ⱥ����û�������Ϣ
	//@nTerminalID: ��Ⱥ��IDΪ0ʱ��Ч����ʾ�����ն˷���������Ϣ
	//@nType: ��ʱ��Ч
	//@nSendTerID: ��ʾ�������ֵ��û�
	//@szUtf8Text: ��������
	virtual void DoTts(int nGroupID, int nTerminalID, int nType, int nSendTerID, const char* szUtf8Text) {}

	//���յ��ļ���Ŀǰֻ֧����Ƶ�ļ�
	//@pTm������ʱ��
	//@nTotalSecond���ļ�ʱ��
	//@nGroupID��Ϊ0ʱ��ʾ1��1������Ϣ����Ϊ0ʱ����ʾ��ĳ��Ⱥ����û�������Ϣ
	//@nTerminalID����ʾ�������ֵ��û�
	//@nType���ļ����ͣ�4��TTX_FILE_AUDIO����ʾ��Ƶ�ļ�
	//@nSendTerID��������ID
	//@szUrl���ļ�����
	virtual void DoFile(const struct tm* pTm, int nTotalSecond, int nGroupID, int nTerminalID, int nType, int nSendTerID, const char* szUrl) {}

public:
	int 	GetTerminalID() {		return m_nTerminalID;	}
	
	//��ȡptt�������(��)
	int		GetPttHeartInterval() {	return m_nPttHeartInterval;	}
	//����ptt�������
	void	SetPttHeartInterval(int nSecond) {	m_nPttHeartInterval = nSecond;	}
	
protected:
	int		m_nTerminalID;	//���ն������ID
	int				m_nPttHeartInterval;	//�������ͼ��, ��λ��
};

#endif

