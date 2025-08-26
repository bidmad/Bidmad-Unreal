// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BidmadENUM.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif

#if PLATFORM_IOS
#include "IOS/IOSAppDelegate.h"
#include <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#import <BidmadSDK/BidmadSDK-Swift.h>
#import <BidmadSDK/BidmadSDK.h>
#import <BidmadSDK/UnrealCommon.h>
#import <OpenBiddingHelper/OpenBiddingHelper-Swift.h>
#import <OpenBiddingHelper/OpenBiddingHelper.h>
#import <BidmadSDK/BIDMADGDPR.h>
#import <OpenBiddingHelper/BidmadAdFreeInformation.h>
#endif

#include "CommonInterface.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FBidmadCommon, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdTrackingAuthorizationResponse, const EBidmadTrackingAuthorizationStatus, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FInitializeSdkCallback, bool, isInitialized);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAdFreeCallback, bool, isAdFree);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Bidmad), meta=(BlueprintSpawnableComponent))
class BIDMADPLUGIN_API UCommonInterface : public USceneComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private: 
	FString mAppDomain;
	FString mCUID;
    
    UCommonInterface();
    
public:
    static UCommonInterface* mCommonInterface;
    
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    static UCommonInterface* GetCommonInterfaceInstance();
    
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Bidmad Function
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void InitializeSdkWithCallback(FString androidAppDomain, FString iosAppDomain);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void BindEventToOnInitializeSdk(const FInitializeSdkCallback& OnInitializeSdk);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void InitializeSdk(FString androidAppDomain, FString iosAppDomain);
	UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void SetDebugging(bool isDebugMod);
	UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void SetCUID(FString id);
	UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void SetChildDirected(bool childDirect);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void ReqAdTrackingAuthorization();
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void SetAdvertiserTrackingEnabled(bool enable);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    bool GetAdvertiserTrackingEnabled();
	UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void SetGdprConsent(bool consent, bool useArea);
	UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    int GetGdprConsent(bool useArea);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    void BindEventToOnAdFree(const FAdFreeCallback& OnAdFree);
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    bool IsAdFree();

    //Bidmad Callback
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadCommon")
	FOnAdTrackingAuthorizationResponse OnAdTrackingAuthorizationResponse;
    
    FInitializeSdkCallback InitializeSdkCallback;
    FAdFreeCallback AdFreeCallback;
};

#if PLATFORM_ANDROID
extern "C"{
	JNIEXPORT void JNICALL Java_ad_helper_openbidding_BidmadCommon_onInitializedCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_AdFreeInformation_onAdFreeCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadCommonInterface : NSObject <BIDMADUnrealCommonDelegate, BidmadAdFreeInformationDelegate>{}
+(BidmadCommonInterface *) getSharedInstance;
-(UnrealCommon *) getCommon;
- (void)setUseArea:(bool) useArea;
- (void)setGDPRSetting:(bool) consent;
- (int)getGDPRSetting;
- (void)didAdFreeInformationStatusChange:(BidmadAdFreeInformationStatus)status;
@end
#endif
