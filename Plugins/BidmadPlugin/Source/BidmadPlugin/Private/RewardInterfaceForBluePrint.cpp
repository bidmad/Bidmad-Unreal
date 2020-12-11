// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardInterfaceForBlueprint.h"
#include "RewardInterface.h"


void URewardInterfaceForBlueprint::NewRewardInstance(FString zoneId)
{
    bool isInstance = FRewardInterface::mRewardInterfaceMap.Contains(zoneId);

    if(!isInstance){
        FRewardInterface* ri = new FRewardInterface(zoneId);
        FRewardInterface::mRewardInterfaceMap.Add(zoneId, ri);
    }
}

void URewardInterfaceForBlueprint::LoadReward(FString zoneId)
{
    bool isInstance = FRewardInterface::mRewardInterfaceMap.Contains(zoneId);

    if(isInstance){
        FRewardInterface* ri = FRewardInterface::mRewardInterfaceMap[zoneId];
        ri->Load();
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterfaceForBlueprint::Load] Instance not found #####"));
    }
}

void URewardInterfaceForBlueprint::ShowReward(FString zoneId)
{
    bool isInstance = FRewardInterface::mRewardInterfaceMap.Contains(zoneId);

    if(isInstance){
        FRewardInterface* ri = FRewardInterface::mRewardInterfaceMap[zoneId];
        ri->Show();
    }else{
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterfaceForBlueprint::Show] Instance not found #####"));
    }
}

bool URewardInterfaceForBlueprint::IsLoadedReward(FString zoneId)
{
    bool isInstance = FRewardInterface::mRewardInterfaceMap.Contains(zoneId);
    if(isInstance){
        FRewardInterface* ri = FRewardInterface::mRewardInterfaceMap[zoneId];
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterfaceForBlueprint::IsLoaded] IsLoaded : %d #####"), ri->IsLoaded());
        return ri->IsLoaded();
    }else{      
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterfaceForBlueprint::IsLoaded] Instance not found #####"));
        return false;
    }
}

void URewardInterfaceForBlueprint::DeleteRewardInstance(FString zoneId)
{
    bool isInstance = FRewardInterface::mRewardInterfaceMap.Contains(zoneId);

    if(isInstance){
        FRewardInterface* ri = FRewardInterface::mRewardInterfaceMap[zoneId];
        FRewardInterface::mRewardInterfaceMap.Remove(zoneId);
        delete ri;
    }else{      
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterfaceForBlueprint::DeleteInstance] Instance not found #####"));
    }
}
