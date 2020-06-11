//
//  TTXAudioRecord.m
//  gMonitor
//
//  Created by Apple on 13-11-7.
//  Copyright (c) 2013年 Apple. All rights reserved.
//

#import "TTXAudioRecord.h"
#import <AVFoundation/AVFoundation.h>
#import <CoreAudio/CoreAudioTypes.h>

enum ChannelCount
{
    k_Mono = 1,
    k_Stereo
};
static int          pcm_buffer_size = 0;
static uint8_t      pcm_buffer[2048*2];


AudioConverterRef               __encodeConvertRef = NULL;   ///< convert param
AudioStreamBasicDescription     __targetDes;                 ///< destination format


@interface TTXAudioRecord ()
{
    AudioStreamBasicDescription dataFormat;

    
}

@end


@implementation TTXAudioRecord

//Howard 2013-07-29 修改函数名，并加上static ,限于本文件使用 //MyAudioQueueInputCallback
static void HowardAudioQueueInputCallback (void *                          inUserData,
                                           AudioQueueRef                   inAQ,
                                           AudioQueueBufferRef             inBuffer,
                                           const AudioTimeStamp *          inStartTime,
                                           UInt32                          inNumberPacketDescriptions,
                                           const AudioStreamPacketDescription *inPacketDescs) {
    TTXAudioRecord *audioRecord = (__bridge TTXAudioRecord *)(inUserData);

    //audioRecord->PlayRecord();
    //[a talk: inBuffer->mAudioData];
       // 由于PCM转成AAC的转换器每次需要有1024个采样点（每一帧2个字节）才能完成一次转换，所以每次需要2048大小的数据，这里定义的pcm_buffer用来累加每次存储的bufferData
    if (audioRecord.outputAAC) {
    float channelValue[2];
    caculate_bm_db(inBuffer->mAudioData, inBuffer->mAudioDataByteSize, 0, 1, channelValue,true);
    audioRecord.volLDB = channelValue[0];
    audioRecord.volRDB = channelValue[1];
    memcpy(pcm_buffer+pcm_buffer_size, inBuffer->mAudioData, inBuffer->mAudioDataByteSize);
    pcm_buffer_size = pcm_buffer_size + inBuffer->mAudioDataByteSize;
    
    if(pcm_buffer_size >= 2048){
        AudioBufferList *bufferList = convertPCMToAAC(audioRecord);
        
        memcpy(pcm_buffer, pcm_buffer + 2048, pcm_buffer_size - 2048);
        pcm_buffer_size = pcm_buffer_size - 2048;
    
        if (audioRecord.delegate != Nil) {
            int ioHeaderLen = 0;
            char * adtsHeader = newAdtsDataForPacketLength(bufferList->mBuffers[0].mDataByteSize, &ioHeaderLen);
            char mData[2048];
            memset(mData, 0, 2048);
            memcpy(mData, adtsHeader, ioHeaderLen);
            memcpy(mData+ioHeaderLen, bufferList->mBuffers[0].mData, bufferList->mBuffers[0].mDataByteSize);
            
            NSLog(@"volLDB = %f volLDB = %f",audioRecord.volLDB,audioRecord.volRDB);
        if (audioRecord.delegate != Nil){
    [audioRecord.delegate recordAudio:audioRecord inBuffer:mData length:bufferList->mBuffers[0].mDataByteSize + ioHeaderLen];
            }
        if(bufferList) {
            free(bufferList->mBuffers[0].mData);
            free(bufferList);
        }
    }
    }
    }else{
            if (audioRecord.delegate != Nil) {
                [audioRecord.delegate recordAudio:audioRecord inBuffer:inBuffer->mAudioData length:AUDIO_BUFFER_NOR_SIZE];
            }
    }
        
    AudioQueueEnqueueBuffer(inAQ, inBuffer, 0, NULL);
}

//给aac加上adts头, packetLength 为rawaac的长度 //某些时候转出来的音频不能播放k可能是没有家adts头
char *newAdtsDataForPacketLength(int packetLength, int *ioHeaderLen) {
    //adts头的长度为固定的7个字节
    int adtsLen = 7;
    //在堆区分配7个字节的内存
    char *packet = malloc(sizeof(char)*adtsLen);
    //选择AAC LC
    int profile = 1;
    //选择采样率对应的下标
    int freqIdx = 11;
    //选择声道数所对应的下标
    int chanCfg = 1;
    //获取adts头和raw aac的总长度
    NSUInteger fullLength = adtsLen+packetLength;
    //设置syncword
    packet[0] = 0xFF;
    packet[1] = 0xF1;
    packet[2] = (char)(((profile-1)<<6)+(freqIdx<<2)+(chanCfg>>2));
    packet[3] = (char)(((chanCfg&3)<<6)+(fullLength>>11));
    packet[4] = (char)((fullLength&0x7FF)>>3);
    packet[5] = (char)(((fullLength&7)<<5)+0x1F);
    packet[6] = (char)0xFC;
    *ioHeaderLen = adtsLen;
    return packet;
}


-(instancetype)init{
    self = [super init];
    if (self) {
          [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error: nil];
        const AudioStreamBasicDescription asbd = {8000.0, kAudioFormatLinearPCM, 12, 2, 1, 2, 1, 16, 0};
        dataFormat = asbd;
        // 编码器转码设置
//        if (_outputAAC) {
//            NSString *err = [self convertBasicSetting];
//            if (err != nil) {
//                NSString *error = nil;
//                for (int i = 0; i < 3; i++) {
//                    usleep(100*1000);
//                    error = [self convertBasicSetting];
//                    if (error == nil) break;
//                }
//                // if init this class failed then restart three times , if failed again,can handle at there
//                //        [self exitWithErr:error];
//            }
//        }
                AudioQueueNewInput(&asbd, HowardAudioQueueInputCallback , (__bridge void *)(self), nil, nil, 0, &d_audio_recording);
//        for (int i = 0; i < AUDIO_PLAY_BUFFERS_NUMBER; i++) {
//            AudioQueueAllocateBuffer(d_audio_recording, AUDIO_BUFFER_SIZE, &d_audio_recording_buffers[i]);//音频队列创建了一个缓冲区
////          
//        }
    }
    return self;
}

-(instancetype)initWithoutputACC:(BOOL)isaac
{
    self = [super init];
    if (self) {
        [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error: nil];
        const AudioStreamBasicDescription asbd = {8000.0, kAudioFormatLinearPCM, 12, 2, 1, 2, 1, 16, 0};
        dataFormat = asbd;
        // 编码器转码设置
        if (isaac) {
        NSString *err = [self convertBasicSetting];
        if (err != nil) {
            NSString *error = nil;
            for (int i = 0; i < 3; i++) {
                usleep(100*1000);
                error = [self convertBasicSetting];
                if (error == nil) break;
            }
        }
        }
        _outputAAC = isaac;
        AudioQueueNewInput(&asbd, HowardAudioQueueInputCallback , (__bridge void *)(self), nil, nil, 0, &d_audio_recording);
        }
    return self;
}












- (BOOL) startRecord:(BOOL)isaac {
    if (!isRecording) {
        memset(pcm_buffer, 0, pcm_buffer_size);
        pcm_buffer_size = 0;
        for (int i = 0; i < AUDIO_PLAY_BUFFERS_NUMBER; i++) {
            if (_outputAAC) {
            AudioQueueAllocateBuffer(d_audio_recording, AUDIO_BUFFER_AAC_SIZE, &d_audio_recording_buffers[i]);//音频队列创建了一个缓冲区
            }else{
             AudioQueueAllocateBuffer(d_audio_recording, AUDIO_BUFFER_NOR_SIZE, &d_audio_recording_buffers[i]);//音频队列创建了一个缓冲区
            }
            
            AudioQueueEnqueueBuffer(d_audio_recording, d_audio_recording_buffers[i], 0, nil);
        }
        AudioQueueSetParameter(d_audio_recording, kAudioQueueParam_Volume,  1.0);
        AudioQueueStart(d_audio_recording, NULL);
        isRecording = YES;
        return YES;
    } else {
        return NO;
    }
}

- (BOOL) stopRecord {
    if (isRecording) {
        AudioQueueFlush(d_audio_recording);
        AudioQueueStop(d_audio_recording,  0);
        
        for (int i = 0; i < AUDIO_PLAY_BUFFERS_NUMBER; i++) {
            AudioQueueFreeBuffer(d_audio_recording, d_audio_recording_buffers[i]);
        }
//        AudioQueueDispose(d_audio_recording, YES);//函数释放一个音频队列的时候，这个音频队列释放掉它拥有的缓冲区
        
//        if (!_outputAAC) {
//
//        }
        
        isRecording = NO;
        

        return YES;
    } else {
        return NO;
    }
}
-(void)dealloc
{
    NSLog(@"TTXAudioRecord delloc");
//    for (int i = 0; i < AUDIO_PLAY_BUFFERS_NUMBER; i++) {
//        AudioQueueFreeBuffer(d_audio_recording, d_audio_recording_buffers[i]);
//    }
    AudioQueueDispose(d_audio_recording, NO);//函数释放一个音频队列的时候，这个音频队列释放掉它拥有的缓冲区
  
    if(__encodeConvertRef != NULL && _outputAAC) {
        //        log4cplus_info("Audio Recoder", "release _encodeConvertRef.");
        AudioConverterDispose(__encodeConvertRef);
        __encodeConvertRef = NULL;
    }
}

// Transcoder basic information settings,转码器基本信息设置
- (NSString *)convertBasicSetting {
    // 此处目标格式其他参数均为默认，系统会自动计算，否则无法进入encodeConverterComplexInputDataProc回调
    AudioStreamBasicDescription sourceDes = dataFormat;
    AudioStreamBasicDescription targetDes;
    // 设置目标格式及基本信息
    memset(&targetDes, 0, sizeof(targetDes));
    targetDes.mFormatID                   = kAudioFormatMPEG4AAC;
    targetDes.mSampleRate                 = 8000.0;
    targetDes.mChannelsPerFrame           = dataFormat.mChannelsPerFrame;
    targetDes.mFramesPerPacket            = 1024;
    // 采集的为AAC需要将targetDes.mFramesPerPacket设置为1024，AAC软编码需要喂给转换器1024个样点才开始编码，这与回调函数中inNumPackets有关，不可随意更改

    
    OSStatus status     = 0;
    UInt32 targetSize   = sizeof(targetDes);
    status              = AudioFormatGetProperty(kAudioFormatProperty_FormatInfo, 0, NULL, &targetSize, &targetDes);
    //    log4cplus_info("pcm", "create target data format status:%d",(int)status);
    
    memset(&__targetDes, 0, sizeof(__targetDes));
    memcpy(&__targetDes, &targetDes, targetSize);
    
    // select software coding,选择软件编码
    AudioClassDescription audioClassDes;
    status = AudioFormatGetPropertyInfo(kAudioFormatProperty_Encoders,
                                        sizeof(targetDes.mFormatID),
                                        &targetDes.mFormatID,
                                        &targetSize);
    //    log4cplus_info("pcm","get kAudioFormatProperty_Encoders status:%d",(int)status);
    // 计算编码器容量
    UInt32 numEncoders = targetSize/sizeof(AudioClassDescription);
    // 用数组存放编码器内容
    AudioClassDescription audioClassArr[numEncoders];
    // 将编码器属性赋给数组
    AudioFormatGetProperty(kAudioFormatProperty_Encoders,
                           sizeof(targetDes.mFormatID),
                           &targetDes.mFormatID,
                           &targetSize,
                           audioClassArr);
    //    log4cplus_info("pcm","wrirte audioClassArr status:%d",(int)status);
    // 遍历数组，设置软编
    for (int i = 0; i < numEncoders; i++) {
        if (audioClassArr[i].mSubType == kAudioFormatMPEG4AAC && audioClassArr[i].mManufacturer == kAppleSoftwareAudioCodecManufacturer) {
            memcpy(&audioClassDes, &audioClassArr[i], sizeof(AudioClassDescription));
            break;
        }
    }
    // 防止内存泄露
    if (__encodeConvertRef == NULL) {
        // 新建一个编码对象，设置原，目标格式
        status          = AudioConverterNewSpecific(&sourceDes, &targetDes, 1,
                                                    &audioClassDes, &__encodeConvertRef);
        
        if (status != noErr) {
            //            log4cplus_info("Audio Recoder","new convertRef failed status:%d \n",(int)status);
            return @"Error : New convertRef failed \n";
        }
    }
    
    targetSize      = sizeof(sourceDes);
    status          = AudioConverterGetProperty(__encodeConvertRef, kAudioConverterCurrentInputStreamDescription, &targetSize, &sourceDes);
    //    log4cplus_info("pcm","get sourceDes status:%d",(int)status);
    
    targetSize      = sizeof(targetDes);
    status          = AudioConverterGetProperty(__encodeConvertRef, kAudioConverterCurrentOutputStreamDescription, &targetSize, &targetDes);
    //    log4cplus_info("pcm","get targetDes status:%d",(int)status);
    
    // 设置码率，需要和采样率对应
    UInt32 bitRate  = 8000.0;
    targetSize      = sizeof(bitRate);
    status          = AudioConverterSetProperty(__encodeConvertRef,
                                                kAudioConverterEncodeBitRate,
                                                targetSize, &bitRate);
    //    log4cplus_info("pcm","set covert property bit rate status:%d",(int)status);
    if (status != noErr) {
        //        log4cplus_info("Audio Recoder","set covert property bit rate status:%d",(int)status);
        return @"Error : Set covert property bit rate failed";
    }
    
    return nil;
}

// PCM -> AAC
AudioBufferList* convertPCMToAAC (TTXAudioRecord *recoder) {
    
    UInt32   maxPacketSize    = 0;
    UInt32   size             = sizeof(maxPacketSize);
    OSStatus status;
    
    status = AudioConverterGetProperty(__encodeConvertRef,
                                       kAudioConverterPropertyMaximumOutputPacketSize,
                                       &size,
                                       &maxPacketSize);
    //    log4cplus_info("AudioConverter","kAudioConverterPropertyMaximumOutputPacketSize status:%d \n",(int)status);
    
    AudioBufferList *bufferList             = (AudioBufferList *)malloc(sizeof(AudioBufferList));
    bufferList->mNumberBuffers              = 1;
    bufferList->mBuffers[0].mNumberChannels = __targetDes.mChannelsPerFrame;
    bufferList->mBuffers[0].mData           = malloc(maxPacketSize);
    bufferList->mBuffers[0].mDataByteSize   = 2048;
    
    AudioStreamPacketDescription outputPacketDescriptions;
    
    // inNumPackets设置为1表示编码产生1帧数据即返回，官方：On entry, the capacity of outOutputData expressed in packets in the converter's output format. On exit, the number of packets of converted data that were written to outOutputData. 在输入表示输出数据的最大容纳能力 在转换器的输出格式上，在转换完成时表示多少个包被写入
    UInt32 inNumPackets = 1;
    // inNumPackets设置为1表示编码产生1024帧数据即返回
    // Notice : Here, due to encoder characteristics, 1024 frames of data must be given to the encoder in order to complete a conversion, 在此处由于编码器特性,必须给编码器1024帧数据才能完成一次转换,也就是刚刚在采集数据回调中存储的pcm_buffer
    status = AudioConverterFillComplexBuffer(__encodeConvertRef,
                                             encodeConverterComplexInputDataProc,
                                             pcm_buffer,
                                             &inNumPackets,
                                             bufferList,
                                             &outputPacketDescriptions);
    
    if(status != noErr){
        //        log4cplus_debug("Audio Recoder","set AudioConverterFillComplexBuffer status:%d inNumPackets:%d \n",(int)status, inNumPackets);
        free(bufferList->mBuffers[0].mData);
        free(bufferList);
        return NULL;
    }
//
//    if (recoder.needsVoiceDemo) {
//        // if inNumPackets set not correct, file will not normally play. 将转换器转换出来的包写入文件中，inNumPackets表示写入文件的起始位置
//        OSStatus status = AudioFileWritePackets(recoder.mRecordFile,
//                                                FALSE,
//                                                bufferList->mBuffers[0].mDataByteSize,
//                                                &outputPacketDescriptions,
//                                                recoder.mRecordPacket,
//                                                &inNumPackets,
//                                                bufferList->mBuffers[0].mData);
//        //        log4cplus_info("write file","write file status = %d",(int)status);
//        if (status == noErr) {
//            recoder.mRecordPacket += inNumPackets;  // 用于记录起始位置
//        }
//    }
    
    return bufferList;
}

#pragma mark ---------------------------------- CallBack : collect pcm and  convert  -------------------------------------
OSStatus encodeConverterComplexInputDataProc(AudioConverterRef              inAudioConverter,
                                             UInt32                         *ioNumberDataPackets,
                                             AudioBufferList                *ioData,
                                             AudioStreamPacketDescription   **outDataPacketDescription,
                                             void                           *inUserData) {
    
    ioData->mBuffers[0].mData           = inUserData;
    ioData->mBuffers[0].mNumberChannels = __targetDes.mChannelsPerFrame;
    ioData->mBuffers[0].mDataByteSize   = 1024 * 2 * __targetDes.mChannelsPerFrame;
    *ioNumberDataPackets = 1;
    
    return 0;
}

void caculate_bm_db(void * const data ,size_t length ,int64_t timestamp, enum ChannelCount channelModel,float channelValue[2],bool isAudioUnit) {
    int16_t *audioData = (int16_t *)data;
    
    if (channelModel == 1) {
        int     sDbChnnel     = 0;
        int16_t curr          = 0;
        int16_t max           = 0;
        size_t traversalTimes = 0;
        
        if (isAudioUnit) {
            traversalTimes = length/2;// 由于512后面的数据显示异常  需要全部忽略掉
        }else{
            traversalTimes = length;
        }
        
        for(int i = 0; i< traversalTimes; i++) {
            curr = *(audioData+i);
            if(curr > max) max = curr;
        }
        
        if(max < 1) {
            sDbChnnel = -100;
        }else {
            sDbChnnel = (20*log10((0.0 + max)/32767) - 0.5);
        }
        
        channelValue[0] = channelValue[1] = sDbChnnel;
        
    } else if (channelModel == k_Stereo){
        int sDbChA = 0;
        int sDbChB = 0;
        
        int16_t nCurr[2] = {0};
        int16_t nMax[2] = {0};
        
        for(unsigned int i=0; i<length/2; i++) {
            nCurr[0] = audioData[i];
            nCurr[1] = audioData[i + 1];
            
            if(nMax[0] < nCurr[0]) nMax[0] = nCurr[0];
            
            if(nMax[1] < nCurr[1]) nMax[1] = nCurr[0];
        }
        
        if(nMax[0] < 1) {
            sDbChA = -100;
        } else {
            sDbChA = (20*log10((0.0 + nMax[0])/32767) - 0.5);
        }
        
        if(nMax[1] < 1) {
            sDbChB = -100;
        } else {
            sDbChB = (20*log10((0.0 + nMax[1])/32767) - 0.5);
        }
        
        channelValue[0] = sDbChA;
        channelValue[1] = sDbChB;
    }
}



@end
