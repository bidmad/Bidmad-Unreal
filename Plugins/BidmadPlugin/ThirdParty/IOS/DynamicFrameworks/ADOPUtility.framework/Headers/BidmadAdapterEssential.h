//
//  BidmadAdapterEssential.h
//  BidmadSDK-DevSuite
//
//  Created by ADOP_Mac on 2022/07/01.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <UIKit/UIKit.h>

@protocol BidmadAdapterEssential <NSObject>

@property (nonatomic, strong) id _Nullable bidmadController;
- (nonnull instancetype)initWithAppID:(NSString * _Nonnull)appID
                                pubID:(NSString * _Nullable)pubID
                               rootVC:(UIViewController * _Nullable)rootVC
                           parentView:(UIView * _Nullable)parentView
                              isChild:(NSNumber * _Nullable)isChild
                        isGDPRConsent:(NSNumber * _Nullable)isGDPRConsent
                        isCCPAConsent:(NSNumber * _Nullable)isCCPAConsent
                     bidmadController:(id _Nonnull)bidmadController;
- (void)load;
- (void)remove;
- (void)setIsDebug:(BOOL)isDebug;

@end
