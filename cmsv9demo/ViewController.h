//
//  ViewController.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/24.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AFNetworking.h"
#import "RecordListViewController.h"
@interface ViewController : UIViewController
@property (nonatomic , copy) NSString *server;

@property (weak, nonatomic) IBOutlet UITableView *groupTable;
@property (weak, nonatomic) IBOutlet UITextField *accountTF;
@property (weak, nonatomic) IBOutlet UITextField *passwordTF;
@property (weak, nonatomic) IBOutlet UITextField *serverTF;

//data
@property (nonatomic, strong) NSMutableDictionary *deviceGroupArr;
@property (nonatomic, strong) NSMutableDictionary *mapVehicleWithVehiIdno;   // vehidno : (VehicleInfoModel)
@property (nonatomic, strong) NSMutableArray *lstVehicleAll;


@property (strong , nonatomic) NSMutableDictionary* groupsDict;
@property (strong , nonatomic) NSMutableArray* groupsArray; //保持原有顺序用。

@property (strong , nonatomic) NSMutableDictionary* gMembersDict;
@property (strong , nonatomic) NSMutableArray* gMembersArray;

@property (strong , nonatomic) NSMutableDictionary *groupMemberDict;//存放组对应成员;  groupid : @[GroupMemberModel]

@property (strong , nonatomic)AFHTTPSessionManager *manage;

@property (nonatomic , strong)RecordListViewController *rlVC;

+(ViewController*)viewController;
@end

