// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonInterface.h"
#include "Engine.h"

UCommonInterface::UCommonInterface()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UCommonInterface::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


// Called every frame
void UCommonInterface::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UCommonInterface::SetDebugging(bool isDebugMod){
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    
    jclass mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/Common");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "setDebugging", "(Z)V", false);
    mEnv->CallStaticVoidMethod(mJCls, jniM, isDebugMod);

    mEnv->DeleteGlobalRef(mJCls);
    #elif PLATFORM_IOS
    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon setDebugMode:isDebugMod];
    #endif
}

void UCommonInterface::ReqAdTrackingAuthorization(){
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    #elif PLATFORM_IOS
    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon reqAdTrackingAuthorization];
    #endif
}

void UCommonInterface::SetAdvertiserTrackingEnabled(bool enable){
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    #elif PLATFORM_IOS
    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon setAdvertiserTrackingEnabled:enable];
    #endif
}

bool UCommonInterface::GetAdvertiserTrackingEnabled(){
	bool result = false;
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    #elif PLATFORM_IOS
    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    result = [unrealCommon getAdvertiserTrackingEnabled];
    #endif

    return result;
}


#if PLATFORM_ANDROID && USE_ANDROID_JNI
#elif PLATFORM_IOS
@implementation BidmadCommonInterface
+(BidmadCommonInterface *) getSharedInstance {
    static BidmadCommonInterface *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance  = [[[self class] alloc] init];
    });

    return sharedInstance;
}

-(id)init{
    self = [super init];
    return self;
}

- (UnrealCommon *) getCommon {
    UnrealCommon* common = [UnrealCommon sharedInstance];
    [common setDelegate:self];

    return common;
}

- (void)BIDMADAdTrackingAuthorizationResponse:(int)response{
    EBidmadTrackingAuthorizationStatus status;
    switch(response){
        case (uint8)EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusNotDetermined :
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusNotDetermined;
        break;
        case (uint8)EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusRestricted :
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusRestricted;
        break;
        case (uint8)EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusDenied :
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusDenied;
        break;
        case (uint8)EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusAuthorized :
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusAuthorized;
        break;
        case (uint8)EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusLessThaniOS14 :
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusLessThaniOS14;
        break;
        default:
            status = EBidmadTrackingAuthorizationStatus::BidmadAuthorizationStatusDenied;
        break;
    }

    for (TObjectIterator<UCommonInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnAdTrackingAuthorizationResponseDynamic.Broadcast(status);
        }
    }
}
@end

#endif


