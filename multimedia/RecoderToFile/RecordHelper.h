//
//  RecordHelper.h
//  cmsv9
//
//  Created by tongtianxing on 2018/11/23.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
//录音保存到文件中
NS_ASSUME_NONNULL_BEGIN
@class RecordHelper;
@protocol RecoderHelperDelegate <NSObject>

-(void)RecordHelper:(RecordHelper*)helper averagePowerForChannel:(CGFloat)power;

@end



@interface RecordHelper : NSObject <AVAudioRecorderDelegate>
{
     AVAudioRecorder *recorder;//录音的对象
    NSTimer *timer;
}
@property (nonatomic , copy)NSString *audioFile;
@property (nonatomic , assign)id<RecoderHelperDelegate> delegate;

-(void)configAudioWithUrl:(NSString*)audioUrl;
-(void)startRecoder;
//结束返回录音时间
-(NSInteger)stopRecoder;
-(void)cancleRecoder;

-(BOOL)helperIsRecording;

@end

NS_ASSUME_NONNULL_END
