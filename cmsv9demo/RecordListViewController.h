//
//  RecordListViewController.h
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RecordListViewController : UIViewController
@property (nonatomic , strong) UITableView *recordList;
-(void)addRecordList:(NSDictionary*)dict;
@end

NS_ASSUME_NONNULL_END
