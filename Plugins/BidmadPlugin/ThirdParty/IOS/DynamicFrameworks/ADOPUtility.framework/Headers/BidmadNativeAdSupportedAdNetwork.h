//
//  BidmadNativeAdSupportedAdNetwork.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2023/02/16.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, BidmadNativeAdSupportedAdNetwork) {
    BidmadNativeAdSupportedAdNetworkAdMob,
    BidmadNativeAdSupportedAdNetworkPangle,
    BidmadNativeAdSupportedAdNetworkTeads,
    BidmadNativeAdSupportedAdNetworkVungle,
    BidmadNativeAdSupportedAdNetworkCoupang,
    BidmadNativeAdSupportedAdNetworkNone,
};

@interface BidmadNativeAdSupportedAdNetworkManager : NSObject

+ (NSString *)getViewClassNameFromEnum:(BidmadNativeAdSupportedAdNetwork)enumValue;

@end
