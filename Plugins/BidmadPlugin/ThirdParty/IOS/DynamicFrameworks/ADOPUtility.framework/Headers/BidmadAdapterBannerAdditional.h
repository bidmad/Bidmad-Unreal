//
//  BidmadAdapterBannerAdditional.h
//  BidmadSDK-DevSuite
//
//  Created by ADOP_Mac on 2022/07/01.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#define BIDMADBannerViewTagForCleaning 96076

@protocol BidmadAdapterBannerAdditional <NSObject>

- (void)setBannerSize:(NSString * _Nonnull)sizeString;
- (void)show;
- (void)hide;

@end
