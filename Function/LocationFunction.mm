//
//  LocationFunction.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "LocationFunction.h"
#import <CoreLocation/CoreLocation.h>
#import "ttxstreamwork.h"
#import "NETWorkType.h"
const int BASENUMBER = 10000000;

@interface LocationFunction()<CLLocationManagerDelegate>

@property (nonatomic , strong)CLLocationManager *manager;

@end


@implementation LocationFunction

+(LocationFunction*)locationFunction
{
    static LocationFunction *location = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (location == nil) {
            location = [[LocationFunction alloc]init];
        }
    });
    return location;
}

-(void)startLocationFunction
{
    if (_manager == nil) {
        _manager = [CLLocationManager new];
        _manager.delegate = [LocationFunction locationFunction];
        if([_manager respondsToSelector:@selector(requestAlwaysAuthorization)])
        {
            _manager.desiredAccuracy = kCLLocationAccuracyBest;
            [_manager requestAlwaysAuthorization];
        }
    }
    [_manager startUpdatingLocation];
}
-(void)stopLocationFunction
{
    [self.manager stopUpdatingLocation];
    _manager.delegate = nil;
    _manager = nil;
}

//设备端的GPS信息的格式一般是按照DDFF.MMMM的方式保存的
//所以此处对设备端如何取秒并转换成此处要求的形式加以示范
//(*注意：具体的计算方式和GPS模块提供的数据格式有关)
//假如设备端采集到的GPS值是：12158.3416，则：
//        度是 121
//        分是 58
//        秒是 0.3416 分 (*注意：单位是分)
//             0.3416 * 60 = 20.496 秒
//        再扩大一千万倍，把它转换成此结构需要的精度：
//            20.496 * 10,000,000 = 204,960,000 (千万分之一秒)
// 此时cLongitudeDegree = 121，cLongitudeCent = 58，lLongitudeSec = 204, 960, 000
-(void)netStream_UpdateGpsInfo:(CLLocation*)currentLocation
{
    TTXGpsInfo_S gps = {0};
   double  dbLongtitude = fabs(currentLocation.coordinate.longitude);
   double dbLatitude = fabs(currentLocation.coordinate.latitude);
       unsigned char latitude_degree = (unsigned char)dbLatitude;
       long long a,b;
      a = BASENUMBER*dbLatitude;
      b = BASENUMBER*latitude_degree;
      dbLatitude = (a - b - 0.0)/BASENUMBER;
      dbLatitude *= 60;
    
     unsigned char latitude_miniute = (unsigned char)dbLatitude;
     a = BASENUMBER*dbLatitude;
     b = BASENUMBER*latitude_miniute;
     dbLatitude = (a - b - 0.0)/BASENUMBER;
     dbLatitude *= 60;
    
    long latitude_second = (long)(dbLatitude*BASENUMBER);
    gps.cLatDegree = (char)latitude_degree;
    gps.cLatCent = (char)latitude_miniute;
    gps.lLatSec = (long)latitude_second;
    
    unsigned char longtitude_degree = (unsigned char)dbLongtitude;
    a = BASENUMBER*dbLongtitude;
    b = BASENUMBER*longtitude_degree;
    dbLongtitude = (a - b - 0.0)/BASENUMBER;
    dbLongtitude *= 60;
    
    
    unsigned char longtitude_miniute = (unsigned char)dbLongtitude;
    a = BASENUMBER*dbLongtitude;
    b = BASENUMBER*longtitude_miniute;
    dbLongtitude = (a - b - 0.0)/BASENUMBER;
    dbLongtitude *= 60;
    long longtitude_second = (long)(dbLongtitude*BASENUMBER);
    
    gps.cLngDegree = (char)longtitude_degree;
    gps.cLngCent = (char)longtitude_miniute;
    gps.lLngSec = (long)longtitude_second;
    
    gps.cGpsStatus = TTX_GPS_VALID;
    
    if (currentLocation.coordinate.longitude > 0)
    {
        gps.cLngDirection = TTX_GPS_LONGITUDE_EAST;
    }
    else
    {
        gps.cLngDirection = TTX_GPS_LONGITUDE_WEST;
    }
    if (currentLocation.coordinate.latitude > 0)
    {
        gps.cLatDirection = TTX_GPS_LATITUDE_NORTH;
    }
    else
    {
        gps.cLatDirection = TTX_GPS_LATITUDE_SOUTH;
    }
    if (currentLocation.altitude < 0)
    {
        gps.usGpsAngle = 0;
    }
    else
    {
        gps.usGpsAngle = currentLocation.altitude;
    }
    gps.usSpeed = 0;
    
    NSLog(@"传输gps");
    TTXStreamIns()->SetGpsInfo(gps);
    
    TTXModuleStatus_S module = {0};
    module.bGpsExist = true; //GPS模块是否存在，true表示存在,  默认为true
    module.c3gState = 3;//3G模块状态,     0、SIM卡不存在1、信号弱2、信号差3、信号一般4、信号好 5、信号 优6、3G模块不存在7、3G功能关闭
    module.cCoorType = TTX_COOR_TYPE_GCJ02;//高德 //GPS坐标类型TTX_COOR_TYPE_WSG84，TTX_COOR_TYPE_GCJ02,
    
    int nLocType = TTX_LOC_TYPE_GPS;
    
    NSString *netWork = [NETWorkType getNetworkTypeByReachability];
    if ([netWork isEqualToString:@"WIFI"]) {
        nLocType = TTX_LOC_TYPE_WIFI;
    }
    module.cLocType = nLocType; //GPS定位类型TTX_LOC_TYPE_GPS，TTX_LOC_TYPE_WIFI
    TTXStreamIns()->SetModuleStatus(module);

}


#pragma mark - LocationManagerDelegate
-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
    //locations里就是更新出来的定位信息，一般取最后一个值
    CLLocation *cllocation = [locations lastObject];
    [[LocationFunction locationFunction] netStream_UpdateGpsInfo:cllocation];
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    if(error.code == kCLErrorLocationUnknown) {
        NSLog(@"无法检索位置");
    }
    else if(error.code == kCLErrorNetwork) {
        NSLog(@"网络问题");
    }
    else if(error.code == kCLErrorDenied) {
        NSLog(@"定位权限的问题");
        [self stopLocationFunction];
    }
}








@end
