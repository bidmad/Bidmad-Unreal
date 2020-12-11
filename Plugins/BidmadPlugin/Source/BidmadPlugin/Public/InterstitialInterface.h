// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterstitialCallback.h"
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

class BIDMADPLUGIN_API FInterstitialInterface
{
private:
#if PLATFORM_ANDROID && USE_ANDROID_JNI
    void DeleteRefMember();
    void SetActivity();
    void MakeInterstitial();
    
    JNIEnv* mEnv;
    jobject mJObj;
    jclass mJCls;
#elif PLATFORM_IOS
    UnrealInterstitial* unrealInterstitial;
#endif
    void GetInstance();
    void SetAdInfo();
    FString mZoneId;
public:
    static TMap <FString, FInterstitialInterface*> mInterstitialInterfaceMap;

    FInterstitialInterface(FString);

    void Load();
    void Show();
    bool IsLoaded();
};

#if PLATFORM_ANDROID && USE_ANDROID_JNI
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onLoadAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onFailedAdCb(JNIEnv *, jobject, jstring);
    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *, jobject, jstring);
}
#elif PLATFORM_IOS
@interface BidmadInterstitialInterface : NSObject <BIDMADInterstitialDelegate>{
    NSMutableDictionary* interstitialList;
    id<BIDMADInterstitialDelegate> delegate;
    UnrealInterstitial * tempInterstitial;
}
+ (BidmadInterstitialInterface *) getSharedInstance;
- (UnrealInterstitial *)getInterstitialByZone:(NSString *)zoneID;
- (void) loadSameZone:(NSString *)zoneId;
- (void) updateInterstitialList:(NSString *) zoneId;
@end
#endif
