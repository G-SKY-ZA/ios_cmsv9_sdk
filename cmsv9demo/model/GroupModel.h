//
//  GroupModel.h
//  cmsv9
//
//  Created by tongtianxing on 2018/10/17.
//  Copyright © 2018年 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YYModel.h"
NS_ASSUME_NONNULL_BEGIN

@interface GroupModel : NSObject

@property NSString *companyName;
@property NSString *disId;
@property NSInteger id; //分组
@property NSString *name;
@property NSInteger parentId;
@property NSString *status;
@property NSInteger userId;
@property NSString *vId;



@property (nonatomic , assign)BOOL expansion;



@end

NS_ASSUME_NONNULL_END
