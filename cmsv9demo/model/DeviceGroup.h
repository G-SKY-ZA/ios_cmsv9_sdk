//
//  DeviceGroup.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/24.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "YYModel.h"
NS_ASSUME_NONNULL_BEGIN
@interface DeviceGroup : NSObject<YYModel>
@property (nonatomic, copy) NSString* idStr;        //分组名称
@property (nonatomic, assign) NSInteger parentId;//数据库生成的序号
@property (nonatomic, copy) NSString* name;        //分组名称




@property (nonatomic, assign) NSInteger vehiCount;//数据库生成的序号
-(void)addVehiCount;
@end

NS_ASSUME_NONNULL_END
