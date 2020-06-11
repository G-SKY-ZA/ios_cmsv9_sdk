//
//  DownRecordPlayer.m
//  cmsv9
//
//  Created by tongtianxing on 2018/12/3.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import "DownRecordPlayer.h"
#import <AVFoundation/AVFoundation.h>
#import "LibFunction.h"
#import "iToast.h"
@interface DownRecordPlayer ()<AVAudioPlayerDelegate>
{
//    iToast *itoast;
}
@property (nonatomic , strong) AVAudioPlayer *recordPlayer;

@property (nonatomic , strong) NSMutableArray *playList;

@property (nonatomic , strong) NSLock *lock;

@property (nonatomic , strong) NSDictionary *cFileDict;//当前播放文件

@property (nonatomic , strong) iToast *itoast;


@end

@implementation DownRecordPlayer




+(DownRecordPlayer*)player
{
    static DownRecordPlayer *player = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (player == nil) {
            player = [[DownRecordPlayer alloc]init];
        }
    });
    return player;
}
-(instancetype)init
{
    self = [super init];
    if (self) {
          [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(audioSessionInterruptionNotification:) name:AVAudioSessionInterruptionNotification object:nil];
    }
    return self;
}


-(void)dealloc
{
    [[NSNotificationCenter defaultCenter]removeObserver:self];
}
-(NSLock *)lock
{
    if (_lock == nil) {
        _lock = [[NSLock alloc]init];
    }
    return _lock;
}
-(NSMutableArray *)playList
{
    if (_playList == nil) {
        _playList = [[NSMutableArray alloc]init];
    }
    return _playList;
}
//显示
-(void)showSenderIToast:(BOOL)flat
{
    
    NSLog(@"showSenderIToast = %d",flat);
 
    if (_itoast) {
            [_itoast removeToast:nil];
            _itoast = nil;
        }
        if (flat) {
            if (_cFileDict) {
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    NSString *text = [NSString stringWithFormat:@"%@:播放录音",self->_cFileDict[SenderNameKey]];
                    self->_itoast = [iToast makeText:text];
                    //                [iToast makeText:[NSString stringWithFormat:@"%@:播放录音",_cFileDict[SenderNameKey]]];
                    [self->_itoast setDuration:NSIntegerMax];
                    [self->_itoast show];
                    NSLog(@"%@",text);
                });

            }
        }

    
    
  
    

    
}


-(void)appendRecordAudioFileDict:(NSDictionary *)fileDict
{
    [self.lock lock];
    NSString *path = fileDict[FilePathKey];
//    NSString *name = fileDict[SenderNameKey];
    [self.playList addObject:fileDict];
    if (_recordPlayer == nil) {
    _cFileDict = fileDict;
    [self setNextAudio:path];
    }
    [self.lock unlock];
}
-(void)setNextAudio:(NSString *)path
{
    _recordPlayer = [[AVAudioPlayer alloc]initWithContentsOfURL:[NSURL fileURLWithPath:path] error:nil];
    _recordPlayer.delegate = self;
    [_recordPlayer prepareToPlay];
    [_recordPlayer play];
    [self showSenderIToast:true];
}
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    [self.lock lock];
    if (flag) {
        NSLog(@"flag 1");
//        NSString *path = player.url.path;
        [self.playList removeObject:_cFileDict];
        if (self.playList.count == 0) {
            [self endOfPlayer];
            [self.lock unlock];
            return;
        }
        NSDictionary *newDict = [self.playList firstObject];
        NSString *newPath = newDict[FilePathKey];
        _cFileDict = newDict;
        [self setNextAudio:newPath];
        NSLog(@"setNextAudio = %@",newPath);

    }else{
         NSLog(@"flag 0");
        [self endOfPlayer];
    }
    [self.lock unlock];
}

-(void)endOfPlayer
{
    [_recordPlayer stop];
    _recordPlayer = nil;
    _recordPlayer.delegate = nil;
    [self.playList removeAllObjects];
    self.playList = nil;
     [self showSenderIToast:false];
}

/* if an error occurs while decoding it will be reported to the delegate. */
- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError * __nullable)error
{
     [_recordPlayer stop];
}
#pragma mark - audioSessionNotification
-(void)audioSessionInterruptionNotification:(NSNotification*)notification
{
    /*
     监听到的中断事件通知,AVAudioSessionInterruptionOptionKey
     
     typedef NS_ENUM(NSUInteger, AVAudioSessionInterruptionType)
     {
     AVAudioSessionInterruptionTypeBegan = 1, 中断开始
     AVAudioSessionInterruptionTypeEnded = 0,  中断结束
     }
     */
    if (_recordPlayer == nil) {
        return;
    }
     int type = [notification.userInfo[AVAudioSessionInterruptionOptionKey] intValue];
    switch (type) {
        case AVAudioSessionInterruptionTypeBegan: // 被打断
            [_recordPlayer pause]; // 暂停播放
            [self showSenderIToast:false];
            break;
        case AVAudioSessionInterruptionTypeEnded: // 中断结束
            [_recordPlayer play];  // 继续播放
            [self showSenderIToast:true];
            break;
        default:
            break;
    }
}



@end
