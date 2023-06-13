//
//  BIDMADNativeAdCommonInterface.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2022/07/26.
//

#import "BidmadNativeAdDataInterface.h"

@protocol BIDMADNativeAdCommonInterface
+ (id _Nonnull)requestFor:(NSString * _Nonnull)appid
                    pubID:(NSString * _Nullable)pubID
                  isDebug:(BOOL)isDebug
       isChildDirectedAds:(NSNumber * _Nullable)isChild;
@end
