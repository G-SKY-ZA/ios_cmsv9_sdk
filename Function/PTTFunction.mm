//
//  PTTFunction.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/28.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "PTTFunction.h"
#import "TTXAudioRecord.h"
#import "ttxpttnetapi.h"
#import "iToast.h"
#import "ttxpttservice.h"

#import "TMAudioDecoder.h"

#import "PCMPlayer.h"

@interface PTTFunction()<TTXAudioRecordDelegate,TMAudioDecoderDelegate>
{
    BOOL bTalk;//正在讲话
    
    TMAudioDecoder *aacDecoder;
    PCMPlayer  *pcmPlayer;
}
@property (nonatomic , strong)TTXAudioRecord *pttRecord;
@end

@implementation PTTFunction

+(PTTFunction*)pttFunction
{
    static PTTFunction *ptt = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (ptt == nil) {
            ptt = [[PTTFunction alloc]init];
        }
    });
    return ptt;
}

-(int)pttStartFunction
{
    if (_pttRecord == nil) {
        _pttRecord =[[TTXAudioRecord alloc]initWithoutputACC:YES];
    }
    if (bTalk == false) {
        bTalk = true;
          int ret = TTXPTT_RequestTalk(bTalk);
        
         if (ret == 0) {//成功获取话语权
         
             _pttRecord.delegate = self;
             [_pttRecord startRecord:YES];
              [self performSelector:@selector(pttStopFunction) withObject:nil afterDelay:30];
         }else{
             bTalk = false;
         }
        return ret;
    }
    return -1;
}
-(void)pttStopFunction
{
     if (bTalk) { //如果再对讲才执行结束
         [_pttRecord stopRecord];
         bTalk = false;
           TTXPTT_RequestTalk(bTalk);
         _pttRecord.delegate = nil;
          [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(pttStopFunction) object:nil];
     }
}

#pragma mark - TTXAudioRecordDelegate 录音回调
- (void)recordAudio:(TTXAudioRecord *)record inBuffer:(void*)buffer length:(int)len
{
    //获取到音频数据
    if (bTalk) {
        NSInteger time = [self getTickCount];
        TTXPttWorkIns()->SendTalkAacFrame((const char*)buffer, len , time * 1000);//传输
        
    }else{
        bTalk = false;
        TTXPTT_RequestTalk(bTalk);
        [_pttRecord stopRecord];
    }
}

-(NSInteger)getTickCount
{
    static  NSDateFormatter *formatter = nil;
    if (formatter == nil) {
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init] ;
        
        [formatter setDateStyle:NSDateFormatterMediumStyle];
        
        [formatter setTimeStyle:NSDateFormatterShortStyle];
        
        [formatter setDateFormat:@"YYYY-MM-dd HH:mm:ss SSS"]; // ----------设置你想要的格式,hh与HH的区别:分别表示12小时制,24小时制
        
        NSTimeZone* timeZone = [NSTimeZone systemTimeZone];
        
        [formatter setTimeZone:timeZone];
    }
    NSDate *datenow = [NSDate date];
    
    return [datenow timeIntervalSince1970];
}


#pragma mark - CTTXPttService服务器回调
////接收到讲话音频
////@nTerminalID: 终端ID，表示那个终端在讲话
////@bStart: true表示开始,false表示停止
#pragma mark - PTT对讲回调
static iToast *itoast = nil;
void CallBackPttAudioTalk(int nGroupID, int nTerminalID, int bTalk)
{
    NSLog(@"CallBackPttAudioTalk bTalk = %d",bTalk);
    if (bTalk) {
        dispatch_async(dispatch_get_main_queue(), ^{
//            [terminalView startAACDecoderAndPlayer];
            [[PTTFunction pttFunction] startAACDecoderAndPlayer];
            itoast = [iToast makeText:@"somebody is talking"];
            [itoast setDuration:30*1000];
            [itoast show];
        });
    }else{
        dispatch_async(dispatch_get_main_queue(), ^{
//            [terminalView stopAACDecoderAndPlayer];
            [[PTTFunction pttFunction] stopAACDecoderAndPlayer];  //有个小bug
            [itoast removeToast:nil];
            itoast = nil;
        });
    }
}
////接收到讲话音频
////@nGroupID: 群组ID
////@nTerminalID: 终端ID
////@nAudioIndex: 音频索引，每次讲话时，从0开始
////@pAudio: 音频数据
////@nLength: 音频长度
void CallBackPttAudioFrame(int nGroupID, int nTerminalID, int nAudioIndex, const char* pBuffer, int nLength)
{
     NSData *audioData = [NSData dataWithBytes:pBuffer length:nLength];
    [[PTTFunction pttFunction] decoderAAC:audioData];
}


#pragma mark -  声音播放接口
-(void)startAACDecoderAndPlayer
{
    aacDecoder = [[TMAudioDecoder alloc]initWithConfig:nil];
    aacDecoder.delegate = [PTTFunction pttFunction];
    pcmPlayer = [[PCMPlayer alloc]init];
}
#pragma mark -  TMAudioDecoderDelegate
//解码回调
- (void)audioDecodeCallback:(NSData *)pcmData
{
    [pcmPlayer playWithData:pcmData];
}


//解码
-(void)decoderAAC:(NSData *)data
{
    //If the AAC data has a ADTS header, then the header needs to be skipped.
    NSUInteger len = [data length];
    [aacDecoder decodeAudioAACData:[data subdataWithRange:NSMakeRange(7, len-7)]];
    
}

-(void)stopAACDecoderAndPlayer
{
    aacDecoder = nil;
    pcmPlayer = nil;
}


@end
