//
//  BidmadSettingInterface.h
//  BidmadSDK-DevSuite
//
//  Created by Seungsub Oh on 2022/12/05.
//

#import <UIKit/UIKit.h>

@protocol BidmadSettingInterface <NSObject>

@required
+ (id<BidmadSettingInterface> _Nonnull)sharedInstance;
- (void)setAdvertiserTrackingEnabled:(BOOL)enable;
- (BOOL)getAdvertiserTrackingEnabled;
- (void)initializeSdk;
- (void)initializeSdkWithKey:(NSString *)appKey;
- (void)setIsChildDirectedAds: (BOOL)isChildDirectedAdsNeeded;
- (void)setUserConsentStatusForCCPACompliance: (BOOL)isUserConsent;

@property (nonatomic, assign) int                   refreshInterval;
@property (nonatomic, assign) int                   age;
@property (nonatomic)bool                           isDebug;
@property (nonatomic)bool                           isSendLog;
@property (nonatomic, strong) NSString*             interstitialZoneID;
@property (nonatomic, strong) NSString*             rewardZoneID;
@property (nonatomic, strong) NSString*             bannerZoneID;
@property (nonatomic, strong) NSString*             appOpenAdZoneID;
@property (nonatomic, strong) NSString*             gender;
@property (nonatomic, strong) NSString*             keyword;
@property (nonatomic, strong) NSString*             houseBannerURL;
@property (nonatomic, assign) float                 longitude;
@property (nonatomic, assign) float                 latitude;
@property (nonatomic) BOOL                       isPreviewHouse;
@property (nonatomic, strong) NSString*          houseBannerPath;
@property (nonatomic)  bool unityState;
@property (nonatomic) bool isIronInit;
@property (nonatomic, strong) NSNumber* isGADMobileAdsInitilized;
@property (nonatomic)  bool isBannerArpmVisible;
@property (nonatomic) bool isRewardCompleteInSetting;
@property (nonatomic, strong) NSString* version;
@property (nonatomic, strong) NSString* testDeviceId;
@property (nonatomic, strong) NSNumber* __nullable isChildDirectedTreatment;
@property (nonatomic, strong) NSNumber* __nullable isUserConsentCCPA;
@property (nonatomic, weak) id<BidmadSendLogDelegate> __nullable bidmadLogDelegate;
@property (nonatomic, strong) NSString * __nullable cuid;
@property (nonatomic) NSNumber * _Nonnull useServerSideCallback;
@property (readonly) BOOL isInitialized;

@end
