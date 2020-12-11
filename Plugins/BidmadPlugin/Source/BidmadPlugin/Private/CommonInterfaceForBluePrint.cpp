// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonInterfaceForBlueprint.h"


FString UCommonInterfaceForBlueprint::GetPlatFormZoneId(FString zoneIdAOS, FString zoneIdiOS)
{
    #if PLATFORM_ANDROID
    return zoneIdAOS;
    #else //PLATFORM_IOS 
    return zoneIdiOS;
    #endif
}
