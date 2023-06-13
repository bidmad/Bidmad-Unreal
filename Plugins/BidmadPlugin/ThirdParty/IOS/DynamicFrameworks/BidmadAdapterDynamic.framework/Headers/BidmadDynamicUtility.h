//
//  BidmadDynamicUtility.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/02/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadDynamicUtility : NSObject

+ (NSError *)errorFromBidmadError:(NSInteger)integer;
+ (NSError *)errorFromBidmadError:(NSInteger)integer detail:(NSString *)detail;

@end

NS_ASSUME_NONNULL_END
