//
//  FMWriteVideoController.m
//  FMRecordVideo
//
//  Created by qianjn on 2017/3/15.
//  Copyright © 2017年 SF. All rights reserved.
//
//  Github:https://github.com/suifengqjn
//  blog:http://gcblog.github.io/
//  简书:http://www.jianshu.com/u/527ecf8c8753

#import "FMWriteVideoController.h"
#import "FMWVideoView.h"
#import "FMVideoPlayController.h"
@interface FMWriteVideoController ()<FMWVideoViewDelegate>
@property (nonatomic, strong)FMWVideoView *videoView;
@property (nonatomic, copy)NSString *videoName;
@end

@implementation FMWriteVideoController

- (BOOL)prefersStatusBarHidden{
    return YES;
}

-(instancetype)initWithVideoName:(NSString*)videoName
{
    self = [super init];
    if (self) {
        _videoName = videoName;
    }
    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationController.navigationBar.hidden = YES;
    _videoView  =[[FMWVideoView alloc] initWithFMVideoViewType:TypeFullScreen videoName:_videoName];
    _videoView.delegate = self;
    [self.view addSubview:_videoView];
    self.view.backgroundColor = [UIColor blackColor];
}


- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    if (_videoView.fmodel.recordState == FMRecordStateFinish) {
        [_videoView.fmodel reset];
    }
    
    
//      [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    //隐藏=YES,显示=NO; Animation:动画效果
//    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
}

- (void)dismissVC
{
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
}


- (void)recordFinishWithvideoUrl:(NSURL *)videoUrl
{
    FMVideoPlayController *playVC = [[FMVideoPlayController alloc] init];
    playVC.videoUrl =  videoUrl;
    [self.navigationController pushViewController:playVC animated:YES];
}


@end
