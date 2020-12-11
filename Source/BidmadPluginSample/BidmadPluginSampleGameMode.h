// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BidmadPluginSampleGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ABidmadPluginSampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABidmadPluginSampleGameMode();
    
    void OnRewardLoadAd(const FString&);
    void OnRewardShowAd(const FString&);
    void OnRewardFailedAd(const FString&);
    void OnRewardCompleteAd(const FString&);
    void OnRewardCloseAd(const FString&);
    void OnRewardClickAd(const FString&);
    void OnRewardSkippedAd(const FString&);
    
    void OnInterstitialLoadAd(const FString&);
    void OnInterstitialShowAd(const FString&);
    void OnInterstitialFailedAd(const FString&);
    void OnInterstitialCloseAd(const FString&);
};



