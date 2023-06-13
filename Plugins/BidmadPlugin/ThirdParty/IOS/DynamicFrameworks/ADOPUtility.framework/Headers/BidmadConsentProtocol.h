//
//  BidmadConsentProtocol.h
//  ADOPUtility
//
//  Created by ADOP_Mac on 2022/06/15.
//

#import <UIKit/UIKit.h>

@protocol BidmadConsentProtocol <NSObject>

+ (void)setGDPR:(NSNumber * _Nullable)gdprConsent;

@end
