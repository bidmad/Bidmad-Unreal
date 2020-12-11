// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class BIDMADPLUGIN_API FInterstitialCallback{
public:
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnFailedAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCloseAd, const FString&);
    
    static FOnLoadAd OnLoadAd;
    static FOnShowAd OnShowAd;
    static FOnFailedAd OnFailedAd;
    static FOnCloseAd OnCloseAd;
};