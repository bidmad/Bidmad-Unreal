//
//  BidmadSendLogDelegate.h
//  ADOPUtility
//
//  Created by Seungsub Oh on 2022/06/03.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <Foundation/Foundation.h>

@protocol BidmadSendLogDelegate <NSObject>

@optional
- (void)bidmadSendLogWithAdNetworkName:(NSString *)adNetworkName type:(NSString * _Nonnull)logType sessionId:(NSString * _Nonnull)sessionId;

@end
