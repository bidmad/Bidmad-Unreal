//
//  BidmadLoadabilityManager.h
//  ADOPUtility
//
//  Created by ADOP_Mac on 2022/07/01.
//

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <Foundation/Foundation.h>

/** _Nullable  _Nonnull
 when initializing, checker function → guard → get loadableConditionsPassed → startAdCycle
 if initializer timeout, fail → endAdCycle
 if loadableConditionsPassed false, fail → endAdCycle
 check if initialized → switch(to: loading)
 didload → switch(to: loaded)
 didfail → fail → endAdCycle
 remove → endAdCycle
 didshow → switch(to: isplaying)
 didclose → endAdCycle
 */

NS_ASSUME_NONNULL_BEGIN

static NSString * BIDMAD_LOADABILITY_INIT = @"BIDMAD_LOADABILITY_INIT";
static NSString * BIDMAD_LOADABILITY_LOADING = @"BIDMAD_LOADABILITY_LOADING";
static NSString * BIDMAD_LOADABILITY_LOADED = @"BIDMAD_LOADABILITY_LOADED";
static NSString * BIDMAD_LOADABILITY_PLAYING = @"BIDMAD_LOADABILITY_PLAYING";

typedef NS_ENUM(NSUInteger, BidmadAdStatus) {
    BidmadAdStatusIsInitProcess,
    BidmadAdStatusIsLoading,
    BidmadAdStatusIsLoaded,
    BidmadAdStatusIsPlaying
};

@interface BidmadLoadabilityManager : NSObject

@property (nonatomic, strong) NSMutableDictionary<NSUUID *, NSNumber *> *isInitProcess;
@property (nonatomic, strong) NSMutableDictionary<NSUUID *, NSNumber *> *isLoading;
@property (nonatomic, strong) NSMutableDictionary<NSUUID *, NSNumber *> *isLoaded;
@property (nonatomic, strong) NSMutableDictionary<NSUUID *, NSNumber *> *isPlaying;

- (instancetype)init;
- (void)startAdCycleWithTarget:(NSUUID *)target;
- (void)resetAdCycleWithTarget:(NSUUID *)target;
- (void)endAdCycle:(NSUUID *)target;
- (void)statusSwitchTo:(BidmadAdStatus)status target:(NSUUID *)target;
- (BOOL)initialLoadabilityCheck:(nonnull NSDictionary *)condition;
- (NSString *)description;

@end

NS_ASSUME_NONNULL_END
