#ifndef _TTX_DVR_NET_DEF_H_
#define _TTX_DVR_NET_DEF_H_

/******************************************************************************
  Author        : afu
  Created       : 2012/11/30
  Last Modified :
  Description   : �����ͨ����Ϣ����
  History       :
	  1.	Date        : 2012/11/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/

#ifdef WIN32

	#ifdef LIBDVRNET_EXPORTS
	#define LIBDVRNET_API __declspec(dllexport)
	#else
	#define LIBDVRNET_API __declspec(dllimport)
	#endif

#else

	#define LIBDVRNET_API

#endif

#include "ttxtypedef.h"

#define TTX_NET_VERSION 		"V6.1.48 20180122"


#define TTX_MAX_CHANNEL			16		//���ͨ����Ŀ
#define TTX_MAX_SESS			4		//���Ự��Ŀ
#define TTX_MAX_STREAM			4		//���������Ŀ
//�����붨��
#define TTX_NET_OK				0		//�ɹ�
#define TTX_NET_FALSE			-1		//ʧ��
#define TTX_NET_ERR_PARAM		-2		//��������
#define TTX_NET_ERR_EXIST		-3		//�Ѿ�����
#define TTX_NET_ERR_NETWORK		-4		//�������
#define TTX_NET_ERR_BUF_FULL	-5		//���������������
#define TTX_NET_ERR_NO_RUNNING	-6		//δ�����������

//�ͻ��˵�¼����
#define TTX_LOGIN_TYPE_LINUX 	0		//Ĭ��ΪǶ��ʽ
#define TTX_LOGIN_TYPE_WINDOW	1		//windowsPC����
#define TTX_LOGIN_TYPE_WEB		2		//IOS��
#define TTX_LOGIN_TYPE_ANDROID	3		//ANdroid��
#define TTX_LOGIN_TYPE_IOS		4		//IOS��

//GPS״̬����
#define TTX_GPS_VALID 			'A'		//GPS��Ч
#define TTX_GPS_UNVALID 		'V'		//GPS��Ч
#define TTX_GPS_LONGITUDE_EAST 	'E'		//����
#define TTX_GPS_LONGITUDE_WEST  'W'		//����
#define TTX_GPS_LATITUDE_NORTH  'N'		//��γ
#define TTX_GPS_LATITUDE_SOUTH  'S'		//��γ

//GPS�������Ͷ���
#define	TTX_COOR_TYPE_WSG84		0		//WSG84��������
#define	TTX_COOR_TYPE_GCJ02		1		//�������꣬�ߵµ�ͼʹ��
#define	TTX_COOR_TYPE_BD09		2		//�ٶ�����

//GPS��λ���Ͷ���
#define	TTX_LOC_TYPE_GPS		0		//GPS��λ
#define	TTX_LOC_TYPE_LBS		1		//��վ
#define	TTX_LOC_TYPE_WIFI		2		//WIFI��λ

//Ӳ��״̬����
#define TTX_DISK_NO_EXIST		0		//Ӳ�̲�����
#define TTX_DISK_EXIST			1		//Ӳ�̴���
#define TTX_DISK_NO_ELEC		2		//Ӳ�̶ϵ�

//3Gģ��״̬����			
//			0��SIM��������1���ź���2���źŲ�3���ź�һ��4���źź�
//			5���ź� ��6��3Gģ�鲻����7��3G���ܹر�
#define TTX_3G_SIM_NO_EXIST		0		//SIM��������
#define TTX_3G_SIGNAL_WEAK		1		//ģ���ź���
#define TTX_3G_SIGNAL_POOR		2		//ģ���źŲ�
#define TTX_3G_SIGNAL_NORMAL	3		//ģ���ź�һ��
#define TTX_3G_SIGNAL_GOOD		4		//ģ���źź�
#define TTX_3G_SIGNAL_EXCELLENT	5		//ģ���ź���
#define TTX_3G_NO_EXIST			6		//ģ�鲻����
#define TTX_3G_CLOSE			7		//3G���ܹر�

//ý�����Ͷ���
#define TTX_MEDIA_TYPE_AV		0		//����Ƶ�ͻ�(����ʵʱԤ��)
#define TTX_MEDIA_TYPE_AUDIO	1		//��Ƶ�ͻ�(������Ƶ����)
#define TTX_MEDIA_TYPE_TALKBACK	2		//�Խ��ͻ�(������Ƶ�Խ�)

//�������Ͷ���
#define TTX_STREAM_TYPE_MAIN	0		//������
#define TTX_STREAM_TYPE_SUB		1		//������
#define TTX_STREAM_TYPE_DIRECT_MAIN		2		//ֱ��������
#define TTX_STREAM_TYPE_DIRECT_SUB		3		//ֱ��������

//��Ƶ������
#define TTX_AUDIO_STREAM_MIC	0		//���
#define TTX_AUDIO_STREAM_CAM	1		//����ͷ
#define TTX_AUDIO_STREAM_PTT	2		//��Ⱥ�Խ�

//¼��ͨ��
#define TTX_CHANNEL_ALL			98		//����ͨ��
#define TTX_CHANNEL_ALL_EX		-1		//����ͨ��

//¼�����Ͷ���
#define TTX_RECTYPE_NORMAL		1		//����¼��
#define TTX_RECTYPE_ALARM		2		//����¼��
#define TTX_RECTYPE_ALL			3		//����¼��

//�ļ����Զ���
#define TTX_FILE_JPEG		1		//ͼƬ�ļ�
#define TTX_FILE_RECORD		2		//¼���ļ�
#define TTX_FILE_LOG		3		//��־�ļ�
#define TTX_FILE_AUDIO		4		//��Ƶ�ļ�

//��־�ļ����Ͷ���(��־�ļ�����ʱʹ��)
#define TTX_LOGFILE_NETWORK		1		//������־��Ϣ
#define TTX_LOGFILE_SYSTEM		2		//ϵͳ��־��Ϣ


//��ͬ���ң�ʹ�ò�ͬ������
#define TTX_FACTORY_TYPE_UNKOWN					0
#define TTX_FACTORY_TYPE_1						1	//
#define TTX_FACTORY_TYPE_2						2	//
#define TTX_FACTORY_TYPE_3						3	//
#define TTX_FACTORY_TYPE_4						4	//
#define TTX_FACTORY_TYPE_5						5	//
#define TTX_FACTORY_TYPE_6						6	//
#define TTX_FACTORY_TYPE_7						7	//
#define TTX_FACTORY_TYPE_8						8	//
#define TTX_FACTORY_TYPE_9						9	//
#define TTX_FACTORY_TYPE_10						10	//
#define TTX_FACTORY_TYPE_11						11	//
#define TTX_FACTORY_TYPE_12						12	//TTX
#define TTX_FACTORY_TYPE_13						13	//
#define TTX_FACTORY_TYPE_14						14	//
#define TTX_FACTORY_TYPE_15						15	//
#define TTX_FACTORY_TYPE_16						16	//
#define TTX_FACTORY_TYPE_17						17	//
#define TTX_FACTORY_TYPE_18						18	//
#define TTX_FACTORY_TYPE_19						19	//
#define TTX_FACTORY_TYPE_20						20	//
#define TTX_FACTORY_TYPE_21						21	//
#define TTX_FACTORY_TYPE_22						22	//
#define TTX_FACTORY_TYPE_23						23	//
#define TTX_FACTORY_TYPE_24						24	//
#define TTX_FACTORY_TYPE_25						25	//
#define TTX_FACTORY_TYPE_26						26	//
#define TTX_FACTORY_TYPE_27						27	//
#define TTX_FACTORY_TYPE_28						28	//
#define TTX_FACTORY_TYPE_29						29	//
#define TTX_FACTORY_TYPE_30						30	//
#define TTX_FACTORY_TYPE_31						31	//
#define TTX_FACTORY_TYPE_32						32	//
#define TTX_FACTORY_TYPE_33						33	//
#define TTX_FACTORY_TYPE_34						34				
#define TTX_FACTORY_TYPE_35						35				
#define TTX_FACTORY_TYPE_36						36				
#define TTX_FACTORY_TYPE_37						37				
#define TTX_FACTORY_TYPE_38						38				
#define TTX_FACTORY_TYPE_39						39				
#define TTX_FACTORY_TYPE_40						40				
#define TTX_FACTORY_TYPE_41						41	//
#define TTX_FACTORY_TYPE_42						42	//
#define TTX_FACTORY_TYPE_43						43	//
#define TTX_FACTORY_TYPE_44						44				
#define TTX_FACTORY_TYPE_45						45				
#define TTX_FACTORY_TYPE_46						46				
#define TTX_FACTORY_TYPE_47						47				
#define TTX_FACTORY_TYPE_48						48				
#define TTX_FACTORY_TYPE_49						49				
#define TTX_FACTORY_TYPE_50						50	

//�ļ����Ͷ���
#define TTX_FILE_TYPE_JPEG						1//ͼƬ
#define TTX_FILE_TYPE_REC						2	//¼���ļ�
#define TTX_FILE_TYPE_AUDIO						4	//��Ƶ�ļ�

//��̨���Ͷ���
#define TTX_PTZ_MOVE_LEFT				1
#define TTX_PTZ_MOVE_RIGHT				2
#define TTX_PTZ_MOVE_TOP				3
#define TTX_PTZ_MOVE_BOTTOM				4
#define TTX_PTZ_MOVE_LEFT_TOP			5
#define TTX_PTZ_MOVE_RIGHT_TOP			6
#define TTX_PTZ_MOVE_LEFT_BOTTOM		7
#define TTX_PTZ_MOVE_RIGHT_BOTTOM		8

#define TTX_PTZ_FOCUS_DEL				9
#define TTX_PTZ_FOCUS_ADD				10
#define TTX_PTZ_LIGHT_DEL				11
#define TTX_PTZ_LIGHT_ADD				12
#define TTX_PTZ_ZOOM_DEL				13
#define TTX_PTZ_ZOOM_ADD				14
#define TTX_PTZ_LIGHT_OPEN				15
#define TTX_PTZ_LIGHT_CLOSE				16
#define TTX_PTZ_WIPER_OPEN				17
#define TTX_PTZ_WIPER_CLOSE				18
#define TTX_PTZ_CRUISE					19
#define TTX_PTZ_MOVE_STOP				99

#define TTX_PTZ_PRESET_MOVE				22
#define TTX_PTZ_PRESET_SET				23
#define TTX_PTZ_PRESET_DEL				24

#define TTX_PTZ_SPEED_MIN				0
#define TTX_PTZ_SPEED_MAX				255

//��Ƶ���Ͷ���
#define TTX_AUDIO_TYPE_G726_40KBPS				1		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_ADPCM					2		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_MEDIA_40KBPS		3		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_MEDIA_32KBPS		4		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_MEDIA_24KBPS		5		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_MEDIA_16KBPS		6		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_32KBPS				7		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_24KBPS				8		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G726_16KBPS				9		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G711A					10		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G711U					11		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_AAC_8KBPS				12
#define TTX_AUDIO_TYPE_AAC_16KBPS				13
#define TTX_AUDIO_TYPE_ARM						14		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_AAC_24KBPS				15
#define TTX_AUDIO_TYPE_ADPCM_IMA				16		//ʹ�ú�˼��ʽ
#define TTX_AUDIO_TYPE_G711A_EX					17		//�Ǻ�˼��ʽ
#define TTX_AUDIO_TYPE_G711U_EX					18		//�Ǻ�˼��ʽ
#define TTX_AUDIO_TYPE_NELLY_8KBPS				19		//Nellymoser

//��ƵCoder ����
#define TTX_VIDEO_CODEC_H264					0
#define TTX_VIDEO_CODEC_H264_HI					1	//��Ƶ����������˼оƬʹ��Щ����	
#define TTX_VIDEO_CODEC_H264_PRI_1				2	//˽�д�������Ϣ���벻Ҫʹ��Щ����
#define TTX_VIDEO_CODEC_H265_HI					3	//
#define TTX_VIDEO_CODEC_H265					4	//


//�������Ͷ���
#define TTX_NETWORK_TYPE_3G				0	//3G�����¼
#define TTX_NETWORK_TYPE_WIFI			1	//WIFI�����¼
#define TTX_NETWORK_TYPE_NET			2	//���������¼
#define TTX_NETWORK_TYPE_4G				3	//4G����

//��������(�������ֿ�����Ӳ�̻�)
#define TTX_DISK_TYPE_SD				1	//SD��
#define TTX_DISK_TYPE_HDD				2	//Ӳ��
#define TTX_DISK_TYPE_SSD				3	//SSD

//�豸�������Ͷ���
#define TTX_CTRL_TYPE_OIL_STOP			1	//�Ͽ���·
#define TTX_CTRL_TYPE_OIL_RESTORE		2	//�ָ���·
#define TTX_CTRL_TYPE_ELEC_STOP			3	//�Ͽ���·
#define TTX_CTRL_TYPE_ELEC_RESTORE		4	//�ָ���·
#define TTX_CTRL_TYPE_REBOOT			5	//�������� 
#define TTX_CTRL_TYPE_RESET				6	//�豸��λ
//Ϊ��ʡ��ͽ�ʡ���̿ռ䣬����DVR���Զ��ص�����ͷ��Դ��ֹͣ¼�񣬴�������״̬��
//����һ������б����������Զ�̻���ָ�DVR�ͻ���������ͷ��Դ������¼��
#define TTX_CTRL_TYPE_SLEEP				7	//����
#define TTX_CTRL_TYPE_WAKE				8	//����
//¼���ͨ����0��ʾͨ��1��1��ʾͨ��2     98��ʾ����ͨ��(TTX_CHANNEL_ALL)
#define TTX_CTRL_TYPE_START_RECORD		9	//��ʼ¼��	//�����ֽ�Ϊ¼���ͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_STOP_RECORD		10	//ֹͣ¼��	//�����ֽ�Ϊ¼���ͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_START_CRUISE		11	//�ͻ��˿�ʼ�Դ�ͨ��������ѯ�������ֽ�Ϊͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_STOP_CRUISE		12	//�ͻ���ֹͣ�Դ�ͨ��������ѯ�������ֽ�Ϊͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_WRITE_LOG			13	//������¼��־����	�������ֽڴ���0��ʾд��־��0��ʾ��д��־
#define TTX_CTRL_TYPE_FORMAT_HDD		14	//��ʽ��Ӳ��(��λ��ʾӲ�̺�,Ӳ�̺Ŵ�0��ʼ,��λ��ʾ�����)
#define TTX_CTRL_TYPE_MILEAGE_CLEARED 		15	//�������
#define TTX_CTRL_TYPE_FLIP_NORMAL 		16	//��ת��ת	//�����ֽ�Ϊͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_FLIP_REVERSE 	 	17	//��ת��ת	//�����ֽ�Ϊͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_CLEAR_ALARM		18		//�������
#define TTX_CTRL_TYPE_SWITCH_CAM		19		//�л�����ͷ
#define TTX_CTRL_TYPE_RECORD_SOUND		20		//��ʼ¼��    //�����ֽ�Ϊ¼����ͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_STOP_REC_SOUND	21		//ֹͣ¼��    //�����ֽ�Ϊ¼����ͨ���ţ������ֽ�Ϊָ��
#define TTX_CTRL_TYPE_WIFI_DOWN_FINISH	22		//wifi���ؽ���

//�ϴ����ļ����Ͷ���
#define TTX_UPLOAD_FILE_TYPE_PICTURE	1	//ͼƬ�ļ�(������jpg, bmp, png�ȸ�ʽ)
#define TTX_UPLOAD_FILE_TYPE_UPGRADE	2	//�����ļ�������Ϊ(�汾��+ �汾����)

#define TTX_MOTION_MASK 			9	//�ƶ����
#define TTX_UPLOAD_STATES_INFO		0x11223344 //��Ϣ֡�Ƿ��gps,����״̬����Ϣ
//������������
#define TTX_TYPE_CODE_ANSI			0		//ANSI
#define TTX_TYPE_CODE_UTF8			1		//UTF8

#pragma pack(4)

typedef struct tagTTXGpsInfo
{
	char cGpsStatus; 			//gps�Ƿ���Ч�꣬A��ʾ��Ч��V��ʾ��Ч��Ĭ��ΪV
	char cReserve;				//��������
	unsigned short usSpeed;		//�ٶ�ֵ��Ĭ��Ϊ0��9999 = 99.99����
	unsigned char cLatDegree;			//γ��ֵ�Ķ�
	unsigned char cLatCent; 				//γ��ֵ�ķ�
	unsigned char cLngDegree;			//����ֵ�Ķ�
	unsigned char cLngCent;				//����ֵ�ķ�
	long lLatSec;				//γ��ֵ����
	long lLngSec;				//����ֵ����
	char cLatDirection;			//γ�ȵķ���'N'��ʾ��γ��'S'��ʾ��γ 
	char cLngDirection;			//���ȵķ���'E'��ʾ������'W'��ʾ����
	unsigned short usGpsAngle; 	//gps�н�(�����˶�����)��0 -  360��0��ʾ������˳ʱ�뷽��90��ʾ��
	short sGaoDu;	//�̣߳���λ��
	unsigned short usReserved;		//�����ֶ�
	//�豸�˵�GPS��Ϣ�ĸ�ʽһ���ǰ���DDFF.MMMM�ķ�ʽ�����
	//���Դ˴����豸�����ȡ�벢ת���ɴ˴�Ҫ�����ʽ����ʾ��
	//(*ע�⣺����ļ��㷽ʽ��GPSģ���ṩ�����ݸ�ʽ�й�) 
	//�����豸�˲ɼ�����GPSֵ�ǣ�12158.3416���� 
	//		���� 121 
	//		���� 58 
	//		���� 0.3416 �� (*ע�⣺��λ�Ƿ�)
	// 			0.3416 * 60 = 20.496 �� 
	//		������һǧ�򱶣�����ת���ɴ˽ṹ��Ҫ�ľ��ȣ� 
	//			20.496 * 10,000,000 = 204,960,000 (ǧ���֮һ��)
	// ��ʱcLongitudeDegree = 121��cLongitudeCent = 58��lLongitudeSec = 204, 960, 000
}TTXGpsInfo_S, *LPNetGpsInfo_S;

typedef struct tagTTXVehiStatus
{
	bool bAccOpen;		//ACC״̬��Ĭ��Ϊtrue��true��ʾACC��
	bool bLeft;			//��ת״̬��true��ʾ��ת״̬,  Ĭ��Ϊfalse
	bool bRight;		//��ת״̬,    true��ʾ��ת״̬,  Ĭ��Ϊfalse
	bool bBrake;		//ɲ��״̬,    true��ʾɲ��״̬,  Ĭ��Ϊfalse
	bool bZZhuang;		//��ת״̬ =  �˻������ĳ�,    true��ʾ��ת״̬,  Ĭ��Ϊfalse
	bool bFZhuang;		//��ת״̬ =  �˻������ĳ�,    true��ʾ��ת״̬,  Ĭ��Ϊfalse
	bool bOverSpeed;	//����״̬
	bool bLowSpeed;		//����״̬
	unsigned int nLiCheng;	//�������,  ��λ��
	float fYouLiang;		//����99.99 = 99.99��
	unsigned int nParkTime;	//ͣ��ʱ����λ�룬����0��ʾ��ֹ״̬	
}TTXVehiStatus_S, *LPTTXVehiStatus_S;

typedef struct tagTTXDiskStatus
{
	char cDiskStatus;	//Ӳ��״̬, 0�����ڣ�1���ڣ�2�ϵ磬Ĭ��Ϊ0
	bool bDisk2Valid;	//Ӳ��2�Ƿ���Ч, Ĭ��Ϊfalse��Ӳ��2��Чʱ��Ӳ��2��״̬����Ч
	char cDisk2Status;	//Ӳ��2״̬, 0�����ڣ�1���ڣ�2�ϵ�
	char cReserve;		//�����ֶ�
}TTXDiskStatus_S, *LPTTXDiskStatus_S;

typedef struct tagTTXModuleStatus
{
	bool bGpsExist;		//GPSģ���Ƿ���ڣ�true��ʾ����,  Ĭ��Ϊtrue
	char c3gState;		//3Gģ��״̬, 	0��SIM��������1���ź���2���źŲ�3���ź�һ��4���źź�
						//			5���ź� ��6��3Gģ�鲻����7��3G���ܹر�
	char cCoorType;		//GPS��������TTX_COOR_TYPE_WSG84��TTX_COOR_TYPE_GCJ02, TTX_COOR_TYPE_BD09
	char cLocType; 		//GPS��λ����TTX_LOC_TYPE_GPS��TTX_LOC_TYPE_WIFI
	char cSatellites;		//������
	char cSosButton;	//����������״̬��1Ϊtrue��0Ϊfalse
	char cLowVoltage;	//��ѹ����״̬��1Ϊtrue, 0Ϊfalse
	char cVoltage;		//����, 0-100
	char cReserve[4];	//��������
}TTXModuleStatus_S, *LPTTXModuleStatus_S;

typedef struct tagTTXIOStatus
{
	unsigned short usIOInputStatus;//IO����ģ��״̬��0λ��ʾIO_1��ֵΪ1��ʾIO���봦�ڱ���״̬��Ĭ��Ϊ0
						//���16��
	unsigned short usIOOutStatus; 	//IO���״̬�����4����Ч
	char cReserve[8];	//��������
}TTXIOStatus_S, *LPTTXIOStatus_S;

typedef struct tagTTXChannelStatus
{
	unsigned short usLostStatus;	//��Ƶ��ʧ״̬�����8����Ч��ÿλ��ʾ��Ӧͨ����״̬	1��ʾ��Ƶ��ʧ
	unsigned short usRecordStatus;	//��Ƶ¼��״̬�����8����Ч	1��ʾ����¼��
	char cRecStaValid;	//¼��״̬�Ƿ���Ч,���ڿͻ��˵Ĳ�¼�񱨾�����
	char cReserve[7];	//��������
}TTXChannelStatus_S, *LPTTXChannelStatus_S;

//OBD״̬
typedef struct tagTTXObdStatus
{
	unsigned int uiSpeed;		//ͨ��OBD�ٶ�		9900 = 99����			(0-256)			
	unsigned int uiRpm;		//������ת��		3000ת					0-16384			
	unsigned char ucStatus;		//��0λ��ʾACC �_�P	1 �x�����_�P  2	ɷ܇�_�P  3	PTO �_�P	4  �o���x܇	
	char ucJQTemp;			//ȼ�ͽ����¶�	33-33��				-127 - 127		
	short ucJQMPos;			//������λ��		102 = 10.2 %				0-1024			
	short ucBatteryVoltage;		//��ص�ѹ			123   = 12.3V				0-512			
	char cReserve[8];	//��������
}TTXObdStatus_S, *LPTTXObdStatus_S;

//����ͳ�Ƶ�״̬
typedef struct tagTTXPeopleStatus
{
	unsigned int uiUp;			//�ϳ�����
	unsigned int uiDown;		//�³�����
	char cReserve[8];	//��������
}TTXPeopleStatus_S, *LPTTXPeopleStatus_S;

typedef struct tagTTXTemperature
{
	float fTemperatue[4];		//�¶ȣ�99.99 = 99.99��
}TTXTemperature_S, *LPTTXTemperature_S;

typedef struct _tagTTXRecFile
{
	unsigned char Year;		//�꣬11 = 2011��
	unsigned char Month;	//�գ���1��ʼ��1 - 12
	unsigned char Day;		//�죬��1��ʼ��1 - 31
	unsigned char Hour;		//Сʱ����0��ʼ��0 - 23
	unsigned char Minute;	//���ӣ���0��ʼ��0 - 59
	unsigned char Second;	//�룬��0��ʼ��0 - 59
	unsigned char Type;		//�ļ�����		TTX_RECTYPE_NORMAL, TTX_RECTYPE_ALARM, TTX_RECTYPE_ALL
	unsigned char Channel;	//ͨ���ţ���0��ʼ
	unsigned int  uiFileTime;	//�ļ�ʱ������Ϊ��λ
	unsigned int  uiFileLen;	//�ļ�����
	char	szFileName[244];
	char	cYJWNewFlag;		//���ļ�ʹ�ã�����0
	char	cCoointNewFlag;		//���ļ�ʹ�ã�����0
	char	bRecording;			//�Ƿ�����¼��0��ʾû�У�1��ʾ����¼��
	char	bStream;				//�Ƿ�Ϊ��ʽ�ļ�����Ϊ��ʽ�ļ�ʱ���ͻ��˻�ʹ�ûطŵķ�ʽ�����ļ�����
	unsigned int ChnMask;		//ͨ�����룬��һ���ļ����ڶ��ͨ����¼��ʱ��ʹ��Щ����
	int 	nAlarmInfo;			//һ���ļ������ж�����������ļ��Ǳ����ļ�ʱ��Ч
}TTXRecFile_S, *LPTTXRecFile_S;

//TTXRecFile_S�ڵ�nAlarmInfo���壬��λ��ʾ������¼���ļ����ڶ������ʱʹ��
//�豸����¼�񱨾����Ͷ���
typedef enum
{
	TTX_FILE_ALARM_INFO_URGENCY_BUTTON  =0 ,		//������ť����
	TTX_FILE_ALARM_INFO_OVERSPEED 		=1 ,		//���ٱ���
	TTX_FILE_ALARM_INFO_LOWSPEED 		=2 ,		//���ٱ���
	TTX_FILE_ALARM_INFO_SHARK			=3 ,		//�񶯱���
	TTX_FILE_ALARM_INFO_TEMPERATOR 		=4 ,		//�¶ȱ���
	TTX_FILE_ALARM_INFO_TMOTION			=5 ,		//�ƶ���ⱨ��
	TTX_FILE_ALARM_INFO_UPS_CUT			=6 ,		//UPS���ϱ���
	TTX_FILE_ALARM_INFO_COLLISION		=7 ,		//��ײ�෭
	TTX_FILE_ALARM_INFO_FATIGUE			=8 ,		//ƣ�ͼ�ʻ
	TTX_FILE_ALARM_INFO_IO1				=9 ,		//IO1����
	TTX_FILE_ALARM_INFO_IO2				=10, 		//IO2����
	TTX_FILE_ALARM_INFO_IO3				=11,		//IO3����
	TTX_FILE_ALARM_INFO_IO4				=12, 		//IO4����
	TTX_FILE_ALARM_INFO_IO5				=13, 		//IO5����
	TTX_FILE_ALARM_INFO_IO6				=14, 		//IO6����
	TTX_FILE_ALARM_INFO_IO7				=15, 		//IO7����
	TTX_FILE_ALARM_INFO_IO8				=16, 		//IO8����
	TTX_FILE_ALARM_INFO_RAPID_ACCELERATION =17,		//�����ٸ澯 
	TTX_FILE_ALARM_INFO_RAPID_DECELERATION =18,		//�����ٸ澯 
	TTX_FILE_ALARM_INFO_REVERSING		 =19,		//�����澯 
	TTX_FILE_ALARM_INFO_CUS_OVER_SPEED	 =20,		//���ٸ澯 
}TTX_ALARM_REC_TYPE_E;

//�ļ���Ϣ
typedef struct _tagTTXFILEInfo_S
{
	int	nYear;			//��	2013
	int	nMonth;			//��	5
	int nDay;			//��	29
	int nBegHour;		//��ʼʱ��
	int nBegMinute;		
	int nBegSecond;
	_u64long u64BegPts;	//�ļ���ʼ��ʱ���
	unsigned int uiTotalMinSecond;	//�ļ���ʱ��������
	unsigned int uiAudioCodec;		//��Ƶ����������	TTX_AUDIO_TYPE_G726_40KBPS
	unsigned int uiAudioChannel;		//��Ƶͨ��
	unsigned int uiAudioSamplesPerSec;	//��Ƶ������
	unsigned int uiAudioBitPerSamples;	//��Ƶÿ��ȡ�������λԪ��
	unsigned int uiInfoCodec;		//��Ϣ֡������	TTX_INFO_CODEC_WKP
	unsigned int uiVideoCodec;		//��Ƶ֡������	TTX_VIDEO_CODEC_H264
	unsigned char ucResolution;		//�ֱ���		TTX_RESOLUTION_720P
	char szReserve[59];		//�����ֶ�
} TTXFILEInfo_S, *LPTTXFILEInfo_S;

//˵����˼����Ϊ
//uiAudioChannel = 1
//uiAudioSamplesPerSec = 8000
//uiAudioBitPerSamples = 16;

//֡��Ϣ
typedef struct _tagTTXFILEFrame_S
{
    _u64long u64Pts;	//֡ʱ���	��λ΢��		1΢�����һ�����֮һ��
    unsigned char	*pU8Data;   //֡����
    unsigned int	u32FrmSize; //֡����
    unsigned int	u32Type;    //֡����
    unsigned int	nChannel;	//��Ӧ��ͨ����Ϣ����Ϣ֡������֡����Ҫ����
    							//�ļ������Ӧ���ͨ������Ƶ���ݣ�����Ҫ����
} TTXFILEFrame_S, *LPTTXFILEFrame_S;

//������������
typedef struct _tagTTXConfigData_S
{
	int nLength;
	char cBuffer[2048];
} TTXConfigData_S, *LPTTXConfigData_S;

//�������
typedef struct _tagTTXNetParam_S
{
	unsigned char cMac[6];			//MAC��ַ
	unsigned char cLanIP[4];		//��������ַ
	unsigned char cLanMask[4];		//��������
	unsigned char cLanGateway[4];	//���ص�ַ
	int 	bAutoLogin;				//�Զ���¼
	char	szServerIP[64];			//��������ַ
	unsigned short usServerPort;	//�������˿�
	unsigned short usConnType;		//�������ͣ���ʱ��Ч
	unsigned short usWebPort;
	unsigned short usReserve;		//��������
	char szWebUrl[128];			//		ip:port/szWebUrl	
} TTXNetParam_S, *LPTTXNetParam_S;

//��ɫ����
typedef struct _tagTTXVideoColor
{
	int nExposure;		//�����
	int	nBrightness;	
	int	nConstract;	
	int	nHue;				
	int	nSaturate;			 
}TTXVideoColor_S, *LPTTXVideoColor_S;

//�Ự���ض˿�����
//ʹ��: 		�ڷ���������ǽ ˫�����ʱʹ�ã�������ֻ�����豸ָ���˿��ϴ�������
//Ĭ�϶˿�Ϊ0��Ϊ0��ʾ����
typedef struct _tagTTXSessPortBind
{
	unsigned short usRegister;	//ע��˿�
	unsigned short usUpgrade;	//�����˿�
	unsigned short usMainStream[TTX_MAX_CHANNEL];	//���������˿�����
	unsigned short usSubStream[TTX_MAX_CHANNEL];	//�������˿�����
	unsigned short usTalkback;	//˫��Խ��˿�
	unsigned short usMikeListen;	//��˼����˿�
	unsigned short usAudioListen[TTX_MAX_CHANNEL];	//���������˿�����
	unsigned short usRecSearch[TTX_MAX_SESS];	//¼���ļ�����
	unsigned short usFileDown[TTX_MAX_SESS];	//�ļ�����(¼���ͼƬ�ļ�����)
	unsigned short usPlayback[TTX_MAX_SESS];	//Զ�̻ط�
	unsigned short usSnapshot[TTX_MAX_SESS];	//ͼƬץ��
}TTXSessPortBind_S, *LPTTXSessPortBind_S;

//͸����ѯ���ݣ���ʱ���������ݰ�����1400�ֽڵ����
typedef struct _tagTTXTransQueryData_S
{
	int nLength;
	char cBuffer[1400];
} TTXTransQueryData_S, *LPTTXTransQueryData_S;

//�豸Ҫ���ص��ļ���Ϣ�����������豸�ϴ����ļ�
typedef struct _tagTTXUploadFileInfo
{
	int nFileType;		//�ļ����ͣ�1��ʾ�����ļ�TTX_DOWN_FILE_TYPE_UPGRADE
	char szParam[256];	//�м�ʹ�� _ �ָ�
	int nFileID;		//�ļ�ID
	char szFile[256];	//�ļ�·��
	char szIP[64];		//������IP
	unsigned short usPort;	//�˿�
	unsigned short usReserve;
	char szMd5[40];		//MD5У��
	char szReserve[32];	//��������
}TTXUploadFileInfo_S;

typedef struct _tagTTXMotionParam
{
	int	nMask[TTX_MOTION_MASK];	//��11λ��ʾ�ƶ����
	int	nSensitive;	//������
	unsigned char bEnable;	//�Ƿ�����
	char cReserve[3];
}TTXMotionParam_S, *LPTTXMotionParam_S;

typedef	struct _tagTTXStateInfoIndexHead
{
	unsigned int		unStateInfoflag; 			//״̬���ͱ�־λTTX_UPLOAD_STATES_INFO
	unsigned short usDataType;		//��������	��0λΪ1��ʾ����״̬��ϢTTXVehiStatus_S,

									//��1λΪ1GPS��ϢTTXGpsInfo_S,��2λΪ1IO״̬TTXIOStatus_S,��3λΪ1gsensor״̬TTXGsensorInfo_S	
	unsigned short usDataLen;		//���ݳ���
}TTXStateInfoIndexHead_S;

typedef struct _tagTTXGsensorInfo
{
	short sAccelerateX; 	//���ٶ�xֵ ����:1000 / Unit(��׼ֵ) =  1g
	short sAccelerateY; //���ٶ�yֵ
	short sAccelerateZ; //���ٶ�zֵ
	short sUnit;			//��׼ֵ (0����Ч)//��λ,��ֵ��ʾ1G
	int	nReserve[4];
}TTXGsensorInfo_S,*LPTTXGsensorInfo_S;


#pragma pack()

//����Ƶ���ݻص�����
//@nType	֡����
//@nLength	֡����
//@u64Stamp	ʱ���
//@pData	֡����
//@pUsr		�û��Զ�������
//����ֵ		TTX_NET_OK��ʾ����
//				TTX_NET_ERR_BUF_FULL��ʾ����������������
typedef int (* TTXPfnAVEncoderCB)(int nType, int nLength, _u64long u64Stamp, const char* pData, void* pUsr);

//�ļ����һص�����
//@pFile		¼���ļ�
//@pUsr		�û��Զ�������
typedef void(* TTXPfnRecFindCB)(LPTTXRecFile_S pFile, void* pUsr);

//�ж��Ƿ���Ҫ�˳�
//����true��ʾ�˳�
//�ļ����ҹ����У���Ҫ��ͣ���ô˺������ж��Ƿ���Ҫ�˳�
typedef bool (* TTXPfnGetExitCB)(void* pUsr);

//͸����ѯ�ص�����
//@pData	��ѯ���ص�����
//@pUsr		�û��Զ�������
typedef void(* TTXPfnTranQueryDataCB)(LPTTXTransQueryData_S pData, void* pUsr);

//808�Խ��õģ���ָ��͸������������
//@pData	��ѯ���ص�����
//@pUsr		�û��Զ�������
typedef void(* TTXPfnJT808UploadTransInstructionCB)(const char* pData, int nLength, void* pUsr);

//808�Խ��õģ���ѯ808��Ϣ��·�Ƿ�����
//@pUsr		�û��Զ�������
//@����true��ʾ���ߣ�false��ʾ����
typedef bool(* TTXPfnJT808CheckOnlineCB)(void* pUsr);


/**
 * @Description:����������
 * @Author: afu	2011-06-30
 */
class CTTXRecFile;
class CTTXFrameReader;
class LIBDVRNET_API CTTXNetWork
{
public:
	CTTXNetWork() 
	{
		memset(&m_GpsInfo, 0, sizeof(m_GpsInfo));
		m_GpsInfo.cGpsStatus = TTX_GPS_UNVALID;
		memset(&m_VehiState, 0, sizeof(m_VehiState));
		m_VehiState.bAccOpen = true;
		memset(&m_DiskStatus, 0, sizeof(m_DiskStatus));
		memset(&m_ModuleStatus, 0, sizeof(m_ModuleStatus));		
		m_ModuleStatus.bGpsExist = true;
		m_ModuleStatus.c3gState = TTX_3G_SIGNAL_NORMAL;
		memset(&m_Temperature, 0, sizeof(m_Temperature));
		memset(&m_IOStatus, 0, sizeof(m_IOStatus));
		memset(&m_ObdStatus, 0, sizeof(m_ObdStatus));
		memset(&m_PeopleStatus, 0, sizeof(m_PeopleStatus));
		memset(&m_ChannelStaus, 0, sizeof(m_ChannelStaus));
		
		memset(&m_Gsensorinfo, 0, sizeof(m_Gsensorinfo)); //Gsensor
		
		m_nGpsInterval = 10;		//Ĭ��GPS���ͼ��Ϊ10����
		m_nHeartInterval = 60;
		m_nTtsFlag = 0;
		m_nTtsParam = 0;
	}
	virtual ~CTTXNetWork(){}
	
public:
	/*****************************************************************************
	* @ ״̬���ַ�ʽ
	*		����A������SetGpsInfo�ӿ���������
	*		����B������GetGpsInfo�ӿڣ��ڻ�ȡʱ���и���
	******************************************************************************/
	//����GPS ��Ϣ���豸�ڱ仯ʱ���Լ�ʱ���и���
	//�ն���GPS��Ϣ�����仯ʱ��ʱ���ô˽ӿڽ��и���
	void	SetGpsInfo(const TTXGpsInfo_S& gps) {	m_GpsInfo = gps;	}
	//���³���״̬
	void	SetVehiStatus(const TTXVehiStatus_S& vehi) {	m_VehiState = vehi;}
	//����Ӳ��״̬
	void	SetDiskStatus(const TTXDiskStatus_S& disk) {	m_DiskStatus = disk;}
	//����ģ��״̬
	void	SetModuleStatus(const TTXModuleStatus_S& module) {	m_ModuleStatus = module;}
	//�����¶�״̬
	void	SetTemperature(const TTXTemperature_S& temperature) {	m_Temperature = temperature;}
	//��ȡ����GPS�������λ��
	int		GetGpsInterval() {	return m_nGpsInterval;	}
	//����GPS���
	void	SetGpsInterval(int nInterval) {	m_nGpsInterval = nInterval;	}
	//��ȡ�������(��)
	int		GetHeartInterval() {	return m_nHeartInterval;	}
	//�����������
	void	SetHeartInterval(int nSecond) {	m_nHeartInterval = nSecond;	}	
	void	SetIOStatus(const TTXIOStatus_S& io) {	m_IOStatus = io;}
	void	SetObdStatus(const TTXObdStatus_S& obd) {	m_ObdStatus = obd;}
	void	SetPeopleStatus(const TTXPeopleStatus_S& people) {	m_PeopleStatus = people;}
	//����ͨ��״̬��Ϣ
	void	SetChannelStatus(const TTXChannelStatus_S& channel) {	m_ChannelStaus = channel;}

	//����gsensor״̬
	void	SetGsensorStatus(const TTXGsensorInfo_S& Gsensor) {	m_Gsensorinfo = Gsensor;}
	
public:
	//�ж�״̬�Ƿ��ʼ���ˣ�ֻ�м��سɹ��󣬲Ż������������ͨ����·
	//����gps����û����ʱ���ϱ�״̬����������
	//�豸�Ͽ��Լ��������ԣ���gpsģ�����ʱ�����Դ�gpsģ���ȡ�����ݣ�����gps�Ƿ���Ч��
	//��������ģ��ʱ�����Դ�����ģ���ȡ������
	//���2���Ӻ��������ǲ����㣬��Ҳ���óɳ�ʼ��״̬�ɹ�
	virtual bool IsInitStatus() {	return true;	}
	//���״̬�仯ʱ����SetGpsInfo ��ʱ���и��£�����Ҫ���ش˽ӿ�
	//Ҳ�ڿ������ش˽ӿڣ����������Ҫʱ�����������ô˽ӿڻ�ȡGPS��Ϣ
	virtual TTXGpsInfo_S GetGpsInfo() { return m_GpsInfo;};
	//��ȡ����״̬
	virtual TTXVehiStatus_S GetVehiStatus() { return m_VehiState;};
	//��ȡӲ��״̬
	virtual TTXDiskStatus_S GetDiskStatus() { return m_DiskStatus;};
	//��ȡģ��״̬
	virtual TTXModuleStatus_S GetModuleStatus() { return m_ModuleStatus;};
	//��ȡ�¶�״̬
	virtual TTXTemperature_S GetTemperature() {	return m_Temperature;}	
	//����IO״̬��Ϣ
	virtual	TTXIOStatus_S GetIOStatus() {	return m_IOStatus;}
	//��ȡObd״̬
	virtual	TTXObdStatus_S GetObdStatus() {	return m_ObdStatus;}
	//��ȡ����ͳ��״̬
	virtual	TTXPeopleStatus_S GetPeopleStatus() {	return m_PeopleStatus;}
	//����ͨ��״̬��Ϣ
	virtual TTXChannelStatus_S GetChannelStatus() {	return m_ChannelStaus;}
	//��ȡ����汾��Ϣ
	//@szVersion: �汾��Ϣ
	//@nVerLen: szVersion����ĳ���, �ϲ㿽�����Ȳ��ó����˳���
	virtual void GetSoftwareVersion(char* szVersion, int nVerLen) {}
	//��ȡ��Ƶ״̬(��Ƶ��ʧ��¼��״̬)
	//@nVideoLost: ��0λ��ʾͨ��1,  ֵΪ1��ʾ��Ƶ��ʧ
	//@nVideoRecord: ��0λ��ʾͨ��1,  ֵΪ1��ʾ����¼��
	virtual void GetVideoStatus(int& nVideoLost, int& nVideoRecord) {}
	//��ȡ������Ϣ
	//@nDiskCount: ������Ŀ
	//@szDiskValue: 16000_8000_32000_8000 ��ʽ, ��λMB, 16000��ʾ���пռ�Ϊ16000MB, 8000��ʾʣ��ռ�Ϊ8000MB
	//          ���0_0  ���ʾӲ�̳���
	//		�м�ʹ��_   �ָ�
	//@nDiskValLen: szDiskValue����ĳ���, �ϲ㿽�����Ȳ��ó����˳���
	virtual void GetDiskInfo(int& nDiskCount, char* szDiskValue, int nDiskValLen) {}
	//��ȡ3G״̬
	//@n3GStatus: 0��ʾ��Ч��1��ʾ��Ч
	//@n3GType: ��������0��ʾ2G,  1��ʾEVDO,  2��ʾWCDMA, 3��ʾTD-WCDMA, 4 TD_LED , 5 FDD
	//@sz3GAddress: 3G�κź�ĵ�ַ
	virtual void Get3GStatus(int &n3GStatus, int& n3GType, char* sz3GAddress, int n3GAddrLen) {}
	//��ȡWIFI״̬
	//@nWifiStatus: 0��ʾ��Ч��1��ʾ��Ч
	//@szWifiAddress: WIFI  �������ַ
	//@nWifiAddrLen: WIFI  �������ַ
	virtual void GetWifiStatus(int &nWifiStatus, char* szWifiAddress, int nWifiAddrLen) {}
	//��ȡIO״̬
	//@nIOOutCount: IO�������
	//@nIOInCount: IO�������
	virtual void GetIOInfo(int& nIOOutCount, int& nIOInCount) {}
	////3g��4g�������Ѿ�ʹ�õ�����������Ϣ����λKB
	virtual void GetNetFlowInfo(unsigned int& ui3GFlow, unsigned int& ui4GFlow) {}

	//��ȡgsensor״̬
	virtual TTXGsensorInfo_S GetGsensorStatus() { return m_Gsensorinfo;};

public:
	//��¼��Ϣ֪ͨ
	//@bSuc: true��ʾ�������ͨ�ųɹ� false��ʾͨ���жϻ򲻳ɹ�
	//@bExistDevice: ��bSucΪtrueʱ��Ч�����Ϊtrue��ʾ�������Ѿ��������Ӧ���豸�����Ϊflase��ʾ������δ�����ص��豸
	virtual void DoLoginMsg(bool bSuc, bool bExistDevice) {}
	
	//��Ȩ����
	//@szSvrAuthKey�������·��ļ�Ȩ�룬�����жϴ˼�Ȩ���Ƿ�����һ���Ĺ���
	//		��������ʾ�������汾�ǶԵģ�������ԣ����豸�����ж�����
	//		Ȼ���ٶ�szSvrAuthKey���м��ܷ��ش����ݸ�������
	//		��������szDevAuthKey���ݽ��н���ƥ�䣬����������������ж�����
	//@szDevAuthKey�豸��szSvrAuthKey���м��ܺ󣬷��ظ�������������
	//@nDevAuthKeyLen����ʾszDevAuthKey�ĳ���(������Ȳ�����260���ֽ�)
	//�������ʧ�ܣ�����ж�����
	virtual bool DoAuthentication(const char* szSvrAuthKey, char* szDevAuthKey, int nDevAuthKeyLen) {	return true;	}
	
	/*****************************************************************************e
	* @ ����ָ��ҵ��
	******************************************************************************/
	//ָ���
	//TTS��������
	//���1���ϲ��ȵ���SetTtsParam�ٵ���DoTtsVoice
	//���2���ϲ�ֱ�ӵ���DoTtsVoice
	//nFlag����λ��ʾ
	//		0 ����
	//		1 ����
	//		2 1���ն���ʾ����ʾ
	//		3 1���ն�TTS ����
	//		4 1���������ʾ
	//		5 0�����ĵ�����Ϣ��1��CAN ��������Ϣ
	//nParam���� �ն���ʾ����ʾʱ��nParam��ʾ��ʾ������
	virtual void SetTtsParam(int nFlag, int nParam) {	m_nTtsFlag = nFlag;	m_nTtsParam = nParam;	}
	virtual bool DoTtsVoice(const char* szText) {		return false;	}
	//���Ϳ���ָ��
	//@nCtrlType: ��������
	virtual bool DoControl(int nCtrlType) {	return false;}
	//����GPS ���ͼ���������ڴ˽ӿ��д洢GPS���������Ϣ
	//@nSecond: ����
	virtual void DoSetGpsInterval(int nSecond) {}
	//PTZ����
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nCommand: ����ָ��
	//@nSpeed: �ٶ�
	//@nParam: ����
	virtual bool DoPtzContrl(int nChannel, int nCommand, int nSpeed, int nParam) {	return false;	}
	//��ȡ����Ԥ��λ
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nPresetNo: ��С����Ԥ�ú�
	virtual bool DoFreePresetGet(int nChannel, int& nPresetNO) {	return false;	}
	//��ȡ�ƶ�������
	//@nChannel: ͨ���Ŵ�0��ʼ
	virtual bool DoReadMotionParam(int nChannel,  TTXMotionParam_S* pMotion) {	return false;	}
	//�����ƶ�������
	virtual bool DoSetMotionParam(int nChannel, const TTXMotionParam_S* pMotion) {		return false;	}
	//���յ�͸����������
	virtual void DoRecvTransparentSerial(int nType, const unsigned char* pBuffer, int nLength) {	}
	//��ȡ��������
	//@nType: ��������
	//@pConfigData: ��������
	virtual bool DoGetConfig(int nType, LPTTXConfigData_S pConfigData) {	return false; 	}
	//���ò�������
	virtual bool DoSetConfig(int nType, const LPTTXConfigData_S pConfigData) {	return false;	}
	//��������͸��
	//@nType: ��������
	//@pInConfig: PC����Ĳ�����Ϣ
	//@pOutConfig: �豸���صĲ�����Ϣ
	virtual bool DoTransparentConfig(int nType, const LPTTXConfigData_S pInConfig, LPTTXConfigData_S pOutConfig) {	return false;	}
	//�ļ��ϴ����
	//@szFile: �ļ�������·��
	virtual void DoFileUploadFinish(const char* szFile) {	}
	//��ȡ��������������豸ʱʹ��
	//@netParam: �������
	virtual bool DoGetNetParam(TTXNetParam_S& netParam) {	return false;	}
	//��ֱ��ʱʵʱ��Ƶʱ��������ʾͨ�����Ƶ�������
	virtual bool DoGetChannelName(char* szChannelName, int nChnNameLen) {	return false;	}
	//�����������(ʹ�ù㲥�ķ�ʽ��������)
	//@Mac: �ϲ���Ҫ�ж�mac�Ƿ����豸��mac��ַһ��
	//@szIDNO: �ն˱��, �ϲ���Ҫ�ж��£��Ƿ����仯
	//@netParam: �������
	virtual bool DoSetNetParam(unsigned char Mac[6], const char* szIDNO, const TTXNetParam_S& netParam) {	return false;	}
	//��ȡ��ɫ����
	virtual bool DoGetVideoColor(int nChannel, LPTTXVideoColor_S pColor) {	return false;	}
	//������ɫ����
	virtual bool DoSetVideoColor(int nChannel, LPTTXVideoColor_S pColor) {	return false;	}
	//WIFI��������
	//@szUser: �û�����Ϣ����ʱ��Ч
	//@szPwd: ������Ϣ����ʱ��Ч
	//@szWifiSsid: Wifi SSID��Ϣ
	//@szWifiPwd: Wifi������Ϣ
	virtual bool DoSetWifiParam(const char* szUser, const char* szPwd, const char* szWifiSsid, const char* szWifiPwd) {	return false;	}

public:
	/*****************************************************************************
	* @ ý��ҵ��
	******************************************************************************/

	/*****************************************************************************
	//��ȡ��Ƶ����
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: TTX_STREAM_TYPE_MAIN �� TTX_STREAM_TYPE_SUB
	//@nVideoCoder: ��Ƶ����TTX_VIDEO_CODEC_H264 ��TTX_VIDEO_CODEC_H265
	//�����ͬͨ������Ƶ��ʽ��һ��ʱ�������ش˽ӿڣ�����ͨ��1��264��ͨ��2��265
	//�����ͬһ����Ƶ��ʽ������Ҫ����GetVideoParam�ӿ�
	******************************************************************************/
	virtual bool GetVideoParam(int nChannel, int nStreamType, int& nVideoCoder) {	return false;	}
	
	/*****************************************************************************
	//ȡ����Ƶͨ���ķֱ���
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: �������ͣ�ý������Ϊ��Ƶʱ��ЧTTX_STREAM_TYPE_MAIN
	//@nResolution: Ĭ�Ϸֱ���TTX_RESOLUTION_CIF
	//@nFrameBufLen: ֡���ȷ���0ʱ������SDK���������С
	//	 QCIF��CIFΪ300K����
	//    HD1��D1Ϊ1200K ����
	//    720PΪ4800K����
	//	1080PΪ19200K ����
	******************************************************************************/
	virtual bool GetVideoResolution(int nChannel, int nStreamType, int& nResolution, int& nFrameBufLen) {	nResolution = TTX_RESOLUTION_CIF; nFrameBufLen = 0;	return true;	}

	//��Ƶ�����ַ�ʽ
	//��ʽ1  ����InitFrameReader��FreeFrameReader�ӿڣ�sdkֱ��ʹ���ϲ��֡����
	//��ʽ2  ����StartAVEnc��StopAVEnc�ӿڣ��ϲ㽫֡����ͨ���ص��͵�sdk, sdk���и�֡����
	//�ȵ���InitFrameReader����ɹ��ˣ��򲻻��ٵ���StartAVEnc�ӿ�,���ʧ�ܣ�������StartAVEnc�ӿ�
	//���InitFrameReader�ɹ�����ֹͣ��ʱ�򣬻����FreeFrameReader
	
	/*****************************************************************************
	//��������Ƶ���룬����������ʵʱ��Ƶ����������ʱ�����ô˽ӿ�
	//@nMediaType: ý�����ͣ�TTX_MEDIA_TYPE_AV ����TTX_MEDIA_TYPE_AUDIO
	//@nChannel: ͨ���Ŵ�0��ʼ�����Ϊ��Ƶʱ��nChannel������Ϊ���ͨ��
	//@nStreamType: �������ͣ�ý������Ϊ��Ƶʱ��Ч
	//@ppReader: ����һ��CTTXFrameReader�������ڻ�ȡ֡����
	//����˽ӿڷ���true���򲻻��ٵ���StartAVEnc��StopAVEnc�����ӿ�
	//SDK�����ٿ���֡���棬���ϲ���л��棬��Ҫ������ߵ�Ч��
	******************************************************************************/
	virtual bool InitFrameReader(int nMediaType, int nChannel, int nStreamType, bool bDirectConnect, CTTXFrameReader** ppReader) {	return false;	}
		
	/*****************************************************************************
	//ֹͣ����Ƶ���룬������ֹͣʵʱ��Ƶ����������ʱ�����ô˽ӿ�
	//@nMediaType: ý�����ͣ�TTX_MEDIA_TYPE_AV ����TTX_MEDIA_TYPE_AUDIO
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: ��������
	//@pReader: ֡�����ȡ����
	******************************************************************************/
	virtual void FreeFrameReader(int nMediaType, int nChannel, int nStreamType, bool bDirectConnect, CTTXFrameReader* pReader) {	/*delete pReader; pReader = NULL;*/		}
	
	/*****************************************************************************
	//��������Ƶ���룬����������ʵʱ��Ƶ����������ʱ�����ô˽ӿ�
	//Ҳ��Ҫ֪����Ƶ�ĸ�ʽ����
	//@nMediaType: ý�����ͣ�TTX_MEDIA_TYPE_AV ����TTX_MEDIA_TYPE_AUDIO
	//@nChannel: ͨ���Ŵ�0��ʼ�����Ϊ��Ƶʱ��nChannel������Ϊ���ͨ��
	//@nStreamType: �������ͣ�ý������Ϊ��Ƶʱ��Ч
	//@pfnEncoderCB: ���ݻص�����
	//@pEncUsr: ����ص������û��Զ�������
	//@ppAVUsr: ��������û��Զ������ݣ����ظ�����⣬��StopAVEnc�����˲�������
	//�ϲ㱣��pfnEncoderCB��pUsr���ڱ����������ʱ��ͨ���˽ӿڸ��������
	//�ϲ㽫����Ƶ���ݰ�˳���͸������
	//�����ģ�鲻������Ƶ���ݣ����ͻ���������Ƶ�󣬲ŷ�����Ƶ
	******************************************************************************/
	virtual bool StartAVEnc(int nMediaType, int nChannel, int nStreamType, TTXPfnAVEncoderCB pfnEncoderCB, void* pEncUsr, void** ppAVUsr) {	return false;	}
		
	/*****************************************************************************
	//ֹͣ����Ƶ���룬������ֹͣʵʱ��Ƶ����������ʱ�����ô˽ӿ�
	//@nMediaType: ý�����ͣ�TTX_MEDIA_TYPE_AV ����TTX_MEDIA_TYPE_AUDIO
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: ��������
	//@pAVUsr: ��StartAVEnc���������pAVUsr����
	//���ô˽ӿں��ϲ����ֹͣ�������ݻص�����
	******************************************************************************/
	virtual bool StopAVEnc(int nMediaType, int nChannel, int nStreamType, void* pAVUsr) {	return false;	}

	/*****************************************************************************
	//�ı��������ͣ�ֱ���豸ʹ�ã�һ�㲻��Ҫ���ش˽ӿ�
	//@nMediaType: ý�����ͣ�TTX_MEDIA_TYPE_AV ����TTX_MEDIA_TYPE_AUDIO
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: ��������
	//@nNewStreamType: �µ���������
	//@pAVUsr: ��StartAVEnc���������pAVUsr����
	******************************************************************************/
	virtual void ChangeStreamType(int nMediaType, int nChannel, int nStreamType, int nNewStreamType, void* pAVUsr) {}

	/*****************************************************************************
	//����I֡
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nStreamType: ��������
	//��һ���µĿͻ������ӵ�ý�������ʱ��������Ҫ���豸���̲���һ��I֡����
	//����3G���紫��I֡���һ�㶼�Ƚϳ�����ʱ����I֡�������ÿͻ��˼�ʱ������Ƶ
	******************************************************************************/
	virtual bool AVEncIFrame(int nChannel, int nStreamType) { return false;	}

	/*****************************************************************************
	//��ȡ��Ƶ����ĸ�ʽ
	//@nChannel: ͨ���Ŵ�0��ʼ
	//@nAudioStreamType: TTX_AUDIO_STREAM_MIC �� TTX_AUDIO_STREAM_CAM,  TTX_AUDIO_STREAM_MICΪ�Խ�ʱʹ��
	//@nAudioCoder: ��Ƶ����TTX_AUDIO_TYPE_G726 ��
	//�����ͬͨ������Ƶ��ʽ��һ��������Խ�ʹ��g711����Ƶʹ��aac��������Щ�ӿ�
	//TTXNET_SetMediaInfo �ӿ����õ���ƽ̨�Խ�ʹ�õ���Ƶ��ʽ
	//�����ͬһ����Ƶ��ʽ������Ҫ����GetAudioParam�ӿ�
	******************************************************************************/
	virtual bool GetAudioParam(int nChannel, int nAudioStreamType, int& nAudioCoder) {	return false;	}

	/*****************************************************************************
	//����˫��Խ�
	//@nChannel: ͨ���Ŵ�0��ʼ����ʾ���ͨ������0��ʼ
	//@pfnEncoderCB: ����ص�
	//@pEncUsr: ����ص��û��Զ�������
	//@ppDecUsr: �û�����ص������庯������
	//˫��Խ�ʱ�����������ݲ�ͣͨ��pfnEncoderCB��֪ͨ�������
	//�豸������Ƶ������
	******************************************************************************/
	virtual bool StartTalkback(int nChannel, TTXPfnAVEncoderCB pfnEncoderCB, void* pEncUsr, void** ppTalkUsr) { 	return false;	}

	/*****************************************************************************
	//ֹͣ˫��Խ�
	//@nChannel: ͨ���Ŵ�0��ʼ����ʾ���ͨ������0��ʼ
	//@pTalkUsr: ��StartTalkback���������ppTalkUsr����
	//�豸���Թر���Ƶ������
	******************************************************************************/
	virtual bool StopTalkback(int nChannel, void* pTalkUsr) 	{		return false;	}
	
	/*****************************************************************************
	//���ý������Ƶ����,�˽ӿ���Ч,�ϲ���Բ�������
	//@nChannel: ���ͨ��
	//@nAudioType: ��Ƶ����TTX_AUDIO_TYPE_G726_40KBPS ��
	//@nFrmLength: ÿ����Ƶ֡�����ݳ���
	//@pTalkUsr: ��StartTalkback���������ppTalkUsr����
	******************************************************************************/
	virtual void TalkSetAudioParam(int nChannel, int nAudioType, int nFrmLength, void* pTalkUsr)	{}

	/*****************************************************************************
	//����Խ�����
	//@nLength: ��Ƶ����
	//@u64Stamp: ʱ���
	//@pData: ��Ƶ����
	//@pTalkUsr: ��StartTalkback���������ppTalkUsr����
	******************************************************************************/
	virtual void TalkDecoder(int nChannel, int nLength, _u64long u64Stamp, const char* pData, void* pTalkUsr)	{}

	/*****************************************************************************
	//�����ļ�����
	//@nYear: ��
	//@nMonth: ��
	//@nDay: ��
	//@nBeginTime: ��ʼʱ�䣬����Ϊ��λ
	//@nEndTime: ����ʱ�䣬����Ϊ��λ
	//@nRecType: ¼������
	//@nChannel: ¼���Ӧ��ͨ��
	//@pfnRecFindCB: �ļ��ص�����
	//@pFindUsr: �ļ������û��Զ�������
	//@pfnGetExitCB: �ж��Ƿ���Ҫ�˳�
	//@pExitUsr: �ж��˳�����
	//���������һ���ļ������̣߳�����¼���ļ�����
	//�ļ����ҹ����У���Ҫ��ͣ����pfnGetExitCB�����ж��Ƿ���Ҫ�˳�
	//���ҵ��ļ�����ʱ����pfnRecFindCB�������ϲ�
	//���ҹ����У�ÿ ��ѭ��Ӧ������usleep(0)������CPUռ���ʸ�
	******************************************************************************/
	virtual void FindRecFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	//֧�ֿ�������(CMSV6�ͻ��˲�֧�ֿ�������,�����������Ҫ���ش˽ӿ�)
	virtual void FindRecFileEx(int nYearS, int nMonthS, int nDayS, int nBeginTime, int nYearE, int nMonthE, int nDayE, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//������Ƶ�ļ�����
	//@nYear: ��
	//@nMonth: ��
	//@nDay: ��
	//@nBeginTime: ��ʼʱ�䣬����Ϊ��λ
	//@nEndTime: ����ʱ�䣬����Ϊ��λ
	//@nRecType: �ļ�����
	//@nChannel: ��Ƶ��Ӧ��ͨ��
	//@pfnRecFindCB: �ļ��ص�����
	//@pFindUsr: �ļ������û��Զ�������
	//@pfnGetExitCB: �ж��Ƿ���Ҫ�˳�
	//@pExitUsr: �ж��˳�����
	//���������һ���ļ������̣߳�����¼���ļ�����
	//�ļ����ҹ����У���Ҫ��ͣ����pfnGetExitCB�����ж��Ƿ���Ҫ�˳�
	//���ҵ��ļ�����ʱ����pfnRecFindCB�������ϲ�
	//���ҹ����У�ÿ ��ѭ��Ӧ������usleep(0)������CPUռ���ʸ�
	******************************************************************************/
	virtual void FindAudioFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nRecType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//����ͼƬ�ļ�����
	//@nYear: ��
	//@nMonth: ��
	//@nDay: ��
	//@nBeginTime: ��ʼʱ�䣬����Ϊ��λ
	//@nEndTime: ����ʱ�䣬����Ϊ��λ
	//@nType: �ļ�����
	//@nChannel: ¼���Ӧ��ͨ��
	//@pfnRecFindCB: �ļ��ص�����
	//@pFindUsr: �ļ������û��Զ�������
	//@pfnGetExitCB: �ж��Ƿ���Ҫ�˳�
	//@pExitUsr: �ж��˳�����
	//�ļ����ҹ����У���Ҫ��ͣ����pfnGetExitCB�����ж��Ƿ���Ҫ�˳�
	//���ҵ��ļ�����ʱ����pfnRecFindCB�������ϲ�
	******************************************************************************/
	virtual void FindJpegFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	
	/*****************************************************************************
	//������־�ļ�
	//@nYear: ��
	//@nMonth: ��
	//@nDay: ��
	//@nBeginTime: ��ʼʱ�䣬����Ϊ��λ
	//@nEndTime: ����ʱ�䣬����Ϊ��λ
	//@nType: �ļ�����
	//@nChannel: ¼���Ӧ��ͨ��
	//@pfnRecFindCB: �ļ��ص�����
	//@pFindUsr: �ļ������û��Զ�������
	//@pfnGetExitCB: �ж��Ƿ���Ҫ�˳�
	//@pExitUsr: �ж��˳�����
	//�ļ����ҹ����У���Ҫ��ͣ����pfnGetExitCB�����ж��Ƿ���Ҫ�˳�
	//���ҵ��ļ�����ʱ����pfnRecFindCB�������ϲ�
	******************************************************************************/
	virtual void FindLogFile(int nYear, int nMonth, int nDay, int nBeginTime, int nEndTime, int nType, int nChannel
					, TTXPfnRecFindCB pfnRecFindCB, void* pFindUsr, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//֪ͨ����¼���ļ����أ��ϲ�һ�㲻��Ҫ���ش˺���
	//@szFile: ¼���ļ�����
	//�������false����������ļ������أ��ϲ�һ�㲻��Ҫ���ش˺���
	******************************************************************************/
	virtual bool DownRecFile(const char* szFile) {	return true;	}

	/*****************************************************************************
	//��ȡ���ص��ļ���С���ϲ�һ�㲻��Ҫ���ش˺���
	//@szFile: ¼���ļ�����, szRealName��ʵ������
	//�������true����ʾ�ı������ص��ļ�����
	******************************************************************************/
	virtual bool GetDownFileRealName(const char* szFile, char* szRealName, int nRealNameLength) {	return false;	}

	/*****************************************************************************
	//��ȡ���ص��ļ�ƫ�ƣ��ϲ�һ�㲻��Ҫ���ش˺���
	//@szFile: ¼���ļ�����
	//�������0��ʾ���ļ�ͷ����ʼ���أ��������ƫ�ƴ���ʼ����
	******************************************************************************/
	virtual _u64long GetDownRecOffset(const char* szFile) {	return 0;	}

	/*****************************************************************************
	//��ȡ���ص��ļ���С���ϲ�һ�㲻��Ҫ���ش˺���
	//@szFile: ¼���ļ�����
	//�������0��ʾ���������ļ�����������ֵ��ʾ����ָ�����ȵ��ļ�
	******************************************************************************/
	virtual _u64long GetDownRecLenth(const char* szFile) {	return 0;	}
	
	/*****************************************************************************
	//�豸����ͼƬץ�Ĳ���������ͼƬ���浽�ļ���
	//�����ļ�·�����ظ������
	//����⽫����õ�ͼƬ���͵���������
	//@nChannel: ͨ����Ϣ
	//@szFileName: ͼƬ�ļ����ƣ�ȫ·��
	//@bDelete: ��ʾ�ļ��ϴ���ɺ��Ƿ�ִ��ɾ���ļ�����
	//�豸���Խ�ͼƬ�洢��Ӳ���ϣ�Ҳ���Դ洢���ڴ���
	//����豸û��Ӳ�̣�����洢���ڴ��ļ���
	******************************************************************************/
	virtual bool Snapshot(int nChannel, char* szFileName, bool& bDelete) {	return false;	}

	/*****************************************************************************
	//��ȡ�����ò�����ʹ�����������ļ�(��ָ���ĸ�ʽ) 
	//��ȡ���������ļ����������������ļ����ص��ͻ���
	//@szFileName: ���������ļ�����
	//@bDelete: ��ʾ�ļ��ϴ���ɺ��Ƿ�ִ��ɾ���ļ�����
	******************************************************************************/
	virtual bool GetConfigFile(char* szFileName, bool& bDelete) {	return false;	}

	/*****************************************************************************
	//��ȡ�����ò�����ʹ�����������ļ�(��ָ���ĸ�ʽ) 
	//�����豸���������ڿ���һ������ļ����Ƚ�С��
	//���ֱ���Ȼ������ڴ�
	******************************************************************************/
	virtual bool SetConfigFile( const char* pConfigBuf, int nBufLen ) {	return false;	}

	/*****************************************************************************
	//��������:   1��CheckUpgradeVer���ж������ļ��汾��Ϣ
						�ͻ�������ʱ�����ȴ��������汾��Ϣ���豸
					  2��GetUpgradeFile�����������ļ��洢·����
					  3���������������ļ������洢��������
					  4��CheckUpgradeFile��У�������ļ�
					  5��UpgradeDevice��У��ɹ���ִ������
	//��ȡ�����ļ�·��
	//���������ļ��Ĵ洢·��
	******************************************************************************/
	//У�������汾
	virtual bool CheckUpgradeVer(const char* szVer){	return true;	}
	//��ȡ�����ļ��洢·��
	virtual bool GetUpgradeFile(char* szFileName){	return false;	}
	//У�������ļ�
	virtual bool CheckUpgradeFile(const char* szFileName)	{	return false;	}
	//�����豸����
	virtual void UpgradeDevice(const char* szFileName)	{	}
	
	/*****************************************************************************
	//֪ͨ����¼��طŲ���
	//@szFile: ¼���ļ�����
	//@ppRecFile:�ϲ� ��Ҫ����¼������������෵�ظ�SDK��SDK���ô˶����ļ�������֡��Ϣ
	//�������false�����ʾ�ļ�������
	//��������
	//	1����InitRecFile��ȡ���ļ���������
	// 	2��pRecFile->OpenFile�������ļ�����������ļ��ӿ�
	//	3��pRecFile->GetFileInfo��ȡ���ļ���Ϣ
	//	4��pRecFile->ReadFrame����ȡ֡����
	******************************************************************************/
	virtual bool InitRecFile(CTTXRecFile** ppRecFile) {	return false;	}
	
	/*****************************************************************************
	//�ͷ��ļ���������
	//@pRecFile: ¼��������󣬴˶�����InitRecFile �ӿڴ���
	******************************************************************************/
	virtual void FreeRecFile(CTTXRecFile* pRecFile) {		}

	/*****************************************************************************
	//�ļ��ϴ�����:   	1��GetUploadFilePath����ȡ�ϴ��ļ��ı���·��
							2��SaveUploadFile���ļ��ϴ���ɺ󣬵���SaveUploadFile���ϲ���Զ��ļ�������Ӧ�Ĵ���
	//��ȡ�ļ��ϴ���·��
	******************************************************************************/
	//��ȡ�ļ��洢·��
	//@nFileType: �ļ�����	TTX_UPLOAD_FILE_TYPE_PICTURE
	//@szSvrFile: ��Ӧ�ڷ��������ļ�������
	//@szFileName: ����������ϲ㷵�ش洢���ļ�·��
	virtual bool GetUploadFilePath(int nFileType, const char* szParam, const char* szSvrFile, char* szSaveFileName)	{	return false;	}
	//�����ϴ����ļ�
	virtual void SaveUploadFile(const char* szFileName, const char* szMd5)	{	}

	/*****************************************************************************
	//͸����ѯ�ӿڣ����ڲ�ѯ�豸��־����Ϣ
	//@nType: ��ѯ����
	//@szParam: ��ѯ����
	//@pfnTranQueryData: ͸����ѯ�ص�����
	//@pFindUsr: ��ѯ�û��Զ�������
	//@pfnGetExitCB: �ж��Ƿ���Ҫ�˳�
	//@pExitUsr: �ж��˳�����
	//���������һ���ļ������̣߳�����¼���ļ�����
	//�ļ����ҹ����У���Ҫ��ͣ����pfnGetExitCB�����ж��Ƿ���Ҫ�˳�
	//���ҵ��ļ�����ʱ����pfnTranQueryData�������ϲ�
	//���ҹ����У�ÿ ��ѭ��Ӧ������usleep(0)������CPUռ���ʸ�
	******************************************************************************/
	virtual void TransQuery(int nType, const char* szParam, TTXPfnTranQueryDataCB pfnTranQueryData, void* pFindUsr
				, TTXPfnGetExitCB pfnGetExitCB, void* pExitUsr) {}

	/*****************************************************************************
	//ͬ��ʱ��(�����������ʱ��ͬ��)���豸��Ҫ���������ʱ�����ٸ��±��ص�ʱ��
	//����ΪUTC�Ǹ�������ʱ��, ȫ���׼ʱ�䣬ÿ�ε�¼�ɹ��󣬶������Уʱ����
	******************************************************************************/
	virtual void SyncTime(struct tm& utcTime) {}


protected:
	TTXGpsInfo_S	m_GpsInfo;		//GPSλ����Ϣ
	TTXVehiStatus_S	m_VehiState;	//����״̬��Ϣ
	TTXDiskStatus_S	m_DiskStatus;	//Ӳ��״̬
	TTXIOStatus_S	m_IOStatus;		//IO״̬
	TTXObdStatus_S m_ObdStatus;		//OBD״̬
	TTXPeopleStatus_S m_PeopleStatus;	//����ͳ��״̬
	TTXChannelStatus_S 	m_ChannelStaus;	//ͨ��״̬
	TTXModuleStatus_S	m_ModuleStatus;	//ģ��״̬
	TTXTemperature_S	m_Temperature;	//�¶�״̬
	int				m_nGpsInterval;		//GPS���ͼ������λ��
	int				m_nHeartInterval;	//�������ͼ��, ��λ��
	int				m_nTtsFlag;		//tts��־
	int				m_nTtsParam;	//tts����
	TTXGsensorInfo_S	m_Gsensorinfo; //gSensor��Ϣ
};

//�ļ��ط�ע������
//GetFileInfo���� _u64long u64BegPts; //�ļ���ʼ��ʱ�����Ϊ�ļ���һ֡��ʱ���
//ReadFrame֡�ӿ�ʱ�����ÿ��֡���ص�ʱ���( _u64long u64Pts;)��u64BegPts�ļ���ʼ��ʱ������бȶ�
//(u64Pts - u64BegPts)/1000 > uiTotalMinSecond�����ʾ�ļ����Ž�����
//Ҫע����Ƶ֡��ʱ���
class LIBDVRNET_API CTTXRecFile
{
public:
	CTTXRecFile() 
	{	
		memset(m_szRecFile, 0, sizeof(m_szRecFile));	
		m_usChnMask = 0;
	}
	virtual ~CTTXRecFile() {}

public:
	//����ҪԤ����ͨ����Ϣ,��һ��¼���ļ��ж��ͨ����¼��ʱ���˲�����Ч
	//��λ��ʾ��0λΪ1ʱ��ʾ��Ҫ��ȡͨ��1��Ƶ
	//����ļ�ֻ�е�ͨ����¼������Ҫ��עЩ�ӿ�
	//�ȵ���SetChnMask���ٵ���OpenFile
	virtual void SetChnMask(unsigned short usChnMask) {	m_usChnMask = usChnMask;	}
	//���ļ�
	//�ɹ�����true��ʧ�ܷ���false
	virtual bool OpenFile( const char *pU8FileName) = 0;
	//�ر��ļ�
	virtual bool CloseFile() = 0; 	
	//ȡ���ļ���Ϣ
	virtual void GetFileInfo(TTXFILEInfo_S* pFileInfo) = 0;
	//�ƶ����ļ�ͷ��
	virtual bool SeekBegin() = 0;
	//��ȡһ֡����
	//����Ƶ����Ƶ���Է���������Ϣ
	//�е���Ƶ֡���ݻ������GPS��Ϣ���뽫��Ҫ��GPS��Ϣ������Ϣ֡����
	virtual bool ReadFrame( TTXFILEFrame_S *pFrame1, TTXFILEFrame_S *pFrame2 ) = 0;
	//�ļ�ƫ��
	//nMinSecond ������ļ�ͷ������ʼʱ�䣬��λ����
	virtual bool SeekIFrame(int nMinSecond) = 0;
	//���ļ�ͷ������֡��Ϣ
	//���ڿ�ţ�ֻ����I֡
	virtual bool ForwardIFrame( TTXFILEFrame_S *pFrame1, TTXFILEFrame_S *pFrame2) = 0;
		//���ļ�
	//�ɹ�����true��ʧ�ܷ���false
	//���nChnMask��Ϊ0������nChnMaskΪ����������nChnΪ��
	virtual bool OpenTimeRange(int nChn, const struct tm& tmBeg, const struct tm& tmEnd) {	return false;	}

protected:
	char	m_szRecFile[256];
	unsigned short m_usChnMask;
};

class LIBDVRNET_API CTTXFrameReader
{
public:
	CTTXFrameReader(int nMediaType, int nChannel, int nStreamType) 
	{	
		m_nMediaType = nMediaType;
		m_nChannel = nChannel;
		m_nStreamType = nStreamType;
	}
	virtual ~CTTXFrameReader() {}

private:
	CTTXFrameReader();

public:
	//�ƶ������µĶ�ȡλ��
	//ʵʱ��Ƶʱ���ص����µ�һ��I֡��λ��
	//��Ƶ�������߶Խ�ʱ���ƶ������µ�һ����Ƶ֡��
	virtual void SeekNewestFrame(bool bIFrame) = 0;
	//��ȡ֡����
	//nType֡����	TTX_FRM_TYPE_I, TTX_FRM_TYPE_P, TTX_FRM_TYPE_A��
	//nLength֡����
	//u64Stampʱ���
	//pFrmBuf֡���棬ֱ�ӽ�֡���ݿ�����pFrmBuf��
	//nFBufLen����ʱ��ʾpFrmBuf�ĳ��ȣ�������ʱ��Ҫ�ж�ʵ�ʵ�֡����Ҫ��nFBufLenС
	//���ʵ�ʵ�֡����Ҫ��nFBufLen����Ҫ����false�����ҽ�nFBufLen��Ϊ��ʵ��֡����
	virtual bool ReadFrame(int& nType, int& nLength, _u64long& u64Stamp, char* pFrmBuf, int& nFBufLen) = 0;
	//��ȡ�����е�֡��Ŀ
	virtual int GetFrameNum() = 0;
	//��ȡ�����е�֡��ʱ�䳤��(��λ����)
	virtual long GetTotalTime() = 0;
	
protected:
	int 	m_nMediaType;
	int 	m_nChannel;
	int 	m_nStreamType;
};

#endif

