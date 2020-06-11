#ifndef _TTX_TYPE_DEF_H_
#define _TTX_TYPE_DEF_H_

#define TTX_MAX_PATH 	260

//֡���Ͷ���
#define TTX_FRM_TYPE_I			0		//I֡
#define TTX_FRM_TYPE_P			1		//P֡
#define TTX_FRM_TYPE_A			2		//��Ƶ֡
#define TTX_FRM_TYPE_INFO		3		//��Ϣ֡

#define TTX_RESOLUTION_QCIF				1	//�ֱ���
#define TTX_RESOLUTION_CIF				2	//�ֱ���
#define TTX_RESOLUTION_HD1				3	//�ֱ���
#define TTX_RESOLUTION_D1				4	//�ֱ���
#define TTX_RESOLUTION_720P				5	//�ֱ���
#define TTX_RESOLUTION_1080P			6	//�ֱ���

#ifdef WIN32

	#pragma warning(disable:4786)
	#include <WINSOCK2.H>
	#include <WINDOWS.H>
	
	#define _u64long unsigned __int64


	#define snprintf _snprintf
	#define _strncasecmp strnicmp
	#define _strcasecmp stricmp

#else

	#define _u64long unsigned long long

	#include <netinet/in.h>
	#include <string.h>

	#define _strncasecmp strncasecmp
	#define _strcasecmp strcasecmp

	
#endif

#ifndef NULL
	#define NULL 0
#endif	

#endif
