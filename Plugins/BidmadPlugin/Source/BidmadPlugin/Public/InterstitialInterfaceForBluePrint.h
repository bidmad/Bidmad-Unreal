// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InterstitialInterfaceForBlueprint.generated.h"

UCLASS()
class BIDMADPLUGIN_API UInterstitialInterfaceForBlueprint : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    static void NewInterstitialInstance(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    static void LoadInterstitial(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    static void ShowInterstitial(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    static bool IsLoadedInterstitial(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
    static void DeleteInstanceInterstitial(FString zoneId);
};
