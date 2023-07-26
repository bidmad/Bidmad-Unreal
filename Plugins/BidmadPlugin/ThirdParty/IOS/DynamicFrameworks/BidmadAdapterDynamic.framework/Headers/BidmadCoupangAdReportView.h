//
//  BidmadCoupangAdReportView.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/07/10.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangAdReportView : UIView

@property (nonatomic) BOOL isProduct1Selected;
@property (nonatomic) BOOL isProduct2Selected;

@property (nonatomic, strong) UIImage *imageProduct1;
@property (nonatomic, strong) UIImage *imageProduct2;

- (instancetype)initWithImageProduct1:(UIImage *)imageProduct1 imageProduct2:(UIImage * _Nullable)imageProduct2 action:(void (^)(NSUInteger))action;

@end

NS_ASSUME_NONNULL_END
