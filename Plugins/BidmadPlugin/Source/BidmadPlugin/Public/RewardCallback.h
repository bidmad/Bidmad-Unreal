// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Callback Interface
class BIDMADPLUGIN_API FRewardCallback{
public:
    
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnFailedAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleteAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCloseAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnClickAd, const FString&);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkippedAd, const FString&);
    
    static FOnLoadAd OnLoadAd;
    static FOnShowAd OnShowAd;
    static FOnFailedAd OnFailedAd;
    static FOnCompleteAd OnCompleteAd;
    static FOnOpenAd OnOpenAd;
    static FOnCloseAd OnCloseAd;
    static FOnClickAd OnClickAd;
    static FOnSkippedAd OnSkippedAd;
};
