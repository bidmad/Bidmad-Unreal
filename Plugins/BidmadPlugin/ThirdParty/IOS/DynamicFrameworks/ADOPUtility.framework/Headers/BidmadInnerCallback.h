//
//  BidmadInnerCallbackCases.h
//  BidmadSDK-DevSuite
//
//  Created by ADOP_Mac on 2022/06/30.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

typedef NS_CLOSED_ENUM(NSUInteger, BidmadInnerCallback) {
    BidmadInnerCallbackLoad,
    BidmadInnerCallbackFail,
    BidmadInnerCallbackClick,
    BidmadInnerCallbackShow,
    BidmadInnerCallbackClose,
    BidmadInnerCallbackSkipped,
    BidmadInnerCallbackRewarded,
    BidmadInnerCallbackInit,
    BidmadInnerCallbackInit_fail
};
