//
//  BidmadLoadStatus.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2022/10/18.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BidmadLoadStatus) {
    BidmadLoadStatusIdle,
    BidmadLoadStatusLoaded,
    BidmadLoadStatusLoading
};

@interface BidmadLoadStatusManager : NSObject

+ (NSString * _Nonnull)toString:(BidmadLoadStatus)status;

@end
