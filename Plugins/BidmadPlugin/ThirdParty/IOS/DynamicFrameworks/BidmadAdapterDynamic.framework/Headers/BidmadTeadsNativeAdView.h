//
//  BidmadTeadsNativeAdView.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/02/28.
//

#import <UIKit/UIKit.h>
#import <TeadsSDK/TeadsSDK.h>
#import <ADOPUtility/ADOPUtility.h>

NS_ASSUME_NONNULL_BEGIN

@class BIDMADNativeAdView;

@interface BidmadTeadsNativeAdView : UIView <BidmadNativeAdViewContainerProtocol>

@property (nonatomic, weak) BIDMADNativeAdView *adView;

@end

NS_ASSUME_NONNULL_END
