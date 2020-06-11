//
//  LibFunction.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "LibFunction.h"
#import "ttxdvrnetapi.h"
#import "ttxpttnetapi.h"
#import "iToast.h"
static long lpReadHeadle = 0;
static long lpReadHeadle2 = 0;


UIKIT_EXTERN NSString  const *SenderNameKey = @"SenderNameKey";
UIKIT_EXTERN NSString  const *FilePathKey = @"FilePathKey";

@interface LibFunction()

@property (nonatomic , strong) dispatch_semaphore_t semaphore_t;

@end



@implementation LibFunction

+(LibFunction *)libFunction
{
    static LibFunction *lib = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (lib == nil) {
            lib = [[LibFunction alloc] init];
             lib.semaphore_t = dispatch_semaphore_create(1);
        }
    });
    return lib;
}

//上传文件发送报警
#pragma mark - 上传图片 录像
-(void)sendUploadFile:(int)nFileType file:(const char*)szFile Id:( const char* _Nullable )szAlarmId
{
    TTXAlarmInfo_S armInfo = {0};
    armInfo.AlarmType = TTX_ALARM_TYPE_UPLOAD_FILE;
    armInfo.AlarmInfo = nFileType;
    char szTemp[256] = {0};
    struct tm tmTime = { 0 };
    time_t tNow = time(NULL);
    localtime_r(&tNow, &tmTime);
    if (nFileType == TTX_FILE_TYPE_REC)
    {
//        armInfo.Param[2] = _videoSecond;
    }else if(nFileType == TTX_FILE_TYPE_AUDIO)
    {
    }else
    {
        armInfo.Param[2] = 0; //文件时长(单位秒)，图片时无效
        sprintf(armInfo.szReserve,"%04d%02d%02d %02d%02d%02d",tmTime.tm_year % 100 + 2000,tmTime.tm_mon + 1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min,tmTime.tm_sec);
    }
    strcpy(armInfo.szDesc, szFile);
    NSString *filePath = [NSString stringWithUTF8String:szFile];
    NSData *data = [NSData dataWithContentsOfFile:filePath];
    armInfo.Param[0] = (int)data.length;    //文件长度
    armInfo.Param[1] = TTX_RECTYPE_NORMAL;    //文件类型，常规或者报警录像
    armInfo.Param[3] = 0;    //通道
    //上报对应的报警信息
    //流程是先上传报警，再上传报警对应的文件数据
    if (szAlarmId != NULL)
    {
        strcat(armInfo.szReserve, ";");
        strcat(armInfo.szReserve, szAlarmId);
    }
    BOOL result =  TTXNET_AddAlarmInfo(&armInfo);
    
    NSLog(@"sendUploadFile result = %d",result);
    if (result == 0) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [[iToast makeText:@"Uploading...."] show];
        });
    }
}
void CallBackFileUploadFinished(const char* szFile)
{
    //    NSString *file = [NSString stringWithUTF8String:szFile];
    NSLog(@"file CallBackFileUploadFinished");
    dispatch_async(dispatch_get_main_queue(), ^{
        [[iToast makeText:@"Upload Finish"] show];
    });
}

#pragma mark - 上传录音
-(void)pttnetapi_TTXPTT_UploadFile:(const char*)szFile group:(int)nGroup terminalID:(int)terminalID sec:(int)tSec pUser:(void* )pUser
{
//    TTX_FILE_AUDIO(4)表示音频文件
      int result = TTXPTT_UploadFile(&lpReadHeadle2, nGroup, terminalID, TTX_FILE_AUDIO, szFile, tSec, pUser, pttUploadFileReadInformation);
    if (result == 0) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [[iToast makeText:@"Uploading...."] show];
        });
    }
    NSLog(@" TTXPTT_UploadFile = %d",result);
}

static void pttUploadFileReadInformation(int nDataType, void* pData, void* pUsr)
{
    NSLog(@"nDataType = %d",nDataType);
    if (nDataType == TTX_PTT_READ_DATA_TYPE_FINISH) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [[iToast makeText:@"UploadFinish"] show];
        });
    }
    TTXPTT_CloseReadHandle(lpReadHeadle2);
}
#pragma mark - 下载录音
//收到录音,下载并播放
-(BOOL)pttnetapi_TTXPTTDownFile:(const char*)szUrl savePath:(const char*)szSavePath pUser:(void*)pUser success:(FileSuccess)dfSuccess
{
    _dfSuccess = dfSuccess;
    //信号量为1 单线程 以后可以改多线程
    dispatch_semaphore_wait(self.semaphore_t, DISPATCH_TIME_FOREVER);
    return  TTXPTT_DownFile(&lpReadHeadle, szUrl, szSavePath, pUser, pttDownFileReadInformation);
}
//回调
static void pttDownFileReadInformation(int nDataType, void* pData, void* pUsr)
{
    if(nDataType == TTX_PTT_READ_DATA_TYPE_FINISH)
    {
        [LibFunction libFunction].dfSuccess((__bridge NSDictionary*)pUsr);
        NSLog(@"成功");
    }else if (nDataType == TTX_PTT_READ_DATA_TYPE_FAILED)
    {
        NSLog(@"失败");
    }
    TTXPTT_CloseReadHandle(lpReadHeadle);
    dispatch_semaphore_signal([LibFunction libFunction].semaphore_t);
}



@end
