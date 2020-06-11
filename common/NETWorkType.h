//
//  NETWorkType.h
//  cmsv9
//
//  Created by tongtianxing on 2018/10/22.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Reachability.h"
#import <SystemConfiguration/CaptiveNetwork.h>
NS_ASSUME_NONNULL_BEGIN

@interface NETWorkType : NSObject
+ (NSString*)getNetworkTypeByReachability;
+(NSString*)fetchSSIDInfo;


@end

NS_ASSUME_NONNULL_END
