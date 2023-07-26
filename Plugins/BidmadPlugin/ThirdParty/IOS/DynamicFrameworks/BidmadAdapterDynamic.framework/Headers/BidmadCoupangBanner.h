//
//  BidmadCoupangBanner.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/19.
//

#import <UIKit/UIKit.h>
#import <ADOPUtility/ADOPUtility.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, BidmadCoupangBannerSize) {
    BidmadCoupangBannerSize320x50,
    BidmadCoupangBannerSize320x100,
    BidmadCoupangBannerSize300x250,
    BidmadCoupangBannerSizeUnsupported,
};

@interface BidmadCoupangBanner : BidmadAdapterAdEssential

@property (nonatomic, copy, nullable) void (^adBlockHandler)(void);

@end

NS_ASSUME_NONNULL_END
