// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

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

#include "InterstitialInterface.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FBidmadInterstitial, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadBidmadInterstitialAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowBidmadInterstitialAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFailedBidmadInterstitialAd, const FString&, ZoneId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCloseBidmadInterstitialAd, const FString&, ZoneId);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Bidmad), meta=(BlueprintSpawnableComponent))
class BIDMADPLUGIN_API UInterstitialInterface : public USceneComponent
{
    GENERATED_BODY()
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
private:
#if PLATFORM_ANDROID
    void DeleteRefMember();
    void SetActivity();
    void MakeInterstitial();
    
    JNIEnv* mEnv;
    jobject mJObj;
    jclass mJCls;
#elif PLATFORM_IOS
    OpenBiddingUnrealInterstitial* unrealInterstitial;
#endif
    void NewiOSInstance();
    void GetInstance();
    void SetAdInfo();
    FString mZoneId;
public:
    // Sets default values for this component's properties
    UInterstitialInterface();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    //Bidmad Function
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void InitInterstitial(FString androidZoneId, FString iosZoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void Load();
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void Show();
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    bool IsLoaded();

    //Bidmad Callback
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadInterstitial")
    FOnLoadBidmadInterstitialAd OnLoadBidmadInterstitialAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadInterstitial")
    FOnShowBidmadInterstitialAd OnShowBidmadInterstitialAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadInterstitial")
    FOnFailedBidmadInterstitialAd OnFailedBidmadInterstitialAd;
    UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadInterstitial")
    FOnCloseBidmadInterstitialAd OnCloseBidmadInterstitialAd;
};

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onLoadAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onFailedAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadInterstitialInterface : NSObject <BIDMADOpenBiddingInterstitialDelegate>{
    id<BIDMADOpenBiddingInterstitialDelegate> delegate;
}
+ (BidmadInterstitialInterface *) getSharedInstance;
- (OpenBiddingUnrealInterstitial *)newInstance:(NSString *)zoneID;
- (OpenBiddingUnrealInterstitial *)getInstance:(NSString *)zoneID;
@end
#endif
