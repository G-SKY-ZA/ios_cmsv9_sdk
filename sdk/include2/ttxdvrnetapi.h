#ifndef _TTX_DVR_NET_API_H_
#define _TTX_DVR_NET_API_H_

#include "ttxdvrnetdef.h"
#include "ttxdvralarmdef.h"
#include "ttxdvrtransparentdef.h"




/******************************************************************************
  Author        : afu
  Created       : 2011/06/30
  Last Modified :
  Description   : ����ģ��ӿڶ���
  History       :
	  1.	Date        : 2011/06/30
		Author      : afu
		Modification: Created file
		
******************************************************************************/

/*
* ע������
* 	1�����ڸ�ʽ��SD�����������TTXNET_SetDataPath ��GPS��������Ϣ���浽SD���ϣ�
		��ôִ�и�ʽ��SD��������ҪTTXNET_StopWork ֹͣ��������
	2�����齫��־Ŀ¼���õ�SD���ϣ����ҷ��Ͱ汾��������־����
		TTXNET_SetLogParam(false, false, 0, "/mnt/sd/", 10);
	3������������Ŀ¼���õ�SD����
		TTXNET_SetDataPath
*/

/*
1��	�汾��	6.1.0.1	
	���ڣ�	20130517	
	�޸ģ�
2��	�汾��	6.1.0.2	
	���ڣ�	20130520	
	�޸ģ�	1����Socket���ͻ������Ϊ64K
				2��TTXPfnAVEncoderCB ���ӷ���ֵTTX_NET_ERR_BUF_FULL��֪ͨ�������ֶ���ý�����ݵ����
				3���Է����ڴ������Ӧ����������ַ����ڴ����������ʹ���ڴ�����
3��	�汾��	6.1.0.3	
	���ڣ�	20130530	
	�޸ģ�	1��ȥ��Socket���ͻ������Ϊ64K �Ĳ���
				2������Զ�̻طŽӿ�
					�ϲ���Ҫ��CTTXRecFile  �̳д����ļ������࣬����Ƶ֡��ʽ����������				
4��	�汾��	6.1.0.4	
	���ڣ�	20130603	
	�޸ģ�	1������PC���ն˽��в�������ʱ�����Ͳ����ļ�����Ϊ0����ɲ�������ʧ�ܵĴ���

5�� 	�汾��	6.1.0.5 
	���ڣ�	20130604	
	�޸ģ�	1�����ӽӿڻ�ȡ������ĳ�����͵Ĳ�����Ϣ(��CTTXNetWork::DoGetConfig ��CTTXNetWork::DoSetConfig )
	
6�� 	�汾��	6.1.0.6
	���ڣ�	20130610	
	�޸ģ�	1�����ӶԴ�������͸������������ж������Ȼ��浽����(ʹ�û��λ�����н��л���)
				2�������ļ��ϴ��������Ͷ��壬�����豸����֪ͨ��������Ҫ�ϴ�¼���ļ���ͼƬ�ļ�
7�� 	�汾��	6.1.0.7
	���ڣ�	20130622	
	�޸ģ�	1���޸�TTXNET_SetDeviceInfo �ӿڣ������ϱ��������ͺͳ�������
				2������TTXNET_SetNetworkInfo�ӿڣ������ϱ���ǰʹ�õ��������ӵ�״̬(3G \ WIFI \ ����)
				3������TTXNET_SetMediaInfo�ӿڣ�����������Ƶý���ʽ
8�� 	�汾��	6.1.0.8
	���ڣ�	20130627	
	�޸ģ�	1���޸�CTTXNetWork::DoFreePresetGet  �ӿڣ����ڻ�ȡ��С��Ч��Ԥ��λ
9�� 	�汾��	6.1.0.9
	���ڣ�	20130629	
	�޸ģ�	1���޸�TTXNET_SendAudioIntercom  �豸���������������Խ�����
10��	�汾: 		6.1.0.10
	����:		20130701
	�޸�		1���޸�TTXNET_StartWork�ӿڣ�����bInitLogin���û�����ѡ���Ƿ��������ע��
				2�����ӻ�ȡ��������ӿ�DoGetNetParam���豸��������ӿ�DoSetNetParam
				3�����ӻ�ȡ��ɫ�����ӿ�DoGetVideoColor��DoSetVideoColor
11��	�汾: 	6.1.0.11
	����:		20130729
	�޸�		1����������¼���ļ�ʱ���ļ�ʱ�� nEndTime ʼ��Ϊ0�� BUG
12��	�汾: 	6.1.0.12
	����:		20130731
	�޸�		1��TTXNET_Initialize�ӿ�����signal(SIGPIPE, SIG_IGN);����, ����socket�ж�ʱ������������˳�
13��	�汾: 	6.1.0.13
	����:		20130802
	�޸�		1������CTTXNetWork::GetVideoResolution ���ڻ�ȡ��Ƶͨ���ķֱ��ʣ���������⿪������
14��	�汾: 	6.1.0.14
	����:		20130803
	�޸�		1������CTTXNetWork::FindJpegFile ���ڲ���ͼƬ�ļ���Ϣ
15��	�汾: 	6.1.0.15
	����:		20130813
	�޸�		1��֧��ͬʱԤ��������������������Ƶ��Ϣ
15��	�汾: 	6.1.0.16
	����:		20130826
	�޸�		1��֧�����ûỰ�󶨱��ض˿�(TTXNET_SetSessPortBind��������TTXNET_StartWork ǰ����
					�ڷ���������ǽ ˫�����ʱʹ�ã�������ֻ�����豸ָ���˿��ϴ�������
16��	�汾: 	6.1.0.17
	����:		20130905
	�޸�		1���ӿ�ý���ϴ���ý��Ự�������������·��������󣬲��ٵȴ��������ظ���Ϣ
				���ٷ������ݸ������������Լ���Ƶ�ϴ��ٶ�
17��	�汾: 	6.1.0.18
	����:		20130921
	�޸�		1����������״̬�ٶ�
					����TTXNET_StopWork���ڷ�������������������£���ʱ����������͸�ע�������ݰ�
					�ӿ�������ж����ߵ��ٶ�( 3G ���绷����, ��������һ���ܼ�ʱ�յ����ݰ�)
				2��������־�ļ���ѯ�ӿ�
					��Ҫ�����豸�˵�ϵͳ��������ʱ��ʹ����־�����ж�
18��	�汾:	6.1.0.19
	����:		20130925
	�޸�		1�������ϱ�IO����, ���״̬
					SetIOStatus(const TTXIOStatus_S& io)
				2�������ϱ�¼��״̬����Ƶ��ʧ״̬
					SetChannelStatus(const TTXChannelStatus_S& channel)
				3�������ϱ����١����١�ͣ��ʱ��״̬��TTXVehiStatus_S
					typedef struct tagTTXVehiStatus
					{
						bool bOverSpeed;		//����״̬
						bool bLowSpeed;		//����״̬
						unsigned int nParkTime;	//ͣ��ʱ����λ�룬����0��ʾ��ֹ״̬	
					}TTXVehiStatus_S, *LPTTXVehiStatus_S;		
19��	�汾:	6.1.20
	����:		20131009
	�޸�		1����������·�Ľ����̣߳����ȴ������ָ��
20��	�汾:	6.1.21
	����:		20131021
	�޸�		1��UDP������·֧��͸����������Э��
21��	�汾:	6.1.22
	����:		20140110
	�޸�		1�����Ӿ�������WIFI�������ù���	DoSetWifiParam
				2������ˮƽ��ת����ֱ��ת����	TTX_CTRL_TYPE_FLIP_HORIZONTAL ��TTX_CTRL_TYPE_FLIP_VERTICAL
22��	�汾:	6.1.23
	����:		20140310
	�޸�		1������TTX_ALARM_TYPE_CUSTOM �Զ��屨�����ͻ�������Ŀ���岻ͬ�ı���
23��	�汾:	6.1.24
	����:		20140414
	�޸�		1��TTXNET_SetNetworkInfo ����imei�����������ϱ�imei��Ϣ
										����version�����������ϱ��豸�����汾(�������Ὣ����������汾���ϱ�)
				2��TTXNET_SetReconnNow ����������������3G �κųɹ���WIFI���ӳɹ��󣬼�ʱ����TTXNET_SetReconnNow
										�������Կ��ٻָ����������������
24��	�汾:	6.1.25
	����:		20140426
	�޸�		1������GetUploadFilePath ��SaveUploadFile ���ڷ��������豸�ϴ��ļ�
				2������TransQuery ����͸����ѯ����(����ʵʱ��ϸ������־��ѯ��)
				3�������������Уʱ�Ĺ���TTXNET_SetSyncTime �����Ƿ�ͬ��Уʱ��SyncTime ��ӦУʱ����
25��	�汾:	6.1.26
	����:		20140613
	�޸�		1���޸ĵ��ν��յ����ָ��ʱ��ֻ�����˵�һ��ָ���BUG
26��	�汾:	6.1.27
	����:		20140708
	�޸�		1������ֹͣ��Ƶż�����ֵ������͵�����BUG
27��	�汾:	6.1.28
	����:		20140718
	�޸�		1������SetHeartInterval  ��������������ʱ����
28��	�汾:	6.1.29
	����:		20140827
	�޸�		1��TTXModuleStatus_S�����������������ϱ��������ͺͶ�λ����
					char cCoorType;		//GPS��������TTX_COOR_TYPE_WSG84��TTX_COOR_TYPE_GCJ02, TTX_COOR_TYPE_BD09
					char cLocType; 		//GPS��λ����TTX_LOC_TYPE_GPS��TTX_LOC_TYPE_WIFI
				2������TTXNET_IsRunningNormal���Ź�����ͨ���˽ӿ����ж�������Ƿ���������
					��������쳣����ֱ����������
				3�������ֹ��õ�ͷ�ļ��ƶ��� dvrnet/common Ŀ¼�£������Ҫ����makefile������������
29���汾:	6.1.30
	����:		20141217
	�޸�		1�����������������ܣ���������ʱ����ӷ������ϻ�ȡ�����İ汾��Ϣ
					�����ȡ�ɹ���
					����CheckUpgradeVer���ж��Ƿ���Ҫ������������GetUploadFilePath, GetUpgradeFile, UpgradeDevice���������ӿ�
					�ϰ汾�豸֧�ִ˹��ܣ��ϲ��������Ҫ���޸�					
				2����������ʱ�ϱ�Ӳ��״̬��ͨ����Ƶ��ʧ״̬����Ϣ�������������������ṩӲ�����ϱ���
				3������UPS���߱�����Ӳ�̳��±�����ǰ����˿�����
30���汾:  	6.1.31
	����:		20150130
	�޸�		1��TTXNET_SetMediaInfo����VideoCoder������Ĭ����TTX_VIDEO_CODEC_H264������Ǻ�˼����ʹ��TTX_VIDEO_CODEC_H264_HI

31���汾:  	6.1.32
	����:		20150314
	�޸�		1������TTX_ALARM_TYPE_DISK_SPACE_WARNING��Ӳ�̿ռ侯��

32���汾:  	6.1.33
	����:		20150605
	�޸�		1��TTXNET_StartWork����bOnlyMedia�ӿڣ�808����ʱ��������808��ý��Ӵ�Э��ʱʹ��
					����TTXNET_TransparentInstruction�ӿڣ�808͸����ָ��ͨ���˽ӿڴ��͵��������
					������Э��8.61  ��������͸��0x8900
						ָ������0xeb;
					�뽫�������������յ���͸��ָ��(ָ������Ϊ0xeb)����TTXNET_TransparentInstruction���͵������
				2������TTXNET_InitiativeUploadStatus�ӿڣ����ڼ�ʱ�ϱ�gps����
33���汾:  	6.1.34
	����:		20150723
	�޸�		1�������豸ע������CTTXNetWork::GetVideoResolution�ӿ��ϱ������ķֱ��ʺͻ�������
					����°汾�ķ�����ʹ�ã��Ὣ�ֱ��ʴ��͵��������ϣ�
					�ͻ��˽�����ʾʱ�����Ϸֱ�������ʹ�ò�ͬ�Ļ���
				2���ط�ʱ���봫��TTXFILEInfo_S ��Ϣ�����Ӵ���
					unsigned char ucResolution;		//�ֱ���		TTX_RESOLUTION_720P
					������������
34���汾:  	6.1.35
	����:		20150830
	�޸�		1������TTXPfnJT808UploadTransInstructionCB����808�Խ�ʱͨ��808͸����ָ���ϴ�����������
35���汾:  	6.1.36
	����:		20151012
	�޸�		1������TTXPfnJT808CheckOnlineCB����808�Խ�ʱ�ж�������·�Ƿ�������
36���汾:  	6.1.37
	����:		20151028
	�޸�		1������TTXAlarmInfo, param[4]��Ϊparam[8]
				2��GetUploadFilePath ����szSvrFile��������ʾ�������϶�Ӧ���ļ����������豸�ж��ļ�����
				3��SaveUploadFile����szMd5��������ʾ�ļ���Ӧ��md5ֵ���豸����ͨ��md5��У���ļ�����ȷ��
37���汾:  	6.1.38
	����:		20151107
	�޸�		1��TTXNET_StartWork����bAuthentication�ӿڣ������Ƿ���м�Ȩ
				2������DoAuthentication�ӿڣ��Է��������ص����ݽ��м�Ȩ����Ȩ�ɹ����ٽ���Ȩ����ܺ󷵻ظ�������
38���汾:  	6.1.39
	����:		20151120
	�޸�		1������TTXObdStatus_S ��TTXPeopleStatus_S��Ϣ�������ϱ�OBD״̬������ͳ����Ϣ
39���汾:  	6.1.40
	����:		20151202
	�޸�		1������IsInitStatus �����ж�gps״̬�Ƿ��ʼ���ɹ�����������ʱ�������������Ч��״̬��Ϣ
				2��TTXNET_SetDataPath ����nStatusCacheCount��nAlarmCacheCount�����������ϲ��Զ��屨����GPS�Ļ�����Ŀ
					��ͬ���Ļ����С�£����Ի�������GPS����
40���汾:  	6.1.41
	����:		20151208
	�޸�		1������TTXNET_SetAVDirectConnectDiffBuffer��Ƶֱ��ʱ��3G�ϱ�ʹ�ò�ͬ�Ļ���
					���ʹ��TTX_STREAM_TYPE_DIRECT_MAIN	TTX_STREAM_TYPE_DIRECT_SUB ��������������
41���汾:  	6.1.42
	����:		20151210
	�޸�		1������TTXNET_SetIsLoginSvr�û��ϲ������Ƿ����������������,Ĭ�������������������
42���汾:  	6.1.43
	����:		20160106
	�޸�		1������TTXNET_SendDirectAlarmInfo����ֱ��ʱ�ϱ�������Ϣ
43���汾:  	6.1.44
	����:		20160301
	�޸�		1������״̬�߳����ڲ���GPS״̬
43���汾:  	6.1.45
	����:		20160416
	�޸�		1��obd�����ϱ������˼������ݣ���TTXObdStatus_S, obd��GPSʵʱ�ϴ�
				2������TTXTireStatus_S��̥ѹ���ݶ��壬̥ѹ����ʹ��͸����ʽ�����ϱ�
				3������TTX_ALARM_TYPE_TPMS̥ѹ�����Ķ���
				4��TTXGpsInfo_S�ṹ������usGaoDu�̶߳��壬��λ��
				5������GetAudioParam�ӿڣ�����ͬͨ����Ƶ��ʽ��һ�µ����⣬��Խ���g711��ͨ����Ƶ��aac
				6������TTXNET_SetMediaIPSameAsLoginIP��TTXNET_SetServerInfo����WIFI����IP1��3G����IP2
44���汾  	6.1.46
	����:		20161201
	�޸�:     	1���޸�ͨ�ÿ��Ŀ¼�ŵ�dvrnet/ttxcommon�ڣ��뽫ԭ���Ŀ�����ɾ�������¸��¿��ļ����ٽ��б���
				2������TTXNET_IsServerDeviceExist�ӿ������жϷ��������Ƿ���Ӻõ��豸������սӿں���˵��
45���汾  	6.1.47
	����:		20170312
	�޸�:     	1��ʵʱ��Ƶ��Զ�̻طţ�һ�ζ�ȡ��֡����Ϣ��������߷���Ч��
				2������GetVideoParam���ڲ�ͬͨ����Ƶ�����ʽ��ͬ
46���汾  	6.1.48
	����:		20170905
	�޸�:     	1������TTXNET_SetDevicePwd�����������豸���ӷ�����ʹ�õ�����
					����TTXNET_SetLoginType�����õ�¼����, Ϊ��linux�ϵ�¼����android��¼
47���汾  	6.1.49
	����:		20180122
	�޸�:     	1���ط�ʱ�ж������wifi���磬ÿ�λ���ȡ֡�����з���

*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @Description: ��ʼ������⣬��������ʱ����
 * @param: ��
 * @return: void 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_Initialize();

/**
 * @Description: �ͷ�����⣬�����˳�ʱ����
 * @param: ��
 * @return: void 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_InInitialize();

/**
 * @Description: ������־����
 * @param:	bConsole 	�Ƿ����������̨
 			bFile 		�Ƿ�д��־���ļ�
 			nLogLevel 	��־����0 - 3��0��С��3��󣬼���Խ��д��־Խ��
 						0: INFO, 1:DEBUG, 2:WARN, 3: ERROR�����Ի����뽫������ͣ����Ա��ڽ��е���
 						�����汾�뽫������ߣ��������ϵͳ����Ч��
 			szLogPath	��־Ŀ¼����־�ļ�Ŀ¼��һ��д��Ӳ���ϻ���SD���ϣ�ʾ��:  /sd/
 						ģ����ڴ�Ŀ¼�����½�һ��ttxnetlog��Ŀ¼���У�ʵ�ִ洢·��Ϊ/sd/ttxnetlog/
 			nMBSize 		��־�ļ���С��Ĭ��Ϊ1MB 
 						��־�ļ�ÿ��200KB����־�ļ��ܴ�С�������ƵĴ�С��
 						��Ḳ����ʷ��־��Ϣ
 * @return: ��
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_SetLogParam(bool bConsole, bool bFile, int nLogLevel, const char* szLogPath, int nMBSize);

/*****************************************************************************
* @ �豸ͨ����Ϣ����
* @ ����ͨ����Ŀ��Ϣ����Ĭ��Ϊ4ͨ�����豸
* @ ���������Ŀ��Ĭ��Ϊ1�������Ҫ��������˼����ͶԽ���
* @ ���û��ר�ŵ����Ӳ��������ʹ��ͨ��1���Խ��ͼ�����
* @ �������0���ᵼ�¿ͻ����޷�������˺ͽ��жԽ�
* @ �豸���ƣ���ΪMDVR�����ʾ���ƺ�
* @ Ӳ�����ͣ�Ĭ��ΪTTX_DISK_TYPE_SD
* @ �������ͣ�TTX_FACTORY_TYPE_UNKOWN
* @ �����豸����,	�Զ���  ��������ͬһ�����µĲ�ͬ���͵��豸
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetDeviceInfo(int nChnCount, int nMicCount, const char* szDeviceName, int nDiskType = TTX_DISK_TYPE_SD
			, int nFactoryType = TTX_FACTORY_TYPE_UNKOWN, int nFactoryDevType = TTX_FACTORY_TYPE_UNKOWN
			, const char* szVersion = "");

//szPwdΪ��¼����
LIBDVRNET_API int	TTXNET_SetDevicePwd(const char* szPwd); 
//��¼����
//@nLoginType: TTX_LOGIN_TYPE_LINUX�����������Ĭ��ΪTTX_LOGIN_TYPE_LINUX
LIBDVRNET_API int	TTXNET_SetLoginType(int nLoginType); 

/*****************************************************************************
* @ �豸�������Ͷ���
* @ ��������3G, WIFI, ����
* @ ��������,��Ϊwifiʱ��ʾssid���ƣ�ֻ��wifiʱ��Ч
* @ imei��Ϊ�ֻ�ģ���IMEI��
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetNetworkInfo(int nNetType, const char* szName, const char* szImei = "");

/*****************************************************************************
* @ ý�����Ͷ���
* @ ��Ƶ����Ĭ��ΪTTX_AUDIO_TYPE_G726_40KBPS
* @ ��Ƶͨ��nAudioChannel	Ĭ��Ϊ1
* @ ��Ƶ������nAudioSamplesPerSec	Ĭ��Ϊ8000
* @ ��Ƶÿ��ȡ�������λԪ����Ĭ��Ϊ16
* @ ��Ϣ֡���������ͣ����ڳ����նˣ���Ҫ���ڽ��� GPS�ͳ���״̬����
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetMediaInfo(int nAudioType, int nAudioChannel, int nAudioSamplesPerSec, int nAudioBitPerSamples, int nVideoCoder = TTX_VIDEO_CODEC_H264);

/*****************************************************************************
* @ �����ļ�λ�ã���Ҫ���ڻ��汨���¼���GPS����
* @ szDataPath �����ļ�·��: /sd/  ĩβΪ/
* @ GPS��������Ϊcache_status.
* @ ������������Ϊcache_alarm
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetDataPath(const char* szDataPath, int nStatusCacheCount = 8192, int nAlarmCacheCount = 2048);

/*****************************************************************************
* @ ���½ӿ��������ά��������·
* @ �����¼���������÷�������ַ�����豸��ţ�����TTXNET_StopWork����TTXNET_StartWork
* @ �������ά��ͨ�������������ʱ��Ϊ1���ӣ�������5����û���յ����ݣ�����Ϊͨ�ŶϿ�
******************************************************************************/

/**
 * @Description: ������������㣬�˽ӿڱ�����TTXNET_StartWorkǰ����
 * @param: �ϲ�Ӧ����Ҫ��CTTXNetWork�̳����࣬ʵ����Ӧ�Ľӿ�
 * @return: 0��ʾ�ɹ� 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_SetNetAdapter(CTTXNetWork* pNetwork);


/**
 * @Description: ��ʼ����ģ�飬���ô˽ӿں��������ά��ͨ����·
 * @param: 	szIDNO: �豸��ţ���13510907654�������ն����к�ʹ��SIM����Ӧ���ֻ����룬���16λ
 			szServerIP ��������ַ
 			usPort �������˿�
 			bInitListen: ʵʼ������
 			usListenPort: ���ؼ����˿�
 			bInitLogin: �Ƿ������������ͨ��
 			bOnlyMedia: �Ƿ�ֻ����ý��,808Э��ʹ��
 			bAuthentication: ��ʾ�Ƿ����ü�Ȩģʽ�����Ϊtrueʱ������������·�һ����Ȩ��
 				A���豸DoAuthentication �Լ�Ȩ��У��������Ȩ�벻�����������������󣬴�ʱsdk���ж�����
 				B��������ͨ���󣬶�authkey���м��ܣ����������ݸ�������
 * @return: 0��ʾ�ɹ� 
 * @Author: afu
 */
LIBDVRNET_API int	TTXNET_StartWork(const char* szIDNO, const char* szServerIP, unsigned short usPort
							, bool bInitListen, unsigned short usListenPort, bool bInitLogin = true, bool bOnlyMedia = false
							, bool bAuthentication = false);


/**
 * @Description:ֹͣ����
 * @param: 	��
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int	TTXNET_StopWork();

/**
 * @Description:�ж��Ƿ����ӳɹ�
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int TTXNET_IsLoginSuc();

/*
 *�ж��豸�Ƿ���ڣ�TTXNET_IsLoginSuc����0�󣬿����ٵ���TTXNET_IsServerDeviceExist�жϷ��������Ƿ����Щ�豸
 * @return: 0��ʾ����,1��ʾ������
*/
LIBDVRNET_API int TTXNET_IsServerDeviceExist();

/**
 * @Description:��ӱ����¼������������ͨ���жϣ����ڻָ�ͨ�ź��ٽ����ϴ�
 * @param:	pAlarmInfo: �����¼�
 * @return: 0��ʾ�ɹ� 
 * @szId��������������ȱ��볬��40 ���ַ������ر�����Ӧ��guid��Ϣ������Ψһ��ʶ����������Ϣ
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int TTXNET_AddAlarmInfo(TTXAlarmInfo_S* pAlarmInfo, char* szId = NULL);

/**
 * @Description:���ʹ���͸������
 * @param: 	nType: ��������
 			pBuffer: ��������
 			nLength: ���ݳ���
 			bReliable: ��ʾ�Ƿ�ɿ�����,  true��ʾ�������ܱ�֤���͵���������
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int	TTXNET_SendTransparentSerial(int nType, const char* pBuffer, int nLength, bool bReliable = false);

/**
 * @Description:��������Խ���ֻ�����������ͨ�ųɹ���ʱ�䣬�Ż᷵�سɹ�
 * @param: 	bStart: �Ƿ�����˫��Խ�
 			nChn: ͨ����
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2013-06-29
 */
LIBDVRNET_API int	TTXNET_SendAudioIntercom(bool bStart, int nChn = 0);

/**
 * @Description:��ȡ�˿ڰ󶨲���
 * @param: 	lpBindPort: �˿ڰ󶨲���
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2013-08-26
 */
LIBDVRNET_API int	TTXNET_GetSessPortBind(TTXSessPortBind_S* lpPort);

/**
 * @Description:���ö˿ڰ󶨲���
 * @param: 	lpBindPort: �˿ڰ󶨲���
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2013-08-26
 */
LIBDVRNET_API int	TTXNET_SetSessPortBind(const TTXSessPortBind_S* lpPort);

/**
 * @Description:���ý��м�ʱ�������統�豸������3G����󣬼�ʱ����Щ�ӿڣ���������Կ������ӵ�������
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2014-04-14
 */
LIBDVRNET_API int	TTXNET_SetReconnNow();

/*****************************************************************************
* @ ͬ��ʱ��(ֻ��һ����Ч)
* �ӷ�������ȡ�õ�ʱ���ͨ��SyncTime �ӿڷ���
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetSyncTime();

/**
 * @Description:������������ϱ���Ƶ����
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2014-07-18
 */
LIBDVRNET_API int	TTXNET_StartUploadVideo(int nChannel, int nStreamType);

/**
 * @Description:ֹͣ�ϱ���Ƶ
 * @return: 0��ʾ�ɹ� 
 * @Author: afu 2014-07-18
 */
LIBDVRNET_API int	TTXNET_StopUploadVideo(int nChannel, int nStreamType);

/**
 * @Description:�ж����������״̬���ϲ㶨ʱ���ô˽ӿ��ж�������Ƿ���������
 * 			�������жϸ����̵߳�����״̬�����ĳ���߳����в���������᷵��ʧ��
 			����ÿ2�����һ��
 * @return: true��ʾ�ɹ� , false��ʾ����ʧ��
 * @Author: afu 2014-08-29
 */
LIBDVRNET_API bool TTXNET_IsRunningNormal();

/**
 * @Description:�Ƿ�����Ƶʱ��ͬʱ������Ƶ
 * @return: �� 
 * @Author: afu 2014-09-19
 */
LIBDVRNET_API void TTXNET_SetSyncSendAudio(bool bSyncSendAudio);

/**
 * @Description:�����ϱ�״̬
 * @return: �� 
 * @Author: afu 2015-04-27
 */
LIBDVRNET_API void TTXNET_InitiativeUploadStatus();

/**
 * @Description:����͸������������(808����ʱʹ�ã�������808��ý���߱�Э��)
 * @return: �� 
 * @Author: afu 2015-06-05
 */
LIBDVRNET_API void TTXNET_TransparentInstruction(const char* pInstruction, int nLength);

/**
 * @Description:�ϱ�ָ���������(808����ʱʹ�ã����ص������ݣ�ͨ��808͸���ϱ�����������)
 * @return: �� 
 * @Author: afu 2015-08-30
 */
LIBDVRNET_API void TTXNET_JT808UploadTransInstruction(void* pUsr, TTXPfnJT808UploadTransInstructionCB pfnUploadInstruction);

/**
 * @Description:�ϱ�ָ���������(�ṩ�ӿ�����������ж�808��������·�Ƿ����ߣ����1���ӵ���һ��)
 * @return: �� 
 * @Author: afu 2015-10-12
 */
LIBDVRNET_API void TTXNET_JT808CheckOnline(void* pUsr, TTXPfnJT808CheckOnlineCB pfnCheckOnline);

/**
 * @Description:��Ƶֱ��ʱ��3G�ϱ�ʹ�ò�ͬ�Ļ���
 * @return: �� 
 * @Author: afu 2015-12-08
 */
LIBDVRNET_API void TTXNET_SetAVDirectConnectDiffBuffer(bool bAVDiffBuffer);

/**
 * @Description:�����Ƿ���������������ӣ���������ã���Ĭ�����������������
 * @return: ��
 * @Author: afu 2015-12-08
 */
LIBDVRNET_API void TTXNET_SetIsLoginSvr(bool bLoginSvr);

/**
  * @Description:ֱ��ʱ���ͱ������ݵ��ͻ��ˣ��ڿͻ���ֱ���豸ʱʹ��
 * @return: ��
 * @Author: afu 2016-01-06
 */
LIBDVRNET_API void TTXNET_SendDirectAlarmInfo(TTXAlarmInfo_S* pAlarmInfo);

/**
  * @Description:���÷�������Ϣ,��WIFI����IP1��3G����IP2���������л�ʱ����Щ�ӿ��������÷�����IP
 * @return: ��
 * @Author: afu 2016-05-11
 */
LIBDVRNET_API void TTXNET_SetServerInfo(const char* szIP, unsigned short usPort);

/**
  * @Description:����ý��Ự��ע�������ʹ��ͬһ��IP����WIFI����IP1��3G����IP2ʱʹ�ã�����ý��Ự�͵�¼��IP����һ��
 * @return: ��
 * @Author: afu 2016-05-11
 */
LIBDVRNET_API void TTXNET_SetMediaIPSameAsLoginIP(bool bSame);

/*****************************************************************************
* @ imsi��Ϊ�ֻ�ģ���IMSI��
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetImsi(const char* szImsi);

/*****************************************************************************
* @ ����Ϊʵʱģʽ��Ĭ��Ϊfalse����Ϊʵʱģʽʱ����Ƶ�ͶԽ���Ͽ��ж��ж�
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetRealTimeMode(bool bRealTimeMode);

/*****************************************************************************
* @ ���ã�Ĭ��Ϊfalse����ʵʱ��Ƶ��������ʱ���Ƿ�Ҫ��gps,����״̬����Ϣ

* @return: ��
* @Author: dhy 2017-06-21
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetUpStateInfoMode(bool bStateInfoMode);

/**
 * @Description:��ȡ���ٺ���������
 * @return: ����ʱ���(����) 
 * @Author: 
 */
LIBDVRNET_API _u64long GetTimeNoRecvData();



#ifdef __cplusplus
}
#endif 


#endif

