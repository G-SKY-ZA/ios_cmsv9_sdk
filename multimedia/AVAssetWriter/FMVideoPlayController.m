//
//  FMVideoPlayController.m
//  fmvideo
//
//  Created by qianjn on 2016/12/30.
//  Copyright © 2016年 SF. All rights reserved.
//

#import "FMVideoPlayController.h"
#import <MediaPlayer/MediaPlayer.h>
#import <AVFoundation/AVFoundation.h>
#import <AssetsLibrary/AssetsLibrary.h>

NSNotificationName const NotificationVideoFinish = @"NotificationVideoFinish";//当前群组名

@interface FMVideoPlayController ()
{
    NSString *videoFile;
}
@property (nonatomic, strong) MPMoviePlayerController *videoPlayer;
@property (nonatomic, strong) NSString *from;

@property (nonatomic, strong) UIImage *videoCover;
@property (nonatomic, assign) NSTimeInterval enterTime;
@property (nonatomic, assign) BOOL hasRecordEvent;

@end

@implementation FMVideoPlayController

- (BOOL)prefersStatusBarHidden{
    return YES;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    self.videoPlayer = [[MPMoviePlayerController alloc] init];
    [self.videoPlayer.view setFrame:self.view.bounds];
    self.videoPlayer.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [self.view addSubview:self.videoPlayer.view];
    [self.videoPlayer prepareToPlay];
    self.videoPlayer.controlStyle = MPMovieControlStyleNone;
    self.videoPlayer.shouldAutoplay = YES;
    self.videoPlayer.repeatMode = MPMovieRepeatModeOne;
    self.title = NSLocalizedString(@"PreView", nil);
    
    
    self.videoPlayer.contentURL = self.videoUrl;
    [self.videoPlayer play];
    
    [self buildNavUI];
    _enterTime = [[NSDate date] timeIntervalSince1970];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(captureFinished:) name:MPMoviePlayerThumbnailImageRequestDidFinishNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stateChanged) name:MPMoviePlayerPlaybackStateDidChangeNotification object:nil];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(videoFinished:) name:MPMoviePlayerPlaybackDidFinishNotification object:self.videoPlayer];
    
    NSString *fileStr = [self.videoUrl absoluteString];
    //file:///var/mobile/Containers/Data/Application/A8A86C3F-26D5-4D65-9883-E4F6A86A7778/Documents/videoFolder/dong2-2018-11-27-17-00-13.mp4
    ///var/mobile/Containers/Data/Application/079944F0-77FD-4848-AC77-2C768193578E/Documents/videoFolder/dong1-2018-11-27-17-05-00.mp4
    if ([fileStr hasPrefix:@"file://"]) {
        fileStr = [fileStr stringByReplacingOccurrencesOfString:@"file://" withString:@""];
        videoFile = fileStr;
    }
    videoFile = self.videoUrl.path;
    
    
    
    
}

- (void)buildNavUI
{
    UIImageView *imageView = [[UIImageView alloc] init];
    imageView.image = [UIImage imageNamed:@"video_play_nav_bg"];
    
//    if (Is_Iphone_X) {
//        imageView.frame = CGRectMake(0, IphoneX_StatusBar_Top, kScreenWidth, 44);
//    }else{
    CGRect bounds = [UIScreen mainScreen].bounds;
    
    
         imageView.frame = CGRectMake(0, 0, bounds.size.width, 44);
//    }
    
   
    imageView.userInteractionEnabled = YES;
    
    UIButton *cancelBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [cancelBtn addTarget:self action:@selector(dismissAction) forControlEvents:UIControlEventTouchUpInside];
    [cancelBtn setImage:[UIImage imageNamed:@"cancel"] forState:UIControlStateNormal];
    cancelBtn.frame = CGRectMake(0, 0, 44, 44);
    [imageView addSubview:cancelBtn];
    
    UIButton *Done = [UIButton buttonWithType:UIButtonTypeCustom];
    [Done addTarget:self action:@selector(DoneAction) forControlEvents:UIControlEventTouchUpInside];
    [Done setTitle:@"Done" forState:UIControlStateNormal];
    Done.frame = CGRectMake(bounds.size.width - 70, 0, 50, 44);
    [imageView addSubview:Done];
    
    self.navigationController.navigationBar.hidden = YES;
    [self.view addSubview:imageView];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
   
//      [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
}



- (void)commit
{
    
}

#pragma mark - notification
#pragma state
- (void)stateChanged
{
    switch (self.videoPlayer.playbackState) {
        case MPMoviePlaybackStatePlaying:
            [self trackPreloadingTime];
            break;
        case MPMoviePlaybackStatePaused:
            break;
        case MPMoviePlaybackStateStopped:
            break;
        default:
            break;
    }
}

-(void)videoFinished:(NSNotification*)aNotification{
    int value = [[aNotification.userInfo valueForKey:MPMoviePlayerPlaybackDidFinishReasonUserInfoKey] intValue];
    if (value == MPMovieFinishReasonPlaybackEnded) {   // 视频播放结束
      
    }
}


- (void)trackPreloadingTime
{
    
}

- (void)dismissAction
{
    [self.videoPlayer stop];
    
  
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if([fileManager fileExistsAtPath:videoFile])
    {
        NSError *error;
     BOOL reuslt =  [fileManager removeItemAtPath:videoFile error:&error];
        NSLog(@"remove the file = %d",reuslt);
    }
    self.videoPlayer = nil;
    [self.navigationController popViewControllerAnimated:YES];
    //[self.navigationController dismissViewControllerAnimated:YES completion:nil];

}
- (void)DoneAction
{
    NSInteger time =  self.videoPlayer.duration;
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    [[NSNotificationCenter defaultCenter]postNotificationName:NotificationVideoFinish object:nil userInfo:@{@"VideoFile":videoFile,@"VideoTime":@(time)}];
}
- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.videoPlayer stop];
    self.videoPlayer = nil;
//    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
}


- (void)captureImageAtTime:(float)time
{
    [self.videoPlayer requestThumbnailImagesAtTimes:@[@(time)] timeOption:MPMovieTimeOptionNearestKeyFrame];
}

- (void)captureFinished:(NSNotification *)notification
{
    self.videoCover = notification.userInfo[MPMoviePlayerThumbnailImageKey];
    if (self.videoCover == nil) {
        self.videoCover = [self coverIamgeAtTime:1];
    }
}


- (UIImage*)coverIamgeAtTime:(NSTimeInterval)time {
    
    
    [self.videoPlayer requestThumbnailImagesAtTimes:@[@(time)] timeOption:MPMovieTimeOptionNearestKeyFrame];
    
    AVURLAsset *asset = [[AVURLAsset alloc] initWithURL:self.videoUrl options:nil];
    AVAssetImageGenerator *assetImageGenerator =[[AVAssetImageGenerator alloc] initWithAsset:asset];
    assetImageGenerator.appliesPreferredTrackTransform = YES;
    assetImageGenerator.apertureMode = AVAssetImageGeneratorApertureModeEncodedPixels;
    
    CGImageRef thumbnailImageRef = NULL;
    CFTimeInterval thumbnailImageTime = time;
    NSError *thumbnailImageGenerationError = nil;
    thumbnailImageRef = [assetImageGenerator copyCGImageAtTime:CMTimeMake(thumbnailImageTime, 60)actualTime:NULL error:&thumbnailImageGenerationError];
    
    if(!thumbnailImageRef)
        NSLog(@"thumbnailImageGenerationError %@",thumbnailImageGenerationError);
    
    UIImage*thumbnailImage = thumbnailImageRef ? [[UIImage alloc]initWithCGImage: thumbnailImageRef] : [UIImage new];
    
    return thumbnailImage;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
