// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

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

#include "RewardInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFailedBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCloseBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickBidmadRewardAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkippedBidmadRewardAd, const FString&, ZoneId);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Bidmad), meta=(BlueprintSpawnableComponent))
class BIDMADPLUGIN_API URewardInterface : public USceneComponent   
{
    GENERATED_BODY()
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
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
    void NewiOSInstance();
    void GetInstance();
    void SetAdInfo();
    FString mZoneId;
public:
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

    //Bidmad Callback
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnLoadBidmadRewardAd OnLoadBidmadRewardAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnShowBidmadRewardAd OnShowBidmadRewardAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnFailedBidmadRewardAd OnFailedBidmadRewardAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnCompleteBidmadRewardAd OnCompleteBidmadRewardAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnCloseBidmadRewardAd OnCloseBidmadRewardAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadReward")
    FOnSkippedBidmadRewardAd OnSkippedBidmadRewardAd;
};

#if PLATFORM_ANDROID && USE_ANDROID_JNI
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onLoadAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onShowAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onFailedAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCompleteAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCloseAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onSkippedAdCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadRewardInterface : NSObject <BIDMADRewardVideoDelegate>{
    id<BIDMADRewardVideoDelegate> delegate;
}
+ (BidmadRewardInterface*)getSharedInstance;
- (UnrealReward *)newInstance:(NSString *)zoneID;
- (UnrealReward *)getInstance:(NSString *)zoneID;
@end
#endif
