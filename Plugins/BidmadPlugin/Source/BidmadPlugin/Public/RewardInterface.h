// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RewardCallback.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"

#if USE_ANDROID_JNI
#include "Android/AndroidJNI.h"

#endif
#endif

#if PLATFORM_IOS

#include "IOS/IOSAppDelegate.h"
#include "IOS/IOSView.h"

#include <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#import <BidmadSDK/BidmadSDK.h>

#endif

/**
 * 
 */
class BIDMADPLUGIN_API FRewardInterface
{
private:
#if PLATFORM_ANDROID && USE_ANDROID_JNI
    void DeleteRefMember();
    void SetActivity();
    void MakeReward();
    
    JNIEnv* mEnv;
    jobject mJObj;
    jclass mJCls;
#elif PLATFORM_IOS
    UnrealReward* unrealReward;
#endif
    void GetInstance();
    void SetAdInfo();
    FString mZoneId;
public:
    static TMap <FString, FRewardInterface*> mRewardInterfaceMap;    

    FRewardInterface(FString);
    
    void Load();
    void Show();
    bool IsLoaded();
};

#if PLATFORM_ANDROID && USE_ANDROID_JNI
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onLoadAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onShowAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onFailedAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCompleteAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onOpenAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCloseAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onClickAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onSkippedAdCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadRewardInterface : NSObject <BIDMADRewardVideoDelegate>{
    NSMutableDictionary* rewardList;
    id<BIDMADRewardVideoDelegate> delegate;
    UnrealReward * tempReward;
}
+ (BidmadRewardInterface*)getSharedInstance;
- (UnrealReward *)getRewardVideoByZone:(NSString *) zoneID;
- (void) loadSameZone:(NSString *)zoneId;
- (void) updateRewardList:(NSString *) zoneId;
@end
#endif
