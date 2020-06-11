//
//  LocationFunction.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LocationFunction : NSObject
+(LocationFunction*)locationFunction;
-(void)startLocationFunction;
-(void)stopLocationFunction;
@end

NS_ASSUME_NONNULL_END
