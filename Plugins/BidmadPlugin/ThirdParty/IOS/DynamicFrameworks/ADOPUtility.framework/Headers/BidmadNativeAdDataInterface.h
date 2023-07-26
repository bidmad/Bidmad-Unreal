//
//  BidmadNativeAdDataInterface.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2022/07/26.
//

#import <UIKit/UIKit.h>

@protocol BidmadNativeAdDataInterface
- (nonnull instancetype)initWithIdentifier:(NSInteger)identifier;
@property (nonatomic) NSInteger id;
@property (nonatomic, copy) NSString * _Nullable headline;
@property (nonatomic, copy) NSString * _Nullable body;
@property (nonatomic, copy) NSString * _Nullable callToAction;
@property (nonatomic, strong) UIImage * _Nullable icon;
@property (nonatomic, strong) NSDecimalNumber * _Nullable starRating;
@property (nonatomic, copy) NSString * _Nullable store;
@property (nonatomic, copy) NSString * _Nullable price;
@property (nonatomic, copy) NSString * _Nullable advertiser;
@property (nonatomic, strong) id _Nullable nativeAdAdMob;
@property (nonatomic, strong) id _Nullable nativeAdPangle;
@property (nonatomic, strong) id _Nullable nativeAdTeads;
@property (nonatomic, strong) id _Nullable nativeAdVungle;
@property (nonatomic, strong) NSDictionary * _Nullable nativeAdCoupang;
@property (nonatomic, readonly, copy) NSString * _Nonnull description;
- (void)remove;
@end
