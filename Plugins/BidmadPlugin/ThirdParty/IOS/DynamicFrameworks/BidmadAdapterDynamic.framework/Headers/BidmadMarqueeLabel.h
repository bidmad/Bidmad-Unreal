//
//  ADOPMarqueeLabel.h
//  ADOPMarqueeLabel
//
//  Created by Seungsub Oh on 2023/06/27.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadMarqueeLabel : UIView

@property (nonatomic, strong) NSString *text;
@property (nonatomic, strong) UIFont *font;
@property (nonatomic, readonly) CGSize intrinsicContentSize;

@end

NS_ASSUME_NONNULL_END
