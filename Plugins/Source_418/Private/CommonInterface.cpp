#include "CommonInterface.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(FBidmadCommon);

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
    #if PLATFORM_ANDROID
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    
    jclass mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/BidmadCommon");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "setDebugging", "(Z)V", false);
    mEnv->CallStaticVoidMethod(mJCls, jniM, isDebugMod);

    mEnv->DeleteLocalRef(mJCls);
    #elif PLATFORM_IOS
    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon setDebugMode:isDebugMod];
    #endif
}

void UCommonInterface::ReqAdTrackingAuthorization(){
    #if PLATFORM_ANDROID

    #elif PLATFORM_IOS

    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon reqAdTrackingAuthorization];

    #endif
}

void UCommonInterface::SetAdvertiserTrackingEnabled(bool enable){
    #if PLATFORM_ANDROID

    #elif PLATFORM_IOS

    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    [unrealCommon setAdvertiserTrackingEnabled:enable];

    #endif
}

bool UCommonInterface::GetAdvertiserTrackingEnabled(){
	bool result = false;

    #if PLATFORM_ANDROID

    #elif PLATFORM_IOS

    UnrealCommon* unrealCommon = [[BidmadCommonInterface getSharedInstance] getCommon];
    result = [unrealCommon getAdvertiserTrackingEnabled];
    #endif

    return result;
}

void UCommonInterface::SetGdprConsent(bool consent, bool useArea){

    #if PLATFORM_ANDROID

    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] SetGdprConsent 1 #####"));
    jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/userinfo/consent/Consent");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/app/Activity;Z)Lcom/adop/sdk/userinfo/consent/Consent;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), useArea);
    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] SetGdprConsent 2 #####"));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setGdprConsent", "(Z)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, consent);

    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] SetGdprConsent 3 #####"));
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);
    
    #elif PLATFORM_IOS

    BidmadCommonInterface* unrealCommonInterface = [BidmadCommonInterface getSharedInstance];
    [unrealCommonInterface setUseArea: useArea];
    [unrealCommonInterface setGDPRSetting: consent];

    #endif
}

int UCommonInterface::GetGdprConsent(bool useArea){
    int result = -2;

    #if PLATFORM_ANDROID

    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    
    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] GetGdprConsent 1 #####"));
    jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/userinfo/consent/Consent");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/app/Activity;Z)Lcom/adop/sdk/userinfo/consent/Consent;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), useArea);

    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] GetGdprConsent 2 #####"));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "getGdprConsentForOtherPlatform", "()I", false);
    result = FJavaWrapper::CallIntMethod(mEnv, mJObj, midGet);

    UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] GetGdprConsent 3 #####"));
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);

    #elif PLATFORM_IOS

    BidmadCommonInterface* unrealCommonInterface = [BidmadCommonInterface getSharedInstance];
    result = [unrealCommonInterface getGDPRSetting];

    #endif

    return result;
}


#if PLATFORM_ANDROID
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

- (void)setUseArea:(bool) useArea {
    [BIDMADGDPR setUseArea: useArea == true ? YES : NO];
}

- (void)setGDPRSetting:(bool) consent {
    [BIDMADGDPR setGDPRSetting: consent == true ? YES : NO];
}

- (int)getGDPRSetting {
    return [BIDMADGDPR getGDPRSetting];
}

@end

#endif


