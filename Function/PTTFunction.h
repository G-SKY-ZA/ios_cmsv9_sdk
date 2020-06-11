//
//  PTTFunction.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/28.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PTTFunction : NSObject

+(PTTFunction*)pttFunction;
-(int)pttStartFunction;
-(void)pttStopFunction;
@end

NS_ASSUME_NONNULL_END
