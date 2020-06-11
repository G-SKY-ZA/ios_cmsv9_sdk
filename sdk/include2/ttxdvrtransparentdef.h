#ifndef _TTX_DVR_TRANSPARENT_DEF_H_
#define _TTX_DVR_TRANSPARENT_DEF_H_

//胎压数据透传定义
#define TTX_TRANSPARENT_TYPE_TPMS		101			//胎压数据透传定义，胎压大概3分钟传送一次就好了

#pragma pack(4)

//胎压定义(20个胎压)
typedef struct _tagTTXTirePressure
{
	unsigned char ucTireBattery;	//电量0-5V，55=5.5V
	char ucTirePress;		//胎压,  23 = 2.3PA，正常范围一般是2.3 - 2.5
	short ucTireTemperure;	//温度200 表示20度	
}TTXTirePress_S;

typedef struct _tagTTXTireStatus
{
	unsigned char ucTireCount;	//胎压的个数
	unsigned char ucReserve[3];	
	TTXTirePress_S arrPress[20];	//
}TTXTireStatus_S;

#define TTX_TRANSPARENT_TYPE_CARINFO		0x00000092			//胎压数据透传定义，胎压大概3分钟传送一次就好了




//刷卡透传
typedef struct CarRecord
{
	char szCarID[32];		//卡号
	char cYear;				//2000年开始
	char cMonth;
	char cDay;
	char cHour;
	char cMin;
	char cSec;
	char cPatch;			//0 - 为实时, 1 - 补传
	char reseved1;
	int	nJingDu;						//经度	4字节 整数部分	9999999 = 9.999999 
	int	nWeiDu;							//纬度	4字节 整数部分	9999999 = 9.999999
	char reseved2[32];
}CarInfo_S, *LPCarInfo_S;

#define TTX_TRANSPARENT_TYPE_GSENSOR		0x00000093			//gSensor消息 传的是SensorHead_S+SensorInfo_S


typedef struct _tagTTXGSenSorHead_S
{
	int nType;			
	int nSecond;		//秒数,范围0-86400,3600*hour+60*min+sec
	short nDataCount;	//数量
	short nDataSize;	//大小
	//后面跟TTXGSenSorInfo_S的数组,nDataCount个
}TTXGSenSorHead_S;

typedef struct _tagTTXGSenSorInfo_S
{
	short AccelerateX;
	short AccelerateY;
	short AccelerateZ;
	short Uint;
}TTXGSenSorInfo_S;

//GSENSOR透传报警类型
#define TTX_TRANSPARENT_GSENSOR_ALARM_START	1
#define TTX_TRANSPARENT_GSENSOR_ALARM_END	2


typedef struct _tagTTXGSenSorALarmInfo_S
{
	int nAlarmType;
	char	szDesc[256];		//报警描述	
	char cReserve[64];	//保留参数 
}TTXGSenSorAlarmInfo_S;



#pragma pack()

#endif
