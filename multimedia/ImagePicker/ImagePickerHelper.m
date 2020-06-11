//
//  ImagePickerHelper.m
//  cmsv9
//
//  Created by tongtianxing on 2018/11/23.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import "ImagePickerHelper.h"
#import <MobileCoreServices/MobileCoreServices.h>
#import <AVFoundation/AVFoundation.h>

@implementation ImagePickerHelper





//拍照/录像跳转
- (void)showImagePickerForSourceType:(UIImagePickerControllerSourceType)sourceType andCameraCaptureMode:(UIImagePickerControllerCameraCaptureMode)mode
{
    UIImagePickerController *imagePickerController = [[UIImagePickerController alloc] init];
    //这是 VC 的各种 modal 形式
    imagePickerController.modalPresentationStyle = UIModalPresentationFullScreen;
    imagePickerController.sourceType = sourceType;
    if (mode == UIImagePickerControllerCameraCaptureModePhoto)
    {
        
    }
    imagePickerController.delegate = self;
    //允许拍照后编辑
    imagePickerController.allowsEditing = NO;
    if (mode == UIImagePickerControllerCameraCaptureModeVideo) {
        //单独设置
        imagePickerController.mediaTypes = [[NSArray alloc] initWithObjects: (NSString *) kUTTypeMovie, nil];
        //设置模式-->拍照/摄像
        imagePickerController.cameraCaptureMode = mode;
        //设置视频分辨率
        imagePickerController.videoQuality = UIImagePickerControllerQualityType640x480;
        
        //开启默认摄像头-->前置/后置
        imagePickerController.cameraDevice = UIImagePickerControllerCameraDeviceRear;
        //设置默认的闪光灯模式-->开/关/自动
        imagePickerController.cameraFlashMode = UIImagePickerControllerCameraFlashModeAuto;
        
        //拍摄时预览view的transform属性，可以实现旋转，缩放功能
        //        imagePickerController.cameraViewTransform = CGAffineTransformMakeRotation(M_PI);
        //        imagePickerController.cameraViewTransform = CGAffineTransformMakeScale(2.0,2.0);
        
    }
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    [window.rootViewController presentViewController:imagePickerController animated:YES completion:NULL];
}

#pragma mark - UIImagePickerControllerDelegate 相机
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info{
    
    NSString *mediaType = info[UIImagePickerControllerMediaType];
    
    if ([mediaType isEqualToString:@"public.image"]) {
        NSLog(@"image...");
        
        
        //获取照片的原图
        UIImage* original = [info objectForKey:UIImagePickerControllerOriginalImage];
        /*
         //获取图片裁剪后，剩下的图
         UIImage* crop = [info objectForKey:UIImagePickerControllerCropRect];
         //获取图片的url
         NSURL* url = [info objectForKey:UIImagePickerControllerMediaURL];
         //获取图片的metadata数据信息
         NSDictionary* metadata = [info objectForKey:UIImagePickerControllerMediaMetadata];
         */
        
        //获取图片裁剪的图
        //        UIImage* edit = [info objectForKey:UIImagePickerControllerEditedImage];
        
        [self saveImage:original];
        
    }else{  // public.movie
        NSLog(@"video...");
        NSURL *url=[info objectForKey:UIImagePickerControllerMediaURL];//视频路径
        NSString *urlStr=[url path];
        
        
        _videoSec = [self getVideoDuration:url];

        [self saveVideo:urlStr];
    }
    [picker dismissViewControllerAnimated:YES completion:nil];
}
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    
    NSLog(@"取消");
    [picker dismissViewControllerAnimated:YES completion:nil];
}
#pragma mark - 抓拍处理
- (void)saveImage:(UIImage *)img
{
    UIImage *newImage = [self imageWithImageSimple:img scaledToSize:CGSizeMake(1080, 1440)];
//    NSString *imagePath = [self getDirectoryPath:@"capture"];
//    NSString *account = getApp().account;
//    NSString *currentTime = [self getCurrentTime];
//    NSString *fileName = [NSString stringWithFormat:@"%@-%@.jpg",account,currentTime];
//    NSString *filePath = [imagePath stringByAppendingPathComponent:fileName];
    
    BOOL result = [UIImageJPEGRepresentation(newImage, 0.5) writeToFile:self.imageUrl atomically:YES];
    if (result == YES) {
        NSLog(@"成功");
        
    }
    if (_delegate) {
        [_delegate captureSuccess:result];
    }
}
//更改分辨率
- (UIImage*)imageWithImageSimple:(UIImage*)image scaledToSize:(CGSize)newSize
{
    // Create a graphics image context
    UIGraphicsBeginImageContext(newSize);
    // Tell the old image to draw in this new context, with the desired
    // new size
    [image drawInRect:CGRectMake(0,0,newSize.width,newSize.height)];
    // Get the new image from the context
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    // End the context
    UIGraphicsEndImageContext();
    // Return the new image.
    return newImage;
}
#pragma mark - 录像处理
- (void)saveVideo:(NSString *)videoPath
{
        [self changeMovToMp4:videoPath];
}
//转换分辨率及转换成mp4类型
-(void)changeMovToMp4:(NSString *)path
{
    AVURLAsset *avAsset = [AVURLAsset URLAssetWithURL:[NSURL fileURLWithPath:path] options:nil];
    NSArray *compatiblePresets = [AVAssetExportSession exportPresetsCompatibleWithAsset:avAsset];
    
    NSString *exportPath = self.videoUrl;
    
    if ([compatiblePresets containsObject:AVAssetExportPresetLowQuality])
    {
        AVAssetExportSession *exportSession = [[AVAssetExportSession alloc]initWithAsset:avAsset presetName:AVAssetExportPresetPassthrough];
        
        exportSession.outputURL = [NSURL fileURLWithPath:exportPath];
        NSLog(@"%@", exportPath);
        exportSession.outputFileType = AVFileTypeMPEG4;
        exportSession.shouldOptimizeForNetworkUse = YES;
        __weak typeof(self) weakSelf = self;
        [exportSession exportAsynchronouslyWithCompletionHandler:^{
            switch ([exportSession status]) {
                case AVAssetExportSessionStatusFailed:
                    NSLog(@"Export failed: %@", [[exportSession error] localizedDescription]);
//                    [weakSelf.delegate videoSuccess:false duration:0];
                    break;
                case AVAssetExportSessionStatusCancelled:
                    NSLog(@"Export canceled");
//                    [weakSelf.delegate videoSuccess:false duration:0];
                    break;
                case AVAssetExportSessionStatusCompleted:
                {
                    NSLog(@"转换成功");
                    CGFloat duration = weakSelf.videoSec;
//                    [weakSelf.delegate videoSuccess:true duration:duration];
                }
                    break;
                default:
                    break;
            }
        }];
    }
}

//获取视频时间
- (CGFloat) getVideoDuration:(NSURL*) URL
{
    NSDictionary *opts = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:NO]
                                                     forKey:AVURLAssetPreferPreciseDurationAndTimingKey];
    AVURLAsset *urlAsset = [AVURLAsset URLAssetWithURL:URL options:opts];
    float second = 0;
    second = urlAsset.duration.value/urlAsset.duration.timescale;
    return second;
}







@end
