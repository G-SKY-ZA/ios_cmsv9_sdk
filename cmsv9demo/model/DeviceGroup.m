//
//  DeviceGroup.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/24.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "DeviceGroup.h"

@implementation DeviceGroup
+(NSDictionary<NSString *,id> *)modelCustomPropertyMapper{
    
    return @{@"idStr":@"id"
             };
}


-(void)addVehiCount {
    _vehiCount += 1;
}
@end
