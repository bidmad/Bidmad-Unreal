//
//  BidmadCoupangTouchdownGestureRecognizer.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/20.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangTouchdownGestureRecognizer : UIGestureRecognizer

- (instancetype)initWithAction:(void (^)(UIGestureRecognizerState))action;
@property (nonatomic, copy, nullable) void (^action)(UIGestureRecognizerState);

@end

NS_ASSUME_NONNULL_END
