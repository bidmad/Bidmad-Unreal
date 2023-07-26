//
//  BidmadCoupangInterstitialADOP.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/22.
//

#import "BidmadCoupangRewardADOP.h"

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangInterstitialADOP : BidmadCoupangFullscreenBase

@property (nonatomic, copy, nullable) void (^adBlockHandler)(void);

@end

NS_ASSUME_NONNULL_END
