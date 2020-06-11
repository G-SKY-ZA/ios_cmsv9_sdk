//
//  RecordHelper.m
//  cmsv9
//
//  Created by tongtianxing on 2018/11/23.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import "RecordHelper.h"



@implementation RecordHelper


-(instancetype)init
{
    self = [super init];
    if (self) {
    
    }
    return self;
}




-(void)configAudioWithUrl:(NSString*)audioUrl
{
    AVAudioSession * session = [AVAudioSession sharedInstance];
    NSError *setCategoryError = nil;
    [session setCategory:AVAudioSessionCategoryPlayAndRecord error:&setCategoryError];
    [session setActive:YES error:nil];
    if (setCategoryError) {
        NSLog(@"%@",[setCategoryError description]);

    }
    //录音设置
    NSMutableDictionary * recordSetting = [[NSMutableDictionary alloc]init];
    //设置录音格式
    [recordSetting  setValue:[NSNumber numberWithInt:kAudioFormatMPEG4AAC] forKey:AVFormatIDKey];
    //设置录音采样率（HZ）
    [recordSetting setValue:[NSNumber numberWithFloat:8000] forKey:AVSampleRateKey];
    //录音通道数
    [recordSetting setValue:[NSNumber  numberWithInt:1] forKey:AVNumberOfChannelsKey];
//    //线性采样位数
//    [recordSetting  setValue:[NSNumber numberWithInt:8] forKey:AVLinearPCMBitDepthKey];
//    //录音的质量
//    [recordSetting  setValue:[NSNumber numberWithInt:AVAudioQualityHigh] forKey:AVEncoderAudioQualityKey];
    
     NSError *error;
//    audioFile = audioUrl;
    NSURL *url = [NSURL fileURLWithPath:audioUrl];
    _audioFile = audioUrl;
    recorder = [[AVAudioRecorder alloc]initWithURL:url settings:recordSetting error:&error];
        //开启音量检测
    recorder.meteringEnabled = YES;
    recorder.delegate = self;
    
    
}


-(void)startRecoder
{
    if([recorder prepareToRecord]){
        [recorder record];
        [self performSelector:@selector(stopRecoder) withObject:nil afterDelay:60];
        if (timer) {
            [timer invalidate];
            timer = nil;
        }
    if (timer == nil) {
    
        timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(averagePowerForChannel) userInfo:nil repeats:YES];
//          __weak typeof(self) weakSelf = self;
//        timer = [NSTimer scheduledTimerWithTimeInterval:0.1 repeats:YES block:^(NSTimer * _Nonnull timer) {
//            RecordHelper *strongHelper = weakSelf;
//           [strongHelper->recorder updateMeters];
//            CGFloat power = [strongHelper->recorder averagePowerForChannel:0];
//            [weakSelf.delegate RecordHelper:weakSelf averagePowerForChannel:power];
//    }];
    }
    }
}
-(void)averagePowerForChannel
{
    [recorder updateMeters];
    CGFloat power = [recorder averagePowerForChannel:0];
    [self.delegate RecordHelper:self averagePowerForChannel:power];
}


-(NSInteger)stopRecoder
{
    if (timer) {
        [timer invalidate];
        timer = nil;
    }
    if (recorder.isRecording) {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(stopRecoder) object:nil];
    NSInteger cTime = recorder.currentTime;
    [recorder stop];
        NSLog(@"录音完毕");
    if (cTime > 1) {
        return cTime;
    }else {
        [recorder deleteRecording];
        return 0;
    }
    }
    return 0;
}

-(void)cancleRecoder
{
    if (recorder.isRecording) {
    if (timer) {
        [timer invalidate];
        timer = nil;
    }
    //删除录制文件
    [recorder deleteRecording];
    [recorder stop];
            }
}

-(BOOL)helperIsRecording
{
    return recorder.isRecording;
}






@end
