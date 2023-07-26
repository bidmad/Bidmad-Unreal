//
//  BidmadCoupangInterstitial.h
//  BidmadCoupangAdapter
//
//  Created by Seungsub Oh on 2023/05/31.
//

#import <Foundation/Foundation.h>
#import <ADOPUtility/ADOPUtility.h>
#import "BidmadCoupangProduct.h"

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangFullscreenBase : BidmadAdapterAdEssential

@property (nonatomic) BOOL isInterstitial;
@property (nonatomic) NSArray<BidmadCoupangProduct *> *products;

@end

NS_ASSUME_NONNULL_END
