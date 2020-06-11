//
//  TTXAudioRecord.h
//  gMonitor
//
//  Created by Apple on 13-11-7.
//  Copyright (c) 2013年 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
//#import "SKYAudioPlay.h"

#define AUDIO_BUFFER_AAC_SIZE                              1024
#define AUDIO_BUFFER_NOR_SIZE                              320
#define AUDIO_PLAY_BUFFERS_NUMBER                        3
//这部分已经修改为c输出aac格式
@class TTXAudioRecord;
@protocol TTXAudioRecordDelegate <NSObject>
- (void)recordAudio:(TTXAudioRecord *)record inBuffer:(void*)buffer length:(int)len;
@end

@interface TTXAudioRecord : NSObject
{
    AudioQueueRef d_audio_recording;  //输出音频播放队列
    AudioQueueBufferRef d_audio_recording_buffers[AUDIO_PLAY_BUFFERS_NUMBER];  //输出音频缓存
    BOOL isRecording;
    
}



// Volume
@property (nonatomic, assign)       float                           volLDB;
@property (nonatomic, assign)       float                           volRDB;
@property (nonatomic, assign) BOOL outputAAC;

@property(nonatomic, assign) id<TTXAudioRecordDelegate> delegate;

-(instancetype)initWithoutputACC:(BOOL)isaac;

- (BOOL) startRecord:(BOOL)isaac;
- (BOOL) stopRecord;
@end
