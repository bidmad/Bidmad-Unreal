// Fill out your copyright notice in the Description page of Project Settings.


#include "InterstitialInterfaceForBlueprint.h"
#include "InterstitialInterface.h"

void UInterstitialInterfaceForBlueprint::NewInterstitialInstance(FString zoneId)
{
    bool isInstance = FInterstitialInterface::mInterstitialInterfaceMap.Contains(zoneId);
    
    if(!isInstance){
        FInterstitialInterface* ii = new FInterstitialInterface(zoneId);
        FInterstitialInterface::mInterstitialInterfaceMap.Add(zoneId, ii);
    }
}

void UInterstitialInterfaceForBlueprint::LoadInterstitial(FString zoneId)
{
    bool isInstance = FInterstitialInterface::mInterstitialInterfaceMap.Contains(zoneId);

    if(isInstance){
        FInterstitialInterface* ii = FInterstitialInterface::mInterstitialInterfaceMap[zoneId];
        ii->Load();
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterfaceForBlueprint::Load] Instance not found #####"));
    }
}

void UInterstitialInterfaceForBlueprint::ShowInterstitial(FString zoneId)
{
    bool isInstance = FInterstitialInterface::mInterstitialInterfaceMap.Contains(zoneId);

    if(isInstance){
        FInterstitialInterface* ii = FInterstitialInterface::mInterstitialInterfaceMap[zoneId];
        ii->Show();
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterfaceForBlueprint::Show] Instance not found #####"));
    }
}

bool UInterstitialInterfaceForBlueprint::IsLoadedInterstitial(FString zoneId)
{
    bool isInstance = FInterstitialInterface::mInterstitialInterfaceMap.Contains(zoneId);

    if(isInstance){
        FInterstitialInterface* ii = FInterstitialInterface::mInterstitialInterfaceMap[zoneId];
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterfaceForBlueprint::IsLoadedInterstitial] IsLoaded : %d #####"), ii->IsLoaded());
        return ii->IsLoaded();
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterfaceForBlueprint::IsLoaded] Instance not found #####"));
        return false;
    }
}

void UInterstitialInterfaceForBlueprint::DeleteInstanceInterstitial(FString zoneId)
{    
    bool isInstance = FInterstitialInterface::mInterstitialInterfaceMap.Contains(zoneId);

    if(isInstance){
        FInterstitialInterface* ii = FInterstitialInterface::mInterstitialInterfaceMap[zoneId];
        FInterstitialInterface::mInterstitialInterfaceMap.Remove(zoneId);
        delete ii;
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterfaceForBlueprint::DeleteInstance] Instance not found #####"));
    }
}
