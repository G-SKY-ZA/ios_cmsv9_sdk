//
//  ImagePickerHelper.h
//  cmsv9
//
//  Created by tongtianxing on 2018/11/23.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
//拍照
@protocol ImagePickerHelperDelegate <NSObject>

-(void)captureSuccess:(BOOL)isSuccess;

//-(void)videoSuccess:(BOOL)isSuccess duration:(CGFloat)duration;暂时不需要

@end

@interface ImagePickerHelper : NSObject<UINavigationControllerDelegate,UIImagePickerControllerDelegate>

@property (nonatomic , assign)CGFloat videoSec;
@property (nonatomic , copy) NSString *imageUrl;
@property (nonatomic , copy) NSString *videoUrl;
@property (nonatomic , assign)id<ImagePickerHelperDelegate> delegate;

- (void)showImagePickerForSourceType:(UIImagePickerControllerSourceType)sourceType andCameraCaptureMode:(UIImagePickerControllerCameraCaptureMode)mode;



@end

NS_ASSUME_NONNULL_END
