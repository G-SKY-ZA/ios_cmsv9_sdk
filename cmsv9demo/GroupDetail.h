//
//  GroupDetail.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/28.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GroupModel.h"
#import "GroupMemberModel.h"
NS_ASSUME_NONNULL_BEGIN
typedef void(^getGroupDetailSuccess)(void);
@interface GroupDetail : NSObject

//+(GroupDetail*)singleton;

//获取组和组员
+(void)requestGroupMemberInfo;
@end

NS_ASSUME_NONNULL_END
