//
//  BidmadCoupangProduct.h
//  BidmadAdapterDynamic
//
//  Created by Seungsub Oh on 2023/06/16.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BidmadCoupangProduct : NSObject

@property (nonatomic, strong) NSString *productName;
@property (nonatomic, assign) NSInteger productPrice;
@property (nonatomic, strong) NSURL *productImageURL;
@property (nonatomic, strong) NSURL *landingURL;
@property (nonatomic, strong) NSURL *impressionURL;
@property (nonatomic, assign) BOOL isRocket;

@end

@interface BidmadCoupangProductsFetcher : NSObject

+ (void)sendImpressionLog:(NSURL *)impressionLogURL completionHandler:(void (^)(BOOL))completionHandler;
+ (void)openAdReportWebWithProduct1:(BidmadCoupangProduct *)product1 product2:(BidmadCoupangProduct * _Nullable)product2;
+ (void)getCoupangAdsFromParameters:(NSArray<NSString *> *)parameters
                  completionHandler:(void (^)(NSArray<BidmadCoupangProduct *> *, NSError *))completionHandler;
+ (void)getImagesFromUrls:(NSArray<NSURL *> *)urls completionHandler:(void (^)(NSArray *))completionHandler;

@end

@interface BidmadCoupangProductsParser : NSObject

+ (NSArray<BidmadCoupangProduct *> *)parseJSONData:(NSData *)jsonData;

@end

@interface NSArray (BidmadCoupangProductsHelper)

- (NSArray<NSURL *> *)coupangProductsImageUrls;
- (NSArray<NSArray *> *)imagesFilterNullWithProducts:(NSArray<BidmadCoupangProduct *> *)products;
- (NSArray *)shuffled;

@end

@interface UIImage (BidmadCoupangImageProcessor)

- (UIImage *)applyBlurWithRadius:(CGFloat)radius;

@end

NS_ASSUME_NONNULL_END
