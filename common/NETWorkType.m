//
//  NETWorkType.m
//  cmsv9
//
//  Created by tongtianxing on 2018/10/22.
//  Copyright © 2018年 babelstar. All rights reserved.
//

#import "NETWorkType.h"

@implementation NETWorkType

+ (NSString*)getNetworkTypeByReachability{
    NSString *network = @"";
    switch ([[Reachability reachabilityForInternetConnection]currentReachabilityStatus]) {
        case NotReachable:
            network = @"NONE";
            break;
        case ReachableViaWiFi:
            network = @"WIFI";
            break;
        case ReachableViaWWAN:
            network = @"WWAN";
            break;
        default:
            break;
    }
    if ([network isEqualToString:@""]) {
        network = @"NO DISPLAY";
    }
    return network;
    }

+(NSString*)fetchSSIDInfo
{
     NSString *ssid = @"Not Found";
    CFArrayRef myArray = CNCopySupportedInterfaces();
    if (myArray!=nil) {
        CFDictionaryRef myDict = CNCopyCurrentNetworkInfo(CFArrayGetValueAtIndex(myArray, 0));
        if (myDict != nil) {
            NSDictionary *dict = (NSDictionary *)CFBridgingRelease(myDict);
            ssid = [dict valueForKey:@"SSID"];
        }
    
    }
    return ssid;
}








@end
