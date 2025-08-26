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
#import <BidmadSDK/BidmadSDK-Swift.h>
#import <BidmadSDK/BidmadSDK.h>
#import <OpenBiddingHelper/OpenBiddingHelper-Swift.h>
#import <OpenBiddingHelper/OpenBiddingHelper.h>
#import <BidmadSDK/UnrealGDPRforGoogle.h>
#import <BidmadSDK/BIDMADGDPRforGoogle.h>
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#endif

#include "GoogleGdprConsentInterface.generated.h"
/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(FBidmadGoogleGDPR, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConsentInfoUpdateSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConsentInfoUpdateFailure, const FString&, ErrorMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConsentFormLoadSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConsentFormLoadFailure, const FString&, ErrorMsg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConsentFormDismissed, const FString&, ErrorMsg);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Bidmad), meta=(BlueprintSpawnableComponent))
class BIDMADPLUGIN_API UGoogleGdprConsentInterface : public USceneComponent
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
#if PLATFORM_ANDROID
    void DeleteRefMember();
    
    JNIEnv* mEnv;
    jobject mJObj;
    jclass mJCls;
#elif PLATFORM_IOS
#endif
public:
    static UGoogleGdprConsentInterface* mGoogleGdprConsentInterface;
	// Sets default values for this component's properties
	UGoogleGdprConsentInterface();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Bidmad Function
    void GetInstance();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void SetDebug(FString testDeviceId, bool isEEA);
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    bool IsConsentFormAvailable();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    int GetConsentStatus();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void Reset();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void RequestConsentInfoUpdate();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void LoadForm();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void ShowForm();
	UFUNCTION(BlueprintCallable,Category="BidmadGDPRConsent")
    void SetListener();

    //Bidmad Callback
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadGDPRConsent")
	FOnConsentInfoUpdateSuccess OnConsentInfoUpdateSuccess;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadGDPRConsent")
	FOnConsentInfoUpdateFailure OnConsentInfoUpdateFailure;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadGDPRConsent")
	FOnConsentFormLoadSuccess OnConsentFormLoadSuccess;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadGDPRConsent")
	FOnConsentFormLoadFailure OnConsentFormLoadFailure;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "BidmadGDPRConsent")
	FOnConsentFormDismissed OnConsentFormDismissed;
};

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateSuccessCb(JNIEnv *, jobject);
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateFailureCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadSuccessCb(JNIEnv *, jobject);
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadFailureCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormDismissedCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadGdprConsentInterface : NSObject<BIDMADGDPRforGoogleProtocol>{}
+(BidmadGdprConsentInterface *) getSharedInstance;
-(void)setDelegate;
-(void)setListener;
-(void)setDebug:(NSString*)testDeviceId isEEA:(BOOL)isTestEurope;
-(BOOL)isConsentFormAvailable;
-(int)getConsentStatus;
-(void)reset;
-(void)requestConsentInfoUpdate;
-(void)loadForm;
-(void)showForm;
//Bidmad Callback
- (void)onConsentFormDismissed:(NSError *)formError;
- (void)onConsentFormLoadFailure:(NSError *)formError;
- (void)onConsentFormLoadSuccess;
- (void)onConsentInfoUpdateFailure:(NSError *)formError;
- (void)onConsentInfoUpdateSuccess;
@end
#endif
