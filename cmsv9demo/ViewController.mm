//
//  ViewController.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/24.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "ViewController.h"

#import "iToast.h"
#import "DeviceGroup.h"
#import "VehicleInfoModel.h"
#import "EquipmentInfoModel.h"
#import "GroupModel.h"
#import "GroupMemberModel.h"
#import "YYModel.h"
#import "XCFileManager.h"
#import "NEtWorkType.h"

//sdk
#import "ttxstreamwork.h"
#import "ttxpttservice.h"

#import "GroupDetail.h"


#import "PTTFunction.h"
#import "LocationFunction.h"
#import "ImagePickerHelper.h"
#import "LibFunction.h"
#import "FMWriteVideoController.h"
#import "FMVideoPlayController.h"
#import "RecordHelper.h"


static ViewController *vc = nil;

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource,UIGestureRecognizerDelegate,ImagePickerHelperDelegate,RecoderHelperDelegate>
{
    BOOL isLogining;
     
      NSString *jsession;
    
    ImagePickerHelper *imagePickerHelper;
    
    RecordHelper *recordHelper;

}


@property (weak, nonatomic) IBOutlet UIButton *loginBtn;

@property (weak, nonatomic) IBOutlet UIButton *PTTBtn;





@end

@implementation ViewController
+(ViewController*)viewController
{
    return vc;
}

-(NSMutableDictionary *)groupMemberDict
{
    if (_groupMemberDict == nil) {
        _groupMemberDict = [NSMutableDictionary dictionary];
    }
    return _groupMemberDict;
}

-(NSMutableDictionary *)groupsDict
{
    if (_groupsDict == nil) {
        _groupsDict = [NSMutableDictionary dictionary];
    }
    return _groupsDict;
}
-(NSMutableArray *)groupsArray
{
    if (_groupsArray == nil) {
        _groupsArray = [NSMutableArray array];
    }
    return _groupsArray;
}
-(NSMutableDictionary *)gMembersDict
{
    if (_gMembersDict == nil) {
        _gMembersDict = [NSMutableDictionary dictionary];
    }
    return _gMembersDict;
}
-(NSMutableArray *)gMembersArray
{
    if (_gMembersArray == nil) {
        _gMembersArray = [NSMutableArray array];
    }
    return _gMembersArray;
}
-(NSMutableDictionary *)deviceGroupArr
{
    if (_deviceGroupArr == nil) {
        _deviceGroupArr = [NSMutableDictionary dictionary];
    }
    return _deviceGroupArr;
}
-(NSMutableDictionary *)mapVehicleWithVehiIdno
{
    if (_mapVehicleWithVehiIdno == nil) {
        _mapVehicleWithVehiIdno = [NSMutableDictionary dictionary];
    }
    return _mapVehicleWithVehiIdno;
}
-(NSMutableArray *)lstVehicleAll
{
    if (_lstVehicleAll == nil) {
        _lstVehicleAll = [NSMutableArray array];
    }
    return _lstVehicleAll;
}



-(void)initData
{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"LoginInfo" ofType:@"plist"];
    NSDictionary *loginInfo = [NSDictionary dictionaryWithContentsOfFile:path];
    NSString *accountInfo = loginInfo[@"Account"];
    NSString *passwordInfo = loginInfo[@"Password"];
    NSString *serverInfo = loginInfo[@"Server"];
    _accountTF.text = accountInfo;
    _passwordTF.text = passwordInfo;
    _passwordTF.secureTextEntry = true;
    _serverTF.text = serverInfo;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    vc = self;
    [self initData];
     _manage = [AFHTTPSessionManager manager];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(tap:)];
    tap.delegate = self;
    [self.view addGestureRecognizer:tap];
    // Do any additional setup after loading the view, typically from a nib.]
    
    [_PTTBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_PTTBtn setBackgroundColor:[UIColor colorWithRed:0 green:102/255.0 blue:191/255.0 alpha:1]];
    _PTTBtn.layer.cornerRadius = 15;
    [_PTTBtn addTarget:self action:@selector(pttBtnClick:) forControlEvents:UIControlEventTouchDown];
    [_PTTBtn addTarget:self action:@selector(pttTouchUpOut:) forControlEvents: UIControlEventTouchDragExit | UIControlEventTouchUpOutside|UIControlEventTouchUpInside];
    
}
-(void)loginAndGetDataSuccess
{
    self.server = self.serverTF.text;
    [self.groupTable reloadData];
    [self loginSuccessInitSDK];
}

-(void)loginSuccessInitSDK
{
     TTXNET_Initialize();
    //打印日志
//        NSString *temDir = [XCFileManager tmpDir];
//        TTXNET_SetLogParam(true, true, 0, [temDir UTF8String], 10);
    NSString *documentsDir = [[XCFileManager documentsDir] stringByAppendingPathComponent:@"Data"];
    if (![XCFileManager isExistsAtPath:documentsDir]) {
        [XCFileManager createDirectoryAtPath:documentsDir];
    }
    NSString *dataPath = [documentsDir stringByAppendingString:@"/"];
    //    //配置缓存的位置，必须为目录结构方式
    TTXNET_SetDataPath([dataPath UTF8String]);
    
    NSString *account = _accountTF.text;
    NSString *svrIP = _serverTF.text;
    NSRange range = [svrIP rangeOfString:@":"];
    if (range.location != NSNotFound) {
        svrIP = [svrIP substringToIndex:range.location];
    }
    

    int port = 6608;
    
    CTTXStreamWork *cttxStreanWork = TTXStreamIns();
    TTXStreamIns()->SetDevIDNO([account UTF8String]);
    TTXStreamIns()->SetSvrInfo([svrIP UTF8String], port);
    TTXNET_SetNetAdapter(cttxStreanWork);
    
    CTTXPttService *cttPttService =  TTXPttWorkIns();
    TTXPTT_SetPttAdapter(cttPttService);
    
    TTXPttWorkIns()->SetPttHeartInterval(TTXStreamIns()->GetHeartInterval());
    TTXNET_SetMediaInfo(TTX_AUDIO_TYPE_AAC_8KBPS, 1, 8000, 16);
    TTXNET_SetRealTimeMode(true);
    
    //     设备通用信息配置 //ncount
    TTXNET_SetDeviceInfo(1, 1, [account UTF8String]);//nCount 1-4
    
    
    // 配置网络类型
    NSString *netWork = [NETWorkType getNetworkTypeByReachability];
    if ([netWork isEqualToString:@"WIFI"]) {
        NSString *ssid = [NETWorkType fetchSSIDInfo];
        if (![ssid isEqualToString:@"Not Found"]) {
            TTXNET_SetNetworkInfo(1, [ssid UTF8String]);//参数nNetType 0 3g 1 wifi 2 有线 3 4g
        }
    }else{
        TTXNET_SetNetworkInfo(3, nil);
    }
    //    开始网络模块，调用此接口后，与服务器维持通信链路
    TTXNET_SetLoginType(TTX_LOGIN_TYPE_IOS);
    int result = -1;
    result = TTXNET_StartWork([account UTF8String], [svrIP UTF8String], 6608, true, 6688);
    //这里配置才能动
    TTXPTT_StartWork();

}


#pragma mark - Login Process
- (IBAction)loginBtnClicked:(UIButton *)sender {
    
    if(sender.selected == false){ //login
        if (isLogining == false) {
            if(_accountTF.text.length > 0 && _passwordTF.text.length > 0 && _serverTF.text.length > 0)
            {
                _manage.responseSerializer.acceptableContentTypes = [NSSet setWithObject:@"text/html"];
            
                NSString *serverAddr =  [NSString stringWithFormat:@"http://%@/",_serverTF.text];
                NSMutableString *str = [[NSMutableString alloc]initWithString:serverAddr];
                [str appendString: @"LoginAction_loginMobile.action?update=gViewerIOS&server=login&userAccount="];
                [str appendString:_accountTF.text];
                [str appendString: @"&password="];
                [str appendString:_passwordTF.text];
                 [str appendString:@"&dispatch=1"];
                  isLogining = true;
                [_manage POST:str parameters:nil headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
                    NSHTTPCookieStorage *cookieJar = [NSHTTPCookieStorage sharedHTTPCookieStorage];
                    NSArray *cookieArr = [cookieJar cookies];
                    for(NSHTTPCookie *cookie in cookieArr) {
                        NSLog(@"cookie －> %@", cookie);
                        if ([cookie.name isEqualToString:@"JSESSIONID"]) {
                            //存储cookies
                            self->jsession = cookie.value;
                        }
                        //存储之后删除cookies
//                        [cookieJar deleteCookie:cookie];
                    }

                    NSLog(@"responseObject = %@",responseObject);
                    NSDictionary *dict = responseObject;
                    int result = [dict[@"result"] intValue];
                    if(result == 0)
                    {
                        BOOL dispatcher = [dict[@"dispatcher"] intValue];
                        if (dispatcher == false) { // no a dispatcher
                           [self loginFailure];
                            return ;
                        }
                         self->jsession = dict[@"JSESSIONID"];
                        [self requestDeviceInfo];
                        
                        [self requestGroupMemberInfo];
                       
                         [[iToast makeText:@"Login successfully"] show];
                        self->isLogining = false;
                         sender.selected = true;
                
                    }else{
                     [self loginFailure];
                    }
                } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
                    [self loginFailure];
                }];
            }
        }
    }else if(sender.selected == true){
        NSString *serverAddr =  [NSString stringWithFormat:@"http://%@/",_serverTF.text];
        NSMutableString *str = [[NSMutableString alloc]initWithString:serverAddr];
          [str appendString: @"LoginAction_logout.action?"];
//          NSDictionary *parameters = @{@"jsession":jsession};
        [_manage POST:str parameters:nil headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
             NSLog(@"responseObject = %@",responseObject);
            NSDictionary *dict = responseObject;
            if ([dict[@"result"] intValue] == 0) {
                sender.selected = false;
                [[iToast makeText:@"Logout Success"] show];
                
                [self logoutSuccess];
            }
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            
        }];
    }
}
-(void)loginFailure
{
    isLogining = false;
    _loginBtn.selected = false;
     [[iToast makeText:@"Login failure"] show];
}
#pragma mark - Get Member Data
-(void)requestDeviceInfo
{
     NSString *serverAddr =  [NSString stringWithFormat:@"http://%@/",_serverTF.text];
      NSMutableString *str = [[NSMutableString alloc] initWithString:serverAddr];
      [str appendString: @"StandardLoginAction_getUserVehicleContainsGroup.action?toMap=3"];
    
    __weak typeof(self) weakSelf = self;
    [_manage POST:str parameters:nil headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSDictionary *dict = responseObject;
        if ([dict[@"result"] intValue] == 0) {
            NSArray *groups = [dict objectForKey:@"companys"];
            for (NSDictionary *dict1 in groups) {
                DeviceGroup *group = [DeviceGroup yy_modelWithJSON:dict1];
                [weakSelf.deviceGroupArr setValue:group forKey:group.idStr];
            }
            
            NSArray* vehicles = [dict objectForKey:@"vehicles"];//
            for (NSDictionary *dict2 in vehicles) {
                    VehicleInfoModel *model = [VehicleInfoModel yy_modelWithJSON:dict2];
//                  EquipmentInfoModel *model1 = model.dl[0];
                [weakSelf.lstVehicleAll addObject:model];
                [weakSelf.mapVehicleWithVehiIdno setObject:model forKey:model.vehiIDNO];
                
                NSString *groupID = [NSString stringWithFormat:@"%zd",model.companyId];
                DeviceGroup *group = [weakSelf.deviceGroupArr objectForKey:groupID];
                if (group) {
                    [group addVehiCount];
                }
            }
        }else{
            [self loginFailure];
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        [self loginFailure];
    }];
}
- (void)requestGroupMemberInfo
{
    NSString *serverAddr =  [NSString stringWithFormat:@"http://%@/",_serverTF.text];
    NSMutableString *str = [[NSMutableString alloc] initWithString:serverAddr];
    [str appendString: @"StandardCooperateAction_getUserDispatch.action"];
    __weak typeof(self) weakSelf = self;
    [_manage POST:str parameters:nil headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSDictionary *dict = responseObject;
        if ([dict[@"result"] intValue] == 0) {
               NSArray *lstGroup = [dict valueForKey: @"lstGroup"];
            for (NSDictionary *dict1 in lstGroup) {
                GroupModel *groupModel = [GroupModel yy_modelWithDictionary:dict1];
                [weakSelf.groupsDict setObject:groupModel forKey:[NSString stringWithFormat:@"%zd",groupModel.id]];
                [weakSelf.groupsArray addObject:groupModel];
            }
            NSArray *lstMember = [dict valueForKey: @"lstMember"];
            for (NSDictionary *dict2 in lstMember) {
            GroupMemberModel *gMemberModel = [GroupMemberModel yy_modelWithDictionary:dict2];
                
                NSString *groupId = [NSString stringWithFormat:@"%zd",gMemberModel.disId];
                
                [weakSelf.gMembersDict setObject:gMemberModel forKey:[NSString stringWithFormat:@"%@:%@",groupId,gMemberModel.name]];
                [weakSelf.gMembersArray addObject:gMemberModel];
                
                if (![weakSelf.groupMemberDict objectForKey:groupId]) {
                    NSMutableArray *arr = [NSMutableArray array];
                    [weakSelf.groupMemberDict setObject:arr forKey:groupId];
                }
                NSMutableArray *arr = [weakSelf.groupMemberDict objectForKey:groupId];
                [arr addObject:gMemberModel];
            
            }
            

            [weakSelf loginAndGetDataSuccess];
            
            
        }else{
           [self loginFailure];
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
          [self loginFailure];
    }];
}
-(void)logoutSuccess
{
    [self.deviceGroupArr removeAllObjects];
    [self.mapVehicleWithVehiIdno removeAllObjects];
    [self.lstVehicleAll removeAllObjects];
    [self.groupsDict removeAllObjects];
    [self.groupsArray removeAllObjects];
    [self.gMembersDict removeAllObjects];
    [self.gMembersArray removeAllObjects];
    [self.groupMemberDict removeAllObjects];
    
    [self.groupTable reloadData];
}



#pragma mark - TableHeader btn clicked
-(void)headerBtnClicked:(UIButton*)btn
{
    NSInteger section = btn.tag;
    GroupModel *gmodel = self.groupsArray[section];
    gmodel.expansion = !gmodel.expansion;
    [self.groupTable reloadData];
}

#pragma mark - UITableView Delegate DataSource
-(UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
     GroupModel *gmodel =  self.groupsArray[section];
    
//    UIView *view = [[UIView alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 30)];
    UIButton *btn = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 30)];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [btn setTitle:gmodel.name forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(headerBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    btn.tag = section;
    return btn;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier];
      
    }
    
    GroupModel *gmodel =  self.groupsArray[indexPath.section];
    NSString *key = [NSString stringWithFormat:@"%zd",gmodel.id];
    NSMutableArray *arr = [self.groupMemberDict valueForKey:key];
    GroupMemberModel *mmodel = arr[indexPath.row];
    if (mmodel.status == 1) {
        cell.textLabel.text =[NSString stringWithFormat:@"%@(默认组)",mmodel.name];
    }else{
        cell.textLabel.text = mmodel.name;
    }
    
    
    return cell;
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return self.groupsArray.count;
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 25;
}
-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 30;
}
-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
  GroupModel *gmodel =  self.groupsArray[section];
  
    if (!gmodel.expansion) {
        NSString *key = [NSString stringWithFormat:@"%zd",gmodel.id];
        NSMutableArray *arr = [self.groupMemberDict valueForKey:key];
        return arr.count;
    }else{
        return 0;
    }

}
//需要选中一个cell来进行后续操作
-(NSIndexPath*)groupTableIndexPathForSelectRow
{
    NSIndexPath *indexPath = [self.groupTable indexPathForSelectedRow];
    UITableViewCell *cell = [self.groupTable cellForRowAtIndexPath:indexPath];
    if (cell) { //有选中      可继续执行
        return indexPath;
    }else{
        return nil;
    }
}
-(void)getTerminalIDFromGroupTableSelectedIndexPath:(NSIndexPath*)indexPath group:(int*)groupID terminal:(int*)nTerminalID
{
    if (indexPath) {
        GroupModel *gmodel =  self.groupsArray[indexPath.section];
        NSString *key = [NSString stringWithFormat:@"%zd",gmodel.id];
        
        *groupID = (int)gmodel.id;
        
        NSMutableArray *arr = [self.groupMemberDict valueForKey:key];
        GroupMemberModel *mmodel = arr[indexPath.row];
  
        if ([mmodel.name isEqualToString:_accountTF.text]) {
            *nTerminalID = 0;
        }else{
            VehicleInfoModel *vehicle = [self.mapVehicleWithVehiIdno valueForKey:mmodel.name];
            EquipmentInfoModel *emodel = vehicle.dl[0];
            *nTerminalID = (int)emodel.dId;
        }
    }
}


#pragma mark - TapGrstureRecognizer
-(void)tap:(UITapGestureRecognizer*)ges
{
    [_accountTF resignFirstResponder];
    [_passwordTF resignFirstResponder];
    [_serverTF resignFirstResponder];
}
-(BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    if ([touch.view isDescendantOfView:self.groupTable]) {
        return NO;
    }else if ([touch.view isDescendantOfView:self.rlVC.view]){
        return NO;
    }
    return YES;
}
#pragma mark - 拍照上传处理
- (IBAction)photographBtnClicked:(UIButton *)sender {
   NSString *directoryPath = [[XCFileManager documentsDir] stringByAppendingPathComponent:@"caputrue"];
   BOOL result = [XCFileManager isDirectoryAtPath:directoryPath];
    if (result == false) {
        [XCFileManager createDirectoryAtPath:directoryPath];
    }
    NSString *currentTime = [self getCurrentTime];
    NSString *fileName = [NSString stringWithFormat:@"%@-%@.jpg",self.accountTF.text,currentTime];
    NSString *filePath = [directoryPath stringByAppendingPathComponent:fileName];
    if (imagePickerHelper == nil) {
        imagePickerHelper = [[ImagePickerHelper alloc]init];
    }
     imagePickerHelper.delegate = self;
     imagePickerHelper.imageUrl = filePath;
    [imagePickerHelper showImagePickerForSourceType:UIImagePickerControllerSourceTypeCamera andCameraCaptureMode:UIImagePickerControllerCameraCaptureModePhoto];
}
#pragma mark - ImagePickerHelperDelegate 默认尺寸1080*1440
-(void)captureSuccess:(BOOL)isSuccess
{
    if (isSuccess) {
        [[LibFunction libFunction] sendUploadFile:TTX_FILE_TYPE_JPEG file:[imagePickerHelper.imageUrl UTF8String] Id:NULL];
    }
}
#pragma mark - 录像上传
- (IBAction)videoBtnClicked:(UIButton *)sender {
     [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(videoFinishWithVideoFile:) name:NotificationVideoFinish object:nil];
    NSString *currentTime = [self getCurrentTime];
    NSString *fileName = [NSString stringWithFormat:@"%@-%@",self.accountTF.text,currentTime];
    FMWriteVideoController *writeVC = [[FMWriteVideoController alloc] initWithVideoName:fileName];
    UINavigationController *NAV = [[UINavigationController alloc] initWithRootViewController:writeVC];
    [self presentViewController:NAV animated:YES completion:nil];
}
#pragma mark - NotificationVideoFinish 上传录像 (暂时)限制最长1分钟和尺寸为屏幕宽高*2 每像素比特为6 视频编码格式h264
-(void)videoFinishWithVideoFile:(NSNotification*)object
{
    NSString *videoFile = [object.userInfo valueForKey:@"VideoFile"];
    NSInteger time = [[object.userInfo valueForKey:@"VideoTime"] integerValue];
    
    [LibFunction libFunction].videoSecond = ceilf(time);
    [[LibFunction libFunction] sendUploadFile:TTX_FILE_TYPE_REC file:[videoFile UTF8String] Id:NULL];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NotificationVideoFinish object:nil];
}
#pragma mark - 录音上传
- (IBAction)recordBtnTouchDown:(UIButton *)sender {
    NSString *directoryPath = [[XCFileManager documentsDir] stringByAppendingPathComponent:@"record"];
    BOOL result = [XCFileManager isDirectoryAtPath:directoryPath];
    if (result == false) {
        [XCFileManager createDirectoryAtPath:directoryPath];
    }
    NSString *currentTime = [self getCurrentTime];
    NSString *fileName = [NSString stringWithFormat:@"%@-%@.aac",self.accountTF.text,currentTime];
    NSString *filePath = [directoryPath stringByAppendingPathComponent:fileName];
    if(recordHelper == nil)
    {
        recordHelper = [[RecordHelper alloc] init];
    }
    recordHelper.delegate = self;
    [recordHelper configAudioWithUrl:filePath];
     [recordHelper startRecoder];
}
- (IBAction)recordBtnTouchUpInside:(UIButton *)sender {
    NSInteger cTime = [recordHelper stopRecoder]; //不精确
    NSString *audioFile = recordHelper.audioFile;
    NSURL *audioFileURL = [NSURL fileURLWithPath:audioFile];
    AVURLAsset* audioAsset =[AVURLAsset URLAssetWithURL:audioFileURL options:nil];
    CMTime audioDuration = audioAsset.duration;
    float audioDurationSeconds = CMTimeGetSeconds(audioDuration);
     if (cTime > 0) {
         NSString *account = self.accountTF.text;
          __block int cGroupId = 0;
         [self.gMembersArray enumerateObjectsUsingBlock:^(GroupMemberModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
             if ([obj.name isEqualToString:account] && obj.status == 1) {
                 cGroupId = (int)obj.parentId;
                 *stop = YES;
             }
         }];
         
          [[LibFunction libFunction] pttnetapi_TTXPTT_UploadFile:[recordHelper.audioFile UTF8String] group:cGroupId terminalID:0 sec:(int)(audioDurationSeconds*1000) pUser:(void*)1];
     }
}
- (IBAction)recordBtnTouchDragExit:(UIButton *)sender {
    [recordHelper cancleRecoder];
}
#pragma mark - 接收录音文件路径回调下载
void CallBackDoFile(const struct tm* pTm, int nTotalSecond, int nGroupID, int nTerminalID, int nType, int nSendTerID, const char* szUrl)
{
    
    NSMutableArray *lstVehicleAll = [ViewController viewController].lstVehicleAll;
    __block VehicleInfoModel *vehicle = nil;
    [lstVehicleAll enumerateObjectsUsingBlock:^(VehicleInfoModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
        EquipmentInfoModel *emodel = obj.dl[0];
        if (emodel.dId == nSendTerID) {
            vehicle = obj;
        }
    }];
      NSString *terminalName = vehicle.vehiIDNO;
        NSString *fileTime = [NSString stringWithFormat:@"%04d%02d%02d%02d%02d%02d",pTm->tm_year % 100 + 2000,pTm->tm_mon + 1,pTm->tm_mday,pTm->tm_hour,pTm->tm_min,pTm->tm_sec];
    NSString *documentsDir = [XCFileManager documentsDir];
    NSString *direc = [documentsDir stringByAppendingPathComponent:@"downFile"];
    if (![XCFileManager isExistsAtPath:direc]) {
        [XCFileManager createDirectoryAtPath:direc];
    }
    NSString *fileName = [NSString stringWithFormat:@"%@-%@.aac",terminalName,fileTime];
    NSString *filePath = [direc stringByAppendingPathComponent:fileName];
    
    NSDictionary *fileDicts = @{SenderNameKey : terminalName , FilePathKey : filePath};//传入
    [[LibFunction libFunction] pttnetapi_TTXPTTDownFile:szUrl savePath:[filePath UTF8String] pUser:(void*)fileDicts success:^(NSDictionary * _Nonnull fileDict) {
        //下载完成后回调 传出
        NSLog(@"fileDict = %@",fileDict);
        if ([ViewController viewController].rlVC == nil) {
            RecordListViewController *vc = [[RecordListViewController alloc] init];
            vc.view.frame = CGRectMake(95, 610, 310, 125);
            [[ViewController viewController].view addSubview:vc.view];
            [ViewController viewController].rlVC = vc;
            [ViewController viewController].rlVC.recordList.frame = vc.view.bounds;
        }
        [[ViewController viewController].rlVC addRecordList:fileDict];
        
        
//        [[DownRecordPlayer player] appendRecordAudioFileDict:fileDict];
    }];
}

#pragma mark - RecoderHelperDelegate 录音声量回调
-(void)RecordHelper:(RecordHelper*)helper averagePowerForChannel:(CGFloat)power
{
    NSLog(@"power = %f",power);
}

-(NSString*)getCurrentTime
{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    
    // ----------设置你想要的格式,hh与HH的区别:分别表示12小时制,24小时制
    
    [formatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
    
    //现在时间,你可以输出来看下是什么格式
    
    NSDate *datenow = [NSDate date];
    
    //----------将nsdate按formatter格式转成nsstring
    
    NSString *currentTimeString = [formatter stringFromDate:datenow];
    
    return currentTimeString;
}


#pragma mark - 定位上传处理
- (IBAction)startLocation:(UIButton *)sender {
    [[LocationFunction locationFunction] startLocationFunction];
}
- (IBAction)stopLocation:(UIButton *)sender {
    [[LocationFunction locationFunction] stopLocationFunction];
}





#pragma mark - PTT实时对讲
-(void)pttBtnClick:(id)btn
{
   int result = [[PTTFunction pttFunction] pttStartFunction];
    [self showErrorResult:result];
}
//松开滑出按钮外
-(void)pttTouchUpOut:(id)btn //松开
{
    [[PTTFunction pttFunction] pttStopFunction];
}


#pragma  mark - 临时小组操作
- (IBAction)addBtnClicked:(UIButton*)sender {
     NSIndexPath *indexPath = [self groupTableIndexPathForSelectRow];
    if (indexPath) {
        int nTerminalID,nGroupID;
        [self getTerminalIDFromGroupTableSelectedIndexPath:indexPath group:&nGroupID terminal:&nTerminalID];
        __block GroupModel *tempGroup = nil;
        [self.groupsArray enumerateObjectsUsingBlock:^(GroupModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
            if ([obj.name isEqualToString:@"Temporary"]) {
                tempGroup = obj;
            }
        }];
        
        if (tempGroup) {
            int result = TTXPTT_AddTempGroupMember((int)tempGroup.id, &nTerminalID, 1);//增
            NSLog(@"%d",result);
            [self showErrorResult:result];
            [GroupDetail requestGroupMemberInfo];//增删
        }
    }
    
}
- (IBAction)deleteBtnClicked:(UIButton *)sender {
     NSIndexPath *indexPath = [self groupTableIndexPathForSelectRow];
    if (indexPath) {
        int nTerminalID,nGroupID;
        [self getTerminalIDFromGroupTableSelectedIndexPath:indexPath group:&nGroupID terminal:&nTerminalID];
        __block GroupModel *tempGroup = nil;
        [self.groupsArray enumerateObjectsUsingBlock:^(GroupModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
            if ([obj.name isEqualToString:@"Temporary"]) {
                tempGroup = obj;
            }
        }];
       int  result = TTXPTT_DelTempGroupMember((int)tempGroup.id, &nTerminalID, 1);//删除队员
           NSLog(@"%d",result);
        [self showErrorResult:result];
        [GroupDetail requestGroupMemberInfo]; // 增删
    }
}
- (IBAction)createBtnClicked:(UIButton *)sender {
     NSIndexPath *indexPath = [self groupTableIndexPathForSelectRow];
    if (indexPath) {
        int nTerminalID,nGroupID;
      [self getTerminalIDFromGroupTableSelectedIndexPath:indexPath group:&nGroupID terminal:&nTerminalID];
      int result =   TTXPTT_CreateTempGroup("", 1, nTerminalID, nGroupID);//创建
        NSLog(@"%d",result);
        [self showErrorResult:result];
    }
}
- (IBAction)removeBtnClicked:(UIButton *)sender {
    __block GroupModel *tempGroup = nil;
    [self.groupsArray enumerateObjectsUsingBlock:^(GroupModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if ([obj.name isEqualToString:@"Temporary"]) {
            tempGroup = obj;
        }
    }];
    if (tempGroup) {
    int result =  TTXPTT_RemoveTempGroup((int)tempGroup.id);//删除小组
                NSLog(@"%d",result);
        [self showErrorResult:result];
    }
}

#pragma  mark - 强拉强拆
- (IBAction)haleBtnClicked:(UIButton *)sender {
    [self switchGroupDoHale:YES];
}
- (IBAction)demolitionBtnClicked:(UIButton *)sender {
     [self switchGroupDoHale:NO];
}
//强拉强拆
-(BOOL)switchGroupDoHale:(BOOL)hale
{
    NSIndexPath *indexPath = [self groupTableIndexPathForSelectRow];
    if (indexPath) { //有选中      可继续执行
        GroupModel *gmodel =  self.groupsArray[indexPath.section];
        NSString *key = [NSString stringWithFormat:@"%zd",gmodel.id];
        NSMutableArray *arr = [self.groupMemberDict valueForKey:key];
        GroupMemberModel *mmodel = arr[indexPath.row];
        int nTerminalID = 0;
        if ([mmodel.name isEqualToString:_accountTF.text]) {
            nTerminalID = 0;
        }else{
        VehicleInfoModel *vehicle = [self.mapVehicleWithVehiIdno valueForKey:mmodel.name];
        EquipmentInfoModel *emodel = vehicle.dl[0];
         nTerminalID = (int)emodel.dId;
        }
           int nGroupID = (int)gmodel.id;

        return [self ttxptt_SwitchGroup:nGroupID terminalID:nTerminalID enter:hale];
    }
    
    return false;
}
-(int)ttxptt_SwitchGroup:(int)nGroupID terminalID:(int)nTerminalID enter:(int)enter
{
    int result = TTXPTT_SwitchGroup(nGroupID, nTerminalID, enter);
    [self showErrorResult:result];
    NSLog(@"result = %d",result);
    return result;
}
#pragma mark - 群组操作回调
//有调用没有实现也会报 Undefined symbols for architecture arm64:
//群组成员发生变化，需要重新去后台获取群组成员信息
void CallBackPttDoUpdateGroupMember(int nGroupID)
{
    NSLog(@" CallBackPttDoUpdateGroupMember = %d",nGroupID);
    [GroupDetail requestGroupMemberInfo];
}
//把用户添加到某个小组 ，需要重新去后台获取群组成员信息
//@nGroupID: 群组ID
//@bTempGroup: 是否为临时群组
void CallBackPttDoAppendToGroup(int nGroupID, int nTerminalID)
{
    NSLog(@" CallBackPttDoAppendToGroup  nGroupID = %d nTerminalID = %d ",nGroupID,nTerminalID);
    [GroupDetail requestGroupMemberInfo];
    
}
//从协同小组中移除，将群组结点删除
//@nGroupID: 群组ID
//@bTempGroup: 是否为临时群组
//@nTerminalID: 那个终端删除了群组
void CallBackPttDoRemoveFromGroup(int nGroupID, int bTempGroup, int nTerminalID)
{
    NSLog(@" CallBackPttDoRemoveFromGroup nGroupID = %d bTempGroup = %d nTerminalID = %d",nGroupID,bTempGroup,nTerminalID);
    [GroupDetail requestGroupMemberInfo];
}
//切换群组(被强拉或者强拆)
//@nGroupID: 群组ID
//@nTerminalID: 终端ID，如果终端ID为0表示本终端切换群组
//@nEnter: 进入或者离开
void CallBackPttDoSwitchGroup(int nGroupID, int nTerminalID, int nEnter)
{
    NSLog(@" CallBackPttDoSwitchGroup nGroupID = %d nTerminalID = %d nEnter = %d",nGroupID,nTerminalID,nEnter);
    
     NSString *key = [NSString stringWithFormat:@"%d",nGroupID];
    NSMutableArray *arr = [vc.groupMemberDict valueForKey:key];
    
    [arr enumerateObjectsUsingBlock:^(GroupMemberModel *obj, NSUInteger idx, BOOL * _Nonnull stop) {
        VehicleInfoModel *vehicle = [vc.mapVehicleWithVehiIdno valueForKey:obj.name];
        EquipmentInfoModel *emodel = vehicle.dl[0];
        if (emodel.dId == nTerminalID) {
            obj.status = nEnter;
            *stop = YES;
        }
    }];
    dispatch_async(dispatch_get_main_queue(), ^{
      [vc.groupTable reloadData];
    });
    
    
//    SKYTerminalView *terminalView = [SKYAppDelegate shareApp].terminalView;
//    [terminalView doSwitchGroup:nGroupID terminalID:nTerminalID enter:nEnter];
}



#pragma mark - 错误显示
-(void)showErrorResult:(int)result
{
    NSString *str = nil;
    switch (result) {
        case 200:
            str = @"密码错误";
            break;
        case 201:
            str = @"已经登陆";
            break;
        case 202:
            str = @"网络错误";
            break;
        case 203:
            str = @"未取得h讲话权";
            break;
        case 204:
            str = @"其他用户正在讲话";
            break;
        case 205:
            str = @"没有处于某个群组(空闲状态)";
            break;
        case 206:
            str = @"群组不存在";
            break;
        case 207:
            str = @"非群组成员";
            break;
        case 208:
            str = @"已经存在临时小组";
            break;
        case 209:
            str = @"非临时群组";
            break;
        case 210:
            str = @"无权限";
            break;
        case 211:
            str = @"操作数据库";
            break;
        case 212:
            str = @"未知错误";
            break;
        case 213:
            str = @"离线状态";
            break;
        case 214:
            str = @"终端不存在";
            break;
        case 215:
            str = @"终端不在线";
            break;
        case 216:
            str = @"终端正在讲话，强拉或者强拆会失败";
            break;
        case 217:
            str = @"终端处在临时群组中";
            break;
        default:
            break;
    }
    if (str != nil) {
        [[iToast makeText:str] show];
    }
    
}





//http://39.104.57.38:80/StandardLoginAction_getUserVehicleContainsGroup.action?toMap=3
//http://39.104.57.38:80/StandardLoginAction_getUserVehicleContainsGroup.action?toMap=3


@end
