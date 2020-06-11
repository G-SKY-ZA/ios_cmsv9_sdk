//
//  GroupMemberModel.h
//  cmsv9
//
//  Created by tongtianxing on 2018/10/17.
//  Copyright © 2018年 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YYModel.h"
NS_ASSUME_NONNULL_BEGIN

@interface GroupMemberModel : NSObject


@property NSString* companyName;
@property NSInteger disId;
@property NSInteger id;
@property NSString* name;
@property NSInteger parentId;
@property NSInteger status;
@property NSString* userId;
@property NSInteger vId;

@end

NS_ASSUME_NONNULL_END
