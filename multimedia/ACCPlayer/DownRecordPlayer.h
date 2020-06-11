//
//  DownRecordPlayer.h
//  cmsv9
//
//  Created by tongtianxing on 2018/12/3.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DownRecordPlayer : NSObject
+(DownRecordPlayer*)player;

-(void)appendRecordAudioFileDict:(NSDictionary *)fileDict;


@end

NS_ASSUME_NONNULL_END
