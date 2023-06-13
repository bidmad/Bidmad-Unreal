//
//  BidmadMobonBannerBridge.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2022/12/22.
//

#import <UIKit/UIKit.h>

@protocol BidmadMobonBannerBridgeDelegate;

@protocol BidmadMobonBannerBridge <NSObject>
@property (nonatomic, strong) id <BidmadMobonBannerBridgeDelegate> _Nullable delegate;
@property (nonatomic, strong) UIViewController * _Nullable rootViewController;
@property (nonatomic) NSInteger interval;
- (nonnull instancetype)initWithFrame:(CGRect)frame mediaCode:(NSString * _Nonnull)mediaCode sCode:(NSString * _Nonnull)sCode;
- (void)loadAd;
- (void)pauseUpdateAd;
@end

@protocol BidmadMobonBannerBridgeDelegate <NSObject>
- (void)adViewDidReceiveAd:(UIView<BidmadMobonBannerBridge> * _Nonnull)bannerAdView;
- (void)adViewFailedAd:(UIView<BidmadMobonBannerBridge> * _Nullable)bannerAdView :(NSString * _Nonnull)error;
- (void)adViewClicked:(UIView<BidmadMobonBannerBridge> * _Nonnull)bannerAdView;
@end

@protocol BidmadMobonInterstitialBridgeDelegate;

@protocol BidmadMobonInterstitialBridge <NSObject>
@property (nonatomic, strong) id <BidmadMobonInterstitialBridgeDelegate> _Nullable delegate;
@property (nonatomic, strong) UIViewController * _Nullable rootViewController;
@property (nonatomic, readonly) BOOL isADLoaded;
@property (nonatomic, readonly) UIInterfaceOrientationMask supportedInterfaceOrientations;
@property (nonatomic, readonly) UIInterfaceOrientation preferredInterfaceOrientationForPresentation;
- (nonnull instancetype)initWithMediaCode:(NSString * _Nonnull)mediaCode unitId:(NSString * _Nonnull)unitId type:(NSInteger)type;
- (void)viewDidLoad;
- (void)viewWillAppear:(BOOL)animated;
- (void)viewWillDisappear:(BOOL)animated;
- (void)loadAd;
- (void)show;
- (void)dismiss;
@end

@protocol BidmadMobonInterstitialBridgeDelegate <NSObject>
- (void)interstitialAdNotLoaded:(UIViewController<BidmadMobonInterstitialBridge> * _Nonnull)interstitialAdView;
- (void)interstitialDidReceiveAd:(UIViewController<BidmadMobonInterstitialBridge> * _Nonnull)interstitialAdView;
- (void)interstitialFailedAd:(UIViewController<BidmadMobonInterstitialBridge> * _Nullable)interstitialAdView :(NSString * _Nonnull)error;
- (void)interstitialClicked:(UIViewController<BidmadMobonInterstitialBridge> * _Nonnull)interstitialAdView;
- (void)interstitialClose:(UIViewController<BidmadMobonInterstitialBridge> * _Nonnull)interstitialAdView;
@end
