// Copyright Epic Games, Inc. All Rights Reserved.

#include "BidmadPlugin.h"
#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#if USE_ANDROID_JNI
#include "Android/AndroidJNI.h"
#endif
#endif


#if PLATFORM_IOS
#include <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#import <BidmadSDK/BidmadSDK.h>
#endif

#define LOCTEXT_NAMESPACE "FBidmadPluginModule"

DEFINE_LOG_CATEGORY(FBidmadPlugin);

bool FBidmadPluginModule::isBidmadModuleStart = false;

void FBidmadPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    FBidmadPluginModule::isBidmadModuleStart = true;
}

void FBidmadPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    FBidmadPluginModule::isBidmadModuleStart = false;
}

void FBidmadPluginModule::SetDebugging(bool isDebugMod){
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    
    jclass mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/Common");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "setDebugging", "(Z)V", false);
    mEnv->CallStaticVoidMethod(mJCls, jniM, isDebugMod);

    mEnv->DeleteGlobalRef(mJCls);
    #elif PLATFORM_IOS
        [[BIDMADSetting sharedInstance]setIsDebug:isDebugMod];
    #endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBidmadPluginModule, BidmadPlugin)
