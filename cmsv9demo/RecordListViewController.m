//
//  RecordListViewController.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/29.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "RecordListViewController.h"
#import "LibFunction.h"
#import "DownRecordPlayer.h"
@interface RecordListViewController ()<UITableViewDelegate,UITableViewDataSource>



@property (nonatomic , strong) NSMutableArray *dataSource;

@end

@implementation RecordListViewController

-(NSMutableArray *)dataSource
{
    if (_dataSource == nil) {
        _dataSource = [NSMutableArray array];
    }
    return _dataSource;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _recordList = [[UITableView alloc]initWithFrame:self.view.bounds style:UITableViewStylePlain];
    _recordList.delegate = self;
    _recordList.dataSource = self;
    [self.view addSubview:_recordList];
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataSource.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *identifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:identifier];
    }
    NSDictionary *dict = _dataSource[indexPath.row];
    cell.textLabel.text = dict[SenderNameKey];
    cell.detailTextLabel.text = dict[FilePathKey];
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
     NSDictionary *dict = _dataSource[indexPath.row];
     [[DownRecordPlayer player] appendRecordAudioFileDict:dict];
}

-(void)addRecordList:(NSDictionary*)dict
{

    [self.dataSource addObject:dict];
    dispatch_async(dispatch_get_main_queue(), ^{
       [_recordList reloadData];
    });
   
}
    



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
