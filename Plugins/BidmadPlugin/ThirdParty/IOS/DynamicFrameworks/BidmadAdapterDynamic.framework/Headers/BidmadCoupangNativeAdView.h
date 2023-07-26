//
//  BidmadCoupangNativeAdView.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/20.
//

#import <UIKit/UIKit.h>
#import <ADOPUtility/ADOPUtility.h>

NS_ASSUME_NONNULL_BEGIN

@class BIDMADNativeAdView;

@interface BidmadCoupangNativeAdView : UIView <BidmadNativeAdViewContainerProtocol>

@property (nonatomic, weak) BIDMADNativeAdView *adView;

@end

NS_ASSUME_NONNULL_END
