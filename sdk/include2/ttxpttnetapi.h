#ifndef _TTX_PTT_NET_API_H_
#define _TTX_PTT_NET_API_H_

#include "ttxdvrnetdef.h"
#include "ttxpttnetdef.h"

/******************************************************************************
  Author        : afu
  Created       : 2017/08/30
  Last Modified :
  Description   : PTT��Ⱥ�Խ��ӿڶ���
  History       :
	  1.	Date        : 2017/08/30
		Author      : afu
		Modification: Created file
		
******************************************************************************/

/*
* ע������
*   
* 	1��ptt��Ⱥ�Խ�����dvrnet�ϲ�һ��ʹ�ã����ܵ���ʹ�á���dvrnet��Makefile���� _TTX_ENABLE_PTT_ �꣬CFLAGS += -D _TTX_ENABLE_PTT_����Ϊ���Ӽ�Ⱥ�Խ��Ĺ���
*/

/*
1��	�汾��	6.1.0.1
		���ڣ�	20170830	
		�޸ģ�	����
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @Description: ��������㣬�˽ӿڱ�����TTXPTT_StartWorkǰ����
 * @param: �ϲ�Ӧ����Ҫ��CTTXPttWork�̳����࣬ʵ����Ӧ�Ľӿ�
 * @return: 0��ʾ�ɹ� 
 * @Author: afu	2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SetPttAdapter(CTTXPttWork* pPttWork);


//��������ֹͣ����
LIBTTXPTT_API int TTXPTT_StartWork();
LIBTTXPTT_API int TTXPTT_StopWork();


/**
 * @Description:�ж��Ƿ����ӳɹ�
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_IsLoginSuc();

/**
 * @Description:��������ʱʱ��
 * @param: lMinSecond���룬Ĭ����5000����
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SetRequireTimeout(long lMinSecond);

/**
 * @Description:���󽲻�Ȩ��, TTXPTT_RequestTalk��sdk�����InitAudioReader��ȡ��Ƶ����
			InitAudioReader�ӿڿ��Բ�ʵ�֣���ʱ�ϲ�Ҫ����TTXPTT_SendAudio������Ƶ����
 * @param:	bTalk: �Ƿ񽲻���trueΪ���󽲻�Ȩ�ޣ�falseΪ�ͷŽ���Ȩ��
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ��
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_RequestTalk(bool bTalk);

/**
 * @Description:������Ƶ���ݣ���TTXPTT_RequestTalk���ȡ������Ȩ���ٵ��ò���Ч
			������Ƶ���ϲ������ַ�ʽ
				a������TTXPTT_SendAudio, b������InitAudioReader�ӿڽ��з�������
					TTXPTT_RequestTalk��sdk�����InitAudioReader��ȡ��Ƶ����
 * @param: 	pAudio: ��Ƶ����
 			nLength: ���ݳ���
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SendAudio(const char* pAudio, int nLength, _u64long u64Stamp);

/**
 * @Description:����TTS
 * @param: 	nGroupID: Ⱥ��ID(Ϊ0ʱ����ʾ��ĳ���ն˷�������)
 			nTerminalID: �ն�ID��Ⱥ��Ϊ0ʱ��Ч����ʾ��ĳ���ն˷�������
			nType: ���ͣ���ʱ��Ч��
			szUtf8Text��������Ϣ, ���Ȳ�����512
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SendTts(int nGroupID, int nTerminalID, int nType, const char* szUtf8Text);

/**
 * @Description:�л�Ⱥ�飬ǿ����ǿ��
 * @param: nGroupID: Ⱥ��ID
 * @param: nTerminalID:�ն�ID�����nTerminalIDΪ0��ʾ���Լ�����
 * @param: nEnter    1Ϊ����Ⱥ��(ǿ��), 0Ϊ�뿪Ⱥ��(ǿ��)
 				nTerminalIDΪ0ʱΪ�Լ��л�Ⱥ��(ֻ�н���ĳ��Ⱥ�飬û���뿪ĳ��Ⱥ��)
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ��
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_SwitchGroup(int nGroupID, int nTerminalID, int nEnter);

/**
 * @Description: ������ʱȺ�飬���ýӿ����û����뵽��ʱȺ����
 * @param: szName: Ⱥ������,��ʱ��Ч
 * @param: bNameUtf8 =1Ϊutf��ʽ�����ƣ�=0Ϊansi
 * @param: nTerminalID: �ն�ID, ��ĳ���ն�һ�𴴽�Ⱥ�飬����
 * @param: nGroupID: ������ʱȺ��ID
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ��
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_CreateTempGroup(const char* szName, int bNameUtf8, int nTerminalID, int& nGroupID);

/**
 * @Description: ����Ⱥ���Ա�����ýӿ����û����뵽��ʱȺ����
 * @param: nGroupID: Ⱥ��ID
 * @param: pArrTerminalID: ��ӳ�Ա��Ⱥ���У�������Ա�л�����Ⱥ��
 * @param: nTerminalCount: �ն���Ŀ
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_AddTempGroupMember(int nGroupID, int* pArrTerminalID, int nTerminalCount);

/**
 * @Description: ɾ��Ⱥ���Ա�����ýӿ����û����뵽��ʱȺ����
 * @param: nGroupID: Ⱥ��ID
 * @param: pArrTerminalID: ��ӳ�Ա��Ⱥ���У�������Ա�л�����Ⱥ��
 * @param: nTerminalCount: �ն���Ŀ
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_DelTempGroupMember(int nGroupID, int* pArrTerminalID, int nTerminalCount);

/**
 * @Description: �Ƴ���ʱȺ��
 * @param: nGroupID: Ⱥ��ID
 * @return: 0��ʾ�ɹ����ӿ�ͬ�����أ����2�볬ʱ
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_RemoveTempGroup(int nGroupID);

/**
 * @Description:��ȡ�û���Ⱥ���б�, �첽�ӿ�
 * @  �� TTXPTT_ReadGroupList�����ݵȴ�TTXPTTPfnReadInformationCB���أ���TTXPTT_CloseReadHandle
 * @param: lpReadHandle���ض�ȡ��������TTXPTT_CloseReadHandleʹ��
 * @param: pUsr: �û��Զ�������
 * @param: pfnReadInfoCB: �ص�����
 * @return: 0��ʾ�ɹ�
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_ReadGroupList(long* lpReadHandle, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description:��ȡȺ���Ա�б�����һ�λ�ȡ���Ⱥ��ĳ�Ա
 * @param: lpReadHandle���ض�ȡ��������TTXPTT_CloseReadHandleʹ��
 * @param: pArrGroupIDȺ��ID�б�
 * @param: nGroupCountȺ����Ŀ
 * @param: pUsr: �û��Զ�������
 * @param: pfnReadInfoCB: �ص�����
 * @return: 0��ʾ�ɹ�
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_ReadGroupMember(long* lpReadHandle, int* pArrGroupID, int nGroupCount, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description: 
 * @  �� TTXPTT_UploadFile�����ݵȴ�TTXPTTPfnReadInformationCB���أ���TTXPTT_CloseReadHandle
 * @param: lpReadHandle���ض�ȡ��������TTXPTT_CloseReadHandleʹ��
 * @param: nGroupID��ʾ��ĳ��Ⱥ����û�����Ƶ�ļ�����Ϊ0ʱnTerminalID��Ч��ʾ��ĳ���ն˷�
 * @param: nFileType�ļ�����  TTX_FILE_AUDIO(4)��ʾ��Ƶ�ļ�
 * @param: szFile: �ļ�����·��
 * @param: nTotalSecond: �ļ���ʱ��
 * @param: pUsr: �û��Զ�������
 * @param: pfnReadInfoCB: �ص�����
 * @return: 0��ʾ�ɹ�
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_UploadFile(long* lpReadHandle, int nGroupID, int nTerminalID, int nFileType, const char* szFile, int nTotalSecond, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);
//�ϴ���Ƶ������
LIBTTXPTT_API int TTXPTT_UploadBuffer(long* lpReadHandle, int nGroupID, int nTerminalID, int nFileType, const char* pBuffer, int nBufLen, int nTotalSecond, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description: 
 * @  �� TTXPTT_DownFile�����ݵȴ�TTXPTTPfnReadInformationCB���أ���TTXPTT_CloseReadHandle
 * @param: lpReadHandle���ض�ȡ��������TTXPTT_CloseReadHandleʹ��
 * @param: szUrl�ļ�·����ͨ��CTTXPttWork��DoFile�ӿڷ���
 * @param: szSavePath: �ļ��Ĵ洢·��
 * @param: pUsr: �û��Զ�������
 * @param: pfnReadInfoCB: �ص�����
 * @return: 0��ʾ�ɹ�
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_DownFile(long* lpReadHandle, const char* szUrl, const char* szSavePath, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);
//������Ƶ��������
//ͨ���ص���nDataType == TTX_PTT_READ_DATA_TYPE_AUDIO_FILE_BUFFER �� (TTXPttAudioFileBuffer_S*)pData����
LIBTTXPTT_API int TTXPTT_DownBuffer(long* lpReadHandle, const char* szUrl, void* pUsr, TTXPTTPfnReadInformationCB pfnReadInfoCB);

/**
 * @Description:�رջ�ȡ����
 * @param: lReadHandle: �û���ȡ������
 * @return: 0��ʾ�ɹ�
 * @Author: afu 2017-08-30
 */
LIBTTXPTT_API int TTXPTT_CloseReadHandle(long lReadHandle);

/**
 * @Description:��ȡ���ٺ���������
 * @return: ����ʱ���(����) 
 * @Author: 
 */
LIBTTXPTT_API _u64long TTXPTT_GetTimeNoRecvData();


#ifdef __cplusplus
}
#endif 


#endif

