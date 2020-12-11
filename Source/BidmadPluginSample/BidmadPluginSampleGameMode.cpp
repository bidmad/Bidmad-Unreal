// Copyright Epic Games, Inc. All Rights Reserved.

#include "BidmadPluginSampleGameMode.h"

#include "RewardCallback.h"
#include "RewardInterface.h"
#include "InterstitialCallback.h"
#include "InterstitialInterface.h"
#include "BidmadPlugin.h"

ABidmadPluginSampleGameMode::ABidmadPluginSampleGameMode()
{
    if(FBidmadPluginModule::isBidmadModuleStart){
        UE_LOG(LogTemp, Warning, TEXT("[ABidmadPluginSampleGameMode] Callback Reg #####"));
        FBidmadPluginModule::SetDebugging(true);
        FRewardCallback::OnLoadAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardLoadAd);
        FRewardCallback::OnShowAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardShowAd);
        FRewardCallback::OnFailedAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardFailedAd);
        FRewardCallback::OnCompleteAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardCompleteAd);
        FRewardCallback::OnCloseAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardCloseAd);
        FRewardCallback::OnClickAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardClickAd);
        FRewardCallback::OnSkippedAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnRewardSkippedAd);
        
        FInterstitialCallback::OnLoadAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnInterstitialLoadAd);
        FInterstitialCallback::OnShowAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnInterstitialShowAd);
        FInterstitialCallback::OnFailedAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnInterstitialFailedAd);
        FInterstitialCallback::OnCloseAd.AddUObject(this,
                &ABidmadPluginSampleGameMode::OnInterstitialCloseAd);
    }
}

//Reward Callback
void ABidmadPluginSampleGameMode::OnRewardLoadAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardLoadAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardShowAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardShowAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardFailedAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardFailedAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardCompleteAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardCompleteAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardCloseAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardCloseAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardClickAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardClickAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardSkippedAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardSkippedAd] #####"));
}

//Interstitial Callback
void ABidmadPluginSampleGameMode::OnInterstitialLoadAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnInterstitialLoadAd] #####"));
}
void ABidmadPluginSampleGameMode::OnInterstitialShowAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnInterstitialShowAd] #####"));
}
void ABidmadPluginSampleGameMode::OnInterstitialFailedAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnInterstitialFailedAd] #####"));
}
void ABidmadPluginSampleGameMode::OnInterstitialCloseAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnInterstitialCloseAd] #####"));
}
