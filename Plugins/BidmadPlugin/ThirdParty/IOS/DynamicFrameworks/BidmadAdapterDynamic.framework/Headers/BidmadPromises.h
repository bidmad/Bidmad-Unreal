//
//  BidmadPromises.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/02/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadPromises : NSObject

+ (NSObject *)getFailPromiseForBidmadError:(NSInteger)bidmadErrorRaw;
+ (NSObject *)getFailPromiseForBidmadError:(NSInteger)bidmadErrorRaw detail:(NSString *)detail;
+ (NSObject *)getPendingPromise;
+ (void)fulfillPendingPromise:(NSObject *)pendingPromise withObject:(NSObject *)object;
+ (void)rejectPendingPromise:(NSObject *)pendingPromise withBidmadError:(NSInteger)bidmadErrorRaw detail:(NSString *)detail;
+ (void)rejectPendingPromise:(NSObject *)pendingPromise withBidmadError:(NSInteger)bidmadErrorRaw;

@end

NS_ASSUME_NONNULL_END
