//
//  BidmadCoupangRewardADOP.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/22.
//

#import "BidmadCoupangFullscreenBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangRewardADOP : BidmadCoupangFullscreenBase

@property (nonatomic, copy, nullable) void (^adBlockHandler)(void);

@end

NS_ASSUME_NONNULL_END
