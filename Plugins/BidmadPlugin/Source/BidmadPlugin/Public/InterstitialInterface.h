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

#include "InterstitialInterface.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FBidmadInterstitial, Log, All);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadInterstitialLoadDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadInterstitialShowDelegate, const FString&, ZoneId);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBidmadInterstitialFailDelegate, const FString&, ZoneId, const FString&, ErrorReason);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBidmadInterstitialCloseDelegate, const FString&, ZoneId);

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
    FString mZoneId;
    FString mId;
public:
    static TMap <FString, UInterstitialInterface*> mInterstitialInterfaceMap;
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

    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void BindEventToOnLoad(const FOnBidmadInterstitialLoadDelegate& OnLoad);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void BindEventToOnShow(const FOnBidmadInterstitialShowDelegate& OnShow);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void BindEventToOnFail(const FOnBidmadInterstitialFailDelegate& OnFail);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    void BindEventToOnClose(const FOnBidmadInterstitialCloseDelegate& OnClose);

    FOnBidmadInterstitialLoadDelegate OnLoadDelegate;
    FOnBidmadInterstitialShowDelegate OnShowDelegate;
    FOnBidmadInterstitialFailDelegate OnFailDelegate;
    FOnBidmadInterstitialCloseDelegate OnCloseDelegate;
};

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onLoadAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *, jobject, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onLoadFailAdCb(JNIEnv *, jobject, jstring, jstring, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *, jobject, jstring, jstring);
}
#elif PLATFORM_IOS
@interface BidmadInterstitialInterface : NSObject <BidmadInterstitialUECallback>{
    id<BidmadInterstitialUECallback> delegate;
}
+ (BidmadInterstitialInterface *) getSharedInstance;
- (OpenBiddingUnrealInterstitial *)newInstance:(NSString *)zoneID uuid:(NSString *)uuid;
- (OpenBiddingUnrealInterstitial *)getInstance:(NSString *)uuid;
@end
#endif
