// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonInterfaceForBlueprint.generated.h"

UCLASS()
class BIDMADPLUGIN_API UCommonInterfaceForBlueprint : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable,Category="BidmadCommon")
    static FString GetPlatFormZoneId(FString zoneIdAOS, FString zoneIdiOS);
};
