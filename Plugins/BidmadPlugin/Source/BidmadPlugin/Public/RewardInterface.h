// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Misc/Guid.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif

#if PLATFORM_IOS

#include "IOS/IOSAppDelegate.h"
#include <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#import <OpenBiddingHelper/OpenBiddingHelper.h>

#endif

#include "RewardInterface.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FBidmadReward, Log, All);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadRewardLoadDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadRewardShowDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBidmadRewardFailDelegate, const FString&, ZoneId, const FString&, ErrorReason);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadRewardCompleteDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadRewardCloseDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadRewardSkipDelegate, const FString&, ZoneId);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Bidmad), meta=(BlueprintSpawnableComponent))
class BIDMADPLUGIN_API URewardInterface : public USceneComponent   
{
    GENERATED_BODY()
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
private:
#if PLATFORM_ANDROID
    void DeleteRefMember();
    void SetActivity();
    void MakeReward();
    
    JNIEnv* mEnv;
    jobject mJObj;
    jclass mJCls;
#elif PLATFORM_IOS
    OpenBiddingUnrealReward* unrealReward;
#endif
    void NewiOSInstance();
    void GetInstance();
    FString mZoneId;
    FString mId;
public:
    static TMap <FString, URewardInterface*> mRewardInterfaceMap;
    // Sets default values for this component's properties
    URewardInterface();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;  
    
    //Bidmad Fucntion
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void InitReward(FString androidZoneId, FString iosZoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void Load();
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void Show();
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    bool IsLoaded();

    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnLoad(const FOnBidmadRewardLoadDelegate& OnLoad);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnShow(const FOnBidmadRewardShowDelegate& OnShow);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnFail(const FOnBidmadRewardFailDelegate& OnFail);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnComplete(const FOnBidmadRewardCompleteDelegate& OnComplete);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnClose(const FOnBidmadRewardCloseDelegate& OnClose);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    void BindEventToOnSkip(const FOnBidmadRewardSkipDelegate& OnSkip);

    FOnBidmadRewardLoadDelegate OnLoadDelegate;
    FOnBidmadRewardShowDelegate OnShowDelegate;
    FOnBidmadRewardFailDelegate OnFailDelegate;
    FOnBidmadRewardCompleteDelegate OnCompleteDelegate;
    FOnBidmadRewardCloseDelegate OnCloseDelegate;
    FOnBidmadRewardSkipDelegate OnSkipDelegate;
};

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onLoadAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onShowAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onLoadFailAdCb(JNIEnv *, jobject, jstring, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCompleteAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCloseAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onSkippedAdCb(JNIEnv *, jobject, jstring, jstring);
}
#elif PLATFORM_IOS
@interface BidmadRewardInterface : NSObject <BidmadRewardUECallback>{
    id<BidmadRewardUECallback> delegate;
}
+ (BidmadRewardInterface*)getSharedInstance;
- (OpenBiddingUnrealReward *)newInstance:(NSString *)zoneID uuid:(NSString *)uuid;
- (OpenBiddingUnrealReward *)getInstance:(NSString *)zoneID;
@end
#endif
