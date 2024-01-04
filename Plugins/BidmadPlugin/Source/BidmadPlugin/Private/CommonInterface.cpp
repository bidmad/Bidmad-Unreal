#include "CommonInterface.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(FBidmadCommon);
UCommonInterface* UCommonInterface::mCommonInterface;

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

UCommonInterface* UCommonInterface::GetCommonInterfaceInstance() {
    if (IsValid(UCommonInterface::mCommonInterface) == false) {
        UCommonInterface::mCommonInterface = NewObject<UCommonInterface>();
    }
    
    return UCommonInterface::mCommonInterface;
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
    mCommonInterface = this;

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

void UCommonInterface::InitializeSdkWithCallback(FString androidAppKey, FString iosAppKey) {
    mCommonInterface = this;
    
    #if PLATFORM_IOS
    [[BIDMADSetting sharedInstance] initializeSdkWithKey:[NSString stringWithUTF8String:TCHAR_TO_UTF8(*iosAppKey)] completionHandler:^(BOOL isInitialized) {
        // Call the callback with the result
        UE_LOG(FBidmadCommon, Warning, TEXT("[UCommonInterface] initializeSdkWithKey #####"));
        if(IsValid(UCommonInterface::mCommonInterface)){
            UCommonInterface::mCommonInterface->InitializeSdkCallback.ExecuteIfBound(isInitialized);
        }
    }];
    #elif PLATFORM_ANDROID
    // Call Native Initialized Callback

    // mInitializeSdkCallback = &callback;
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    mAppKey = androidAppKey;
    jstring _appKey = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mAppKey));
    jclass mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/BidmadCommon");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "initializeSdkWithCbListener", "(Landroid/app/Activity;Ljava/lang/String;)V", false);
    mEnv->CallStaticVoidMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), _appKey);

    mEnv->DeleteLocalRef(mJCls);

    #endif
}

void UCommonInterface::BindEventToOnInitializeSdk(const FInitializeSdkCallback& OnInitializeSdk) {
    InitializeSdkCallback = OnInitializeSdk;
}

void UCommonInterface::InitializeSdk(FString androidAppKey, FString iosAppKey) {
    #if PLATFORM_ANDROID
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    mAppKey = androidAppKey;
    jstring _appKey = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mAppKey));
    jclass mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/BidmadCommon");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "initializeSdk", "(Landroid/app/Activity;Ljava/lang/String;)V", false);
    mEnv->CallStaticVoidMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), _appKey);

    mEnv->DeleteLocalRef(mJCls);

    #elif PLATFORM_IOS
    [[BIDMADSetting sharedInstance] initializeSdkWithKey:[NSString stringWithUTF8String:TCHAR_TO_UTF8(*iosAppKey)]];
    #endif
}

void UCommonInterface::SetCUID(FString id){
    #if PLATFORM_ANDROID
        JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
               // UE_LOG(FBidmadCommon, Error, TEXT("[UCommonInterface] SetCUID #####")); 
        mCUID = id; 
        jstring _cuid = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mCUID));
        jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/AdOption"); 
        jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "()Lcom/adop/sdk/AdOption;", false);
        jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM);
        jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setCuid", "(Ljava/lang/String;)V", false);
        FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _cuid);
    
        mEnv->DeleteLocalRef(mJObj);
        mEnv->DeleteLocalRef(mJCls);

    #elif PLATFORM_IOS
    [BIDMADSetting.sharedInstance setCuid:[NSString stringWithUTF8String:TCHAR_TO_UTF8(*id)]];
    #endif
}

void UCommonInterface::SetChildDirected(bool childDirected){
    #if PLATFORM_ANDROID
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/AdOption");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "()Lcom/adop/sdk/AdOption;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM);
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setChildDirected", "(Z)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, childDirected);

    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);

    #elif PLATFORM_IOS
    [[BIDMADSetting sharedInstance] setIsChildDirectedAds:childDirected];
    #endif
}

void UCommonInterface::SetGdprConsent(bool consent, bool useArea){

    #if PLATFORM_ANDROID

    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv();
    jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/userinfo/consent/Consent");    
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/app/Activity;Z)Lcom/adop/sdk/userinfo/consent/Consent;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), useArea);
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setGdprConsent", "(Z)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, consent);

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
    
    jclass mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/userinfo/consent/Consent");    
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/app/Activity;Z)Lcom/adop/sdk/userinfo/consent/Consent;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis(), useArea);

    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "getGdprConsentForOtherPlatform", "()I", false);
    result = FJavaWrapper::CallIntMethod(mEnv, mJObj, midGet);

    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);

    #elif PLATFORM_IOS

    BidmadCommonInterface* unrealCommonInterface = [BidmadCommonInterface getSharedInstance];
    result = [unrealCommonInterface getGDPRSetting];

    #endif

    return result;
}

void UCommonInterface::BindEventToOnAdFree(const FAdFreeCallback& OnAdFree) {
    mCommonInterface = this;
    AdFreeCallback = OnAdFree;
#if PLATFORM_IOS
    [BidmadAdFreeInformation setDelegate:[BidmadCommonInterface getSharedInstance]];
#elif PLATFORM_ANDROID
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv(); // Context
    jclass mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/AdFreeInformation");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/content/Context;)Lad/helper/openbidding/AdFreeInformation;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis());

    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setOnAdFreeCbListener", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);
#endif
}

bool UCommonInterface::IsAdFree() {
#if PLATFORM_IOS
    return ([BidmadAdFreeInformation status] == BidmadAdFreeInformationStatusBlocked);
#elif PLATFORM_ANDROID
    JNIEnv* mEnv = FAndroidApplication::GetJavaEnv(); // Context
    jclass mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/AdFreeInformation");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/content/Context;)Lad/helper/openbidding/AdFreeInformation;", false);
    jobject mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis());

    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "getAdFreeStatus", "()I", false);

    int result = FJavaWrapper::CallIntMethod(mEnv, mJObj, midGet);

    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);

    return (result==0)? true : false;
#else
    return false;
#endif
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

    if(IsValid(UCommonInterface::mCommonInterface)){
        UCommonInterface::mCommonInterface->OnAdTrackingAuthorizationResponse.Broadcast(status);
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

- (void)didAdFreeInformationStatusChange:(BidmadAdFreeInformationStatus)status {
    UE_LOG(FBidmadCommon, Warning, TEXT("[UCommonInterface] iOS didAdFreeInformationStatusChange #####"));
    if(IsValid(UCommonInterface::mCommonInterface)){
        UCommonInterface::mCommonInterface->AdFreeCallback.ExecuteIfBound(status == BidmadAdFreeInformationStatusBlocked);
    }
}

@end

#endif

#if PLATFORM_ANDROID
extern "C"{
    // Java call Methods
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_BidmadCommon_onInitializedCb(JNIEnv *env, jobject obj, jstring isComplete){
        UE_LOG(FBidmadCommon, Warning, TEXT("[UCommonInterface] Java_ad_helper_openbidding_BidmadCommon_onInitializedCb #####"));
        if(IsValid(UCommonInterface::mCommonInterface)) {

            const char *isCompletedStr = env->GetStringUTFChars(isComplete, NULL);

            if(std::strncmp(isCompletedStr, "true", 4) == 0) {
                UCommonInterface::mCommonInterface->InitializeSdkCallback.ExecuteIfBound(true);
            }else {
                UCommonInterface::mCommonInterface->InitializeSdkCallback.ExecuteIfBound(false);
            }
            env->ReleaseStringUTFChars(isComplete, isCompletedStr);
        }
    }
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_AdFreeInformation_onAdFreeCb(JNIEnv *env, jobject obj, jstring isAdFree){
        UE_LOG(FBidmadCommon, Warning, TEXT("[UCommonInterface] Java_ad_helper_openbidding_AdFreeInformation_onAdFreeCb #####"));
        if(IsValid(UCommonInterface::mCommonInterface)) {
            const char *isAdFreeStr = env->GetStringUTFChars(isAdFree, NULL);

            if(std::strncmp(isAdFreeStr, "true", 4) == 0) {
               UCommonInterface::mCommonInterface->AdFreeCallback.ExecuteIfBound(true);
            }else {
               UCommonInterface::mCommonInterface->AdFreeCallback.ExecuteIfBound(false);
            }

            env->ReleaseStringUTFChars(isAdFree, isAdFreeStr);
        }
    }  

}

#endif
