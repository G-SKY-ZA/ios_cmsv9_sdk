//
//  GroupDetail.m
//  cmsv9demo
//
//  Created by tongtianxing on 2019/1/28.
//  Copyright © 2019 tongtianxing. All rights reserved.
//

#import "GroupDetail.h"

#import "ViewController.h"

@implementation GroupDetail

//+(GroupDetail*)singleton
//{
//    static GroupDetail *groupDetail = nil;
//    static dispatch_once_t onceToken;
//    dispatch_once(&onceToken, ^{
//        groupDetail = [[GroupDetail alloc] init];
//    });
//    return groupDetail;
//}

//获取组和组员
+(void)requestGroupMemberInfo
{
    ViewController *vc = [ViewController viewController];
    NSString *serverAddr =  [NSString stringWithFormat:@"http://%@/",vc.server];
    NSMutableString *str = [[NSMutableString alloc] initWithString:serverAddr];
    [str appendString: @"StandardCooperateAction_getUserDispatch.action"];
    
    [vc.manage POST:str parameters:nil headers:nil progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        NSDictionary *dict = responseObject;
        if ([dict[@"result"] intValue] == 0) {
            
            [vc.groupsDict removeAllObjects];
            [vc.groupsArray removeAllObjects];
            [vc.gMembersDict removeAllObjects];
            [vc.gMembersArray removeAllObjects];
            [vc.groupMemberDict removeAllObjects];
            
            NSArray *lstGroup = [dict valueForKey: @"lstGroup"];
            for (NSDictionary *dict1 in lstGroup) {
                GroupModel *groupModel = [GroupModel yy_modelWithDictionary:dict1];
                [vc.groupsDict setObject:groupModel forKey:[NSString stringWithFormat:@"%zd",groupModel.id]];
                [vc.groupsArray addObject:groupModel];
            }
            
            NSArray *lstMember = [dict valueForKey: @"lstMember"];
            for (NSDictionary *dict2 in lstMember) {
                GroupMemberModel *gMemberModel = [GroupMemberModel yy_modelWithDictionary:dict2];
                
                NSString *groupId = [NSString stringWithFormat:@"%zd",gMemberModel.disId];
                
                [vc.gMembersDict setObject:gMemberModel forKey:[NSString stringWithFormat:@"%@:%@",groupId,gMemberModel.name]];
                [vc.gMembersArray addObject:gMemberModel];
                
                if (![vc.groupMemberDict objectForKey:groupId]) {
                    NSMutableArray *arr = [NSMutableArray array];
                    [vc.groupMemberDict setObject:arr forKey:groupId];
                }
                NSMutableArray *arr = [vc.groupMemberDict objectForKey:groupId];
                [arr addObject:gMemberModel];
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                [vc.groupTable reloadData];
            });
        }else{
           
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {

    }];
    
}













@end
