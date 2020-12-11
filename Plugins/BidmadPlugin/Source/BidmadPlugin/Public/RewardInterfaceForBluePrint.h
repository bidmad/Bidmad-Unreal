// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RewardInterfaceForBlueprint.generated.h"

UCLASS()
class BIDMADPLUGIN_API URewardInterfaceForBlueprint : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    static void NewRewardInstance(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    static void LoadReward(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    static void ShowReward(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    static bool IsLoadedReward(FString zoneId);
    UFUNCTION(BlueprintCallable,Category="BidmadReward")
    static void DeleteRewardInstance(FString zoneId);
};
