//
//  LibFunction.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN
typedef void(^FileSuccess)(NSDictionary *fileDict);
UIKIT_EXTERN NSString  const *SenderNameKey;
UIKIT_EXTERN NSString  const *FilePathKey;

@interface LibFunction : NSObject

@property (nonatomic , assign)int videoSecond;
@property (nonatomic , copy) FileSuccess dfSuccess;
+(LibFunction*)libFunction;
-(void)sendUploadFile:(int)nFileType file:(const char*)szFile Id:( const char* _Nullable )szAlarmId;
//upload record
-(void)pttnetapi_TTXPTT_UploadFile:(const char*)szFile group:(int)nGroup terminalID:(int)terminalID sec:(int)tSec pUser:(void* )pUser;
//down record
-(BOOL)pttnetapi_TTXPTTDownFile:(const char*)szUrl savePath:(const char*)szSavePath pUser:(void*)pUser success:(FileSuccess)dfSuccess;
@end

NS_ASSUME_NONNULL_END
