#include "RewardInterface.h"

DEFINE_LOG_CATEGORY(FBidmadReward);

TMap <FString, URewardInterface*> URewardInterface::mRewardInterfaceMap;

URewardInterface::URewardInterface()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void URewardInterface::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


// Called every frame
void URewardInterface::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void URewardInterface::InitReward(FString androidZoneId, FString iosZoneId)
{
    #if PLATFORM_ANDROID
    checkf(!androidZoneId.IsEmpty(), TEXT("[URewardInterface::InitReward] ZoneId is Empty #####"));
    #elif PLATFORM_IOS
    checkf(!iosZoneId.IsEmpty(), TEXT("[URewardInterface::InitReward] ZoneId is Empty #####"));
    #else
    if(androidZoneId.IsEmpty() || androidZoneId.IsEmpty()){
        UE_LOG(FBidmadReward, Error, TEXT("[URewardInterface::InitReward] ZoneId is Empty #####"));
    }
    #endif

    #if PLATFORM_ANDROID
    mZoneId = androidZoneId;
    #else //PLATFORM_IOS 
    mZoneId = iosZoneId;
    #endif
    
    if(mId.IsEmpty()){
      mId = FGuid::NewGuid().ToString();  
    }

    //Android JNI Start
    #if PLATFORM_ANDROID
    GetInstance(); 
    SetActivity();
    MakeReward();
    #elif PLATFORM_IOS
    NewiOSInstance();
    #endif
    
    mRewardInterfaceMap.Add(mId, this);

    #if PLATFORM_ANDROID
    DeleteRefMember(); //Android JNI END
    #endif
}

void URewardInterface::NewiOSInstance() {
    #if PLATFORM_ANDROID
    #elif PLATFORM_IOS
    unrealReward = [[BidmadRewardInterface getSharedInstance] newInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)] uuid:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mId)]];
    #endif
}

void URewardInterface::GetInstance() {
    #if PLATFORM_ANDROID
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClass("ad/helper/openbidding/reward/UnrealReward");

    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;Ljava/lang/String;)Lad/helper/openbidding/reward/UnrealReward;", false);

    jstring _mId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mId));
    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _zoneId, _mId);

    mEnv->DeleteLocalRef(_zoneId);
    mEnv->DeleteLocalRef(_mId);
    #elif PLATFORM_IOS
    unrealReward = [[BidmadRewardInterface getSharedInstance] getInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mId)]];
    #endif
}
//Only Android Funtion START
#if PLATFORM_ANDROID
void URewardInterface::SetActivity() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setActivity", "(Landroid/app/Activity;)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, FAndroidApplication::GetGameActivityThis());
}

void URewardInterface::MakeReward() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "makeReward", "()V", false);
    mEnv->CallVoidMethod(mJObj, midGet);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
}

void URewardInterface::DeleteRefMember(){
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);
}
#endif

void URewardInterface::Load() {
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    [unrealReward load];
    #endif
}

void URewardInterface::Show() {
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "show", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        [unrealReward show];
    });
    #endif
}

bool URewardInterface::IsLoaded() {
    bool result = false;
    GetInstance();
    #if PLATFORM_ANDROID
   
    
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "isLoaded", "()Z", false);
    result = FJavaWrapper::CallBooleanMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    result = [unrealReward isLoaded];
    #endif

    return result;
}

void URewardInterface::BindEventToOnLoad(const FOnBidmadRewardLoadDelegate& OnLoad) {
    OnLoadDelegate = OnLoad;
}

void URewardInterface::BindEventToOnShow(const FOnBidmadRewardShowDelegate& OnShow) {
    OnShowDelegate = OnShow;
}

void URewardInterface::BindEventToOnFail(const FOnBidmadRewardFailDelegate& OnFail) {
    OnFailDelegate = OnFail;
}

void URewardInterface::BindEventToOnComplete(const FOnBidmadRewardCompleteDelegate& OnComplete) {
    OnCompleteDelegate = OnComplete;
}

void URewardInterface::BindEventToOnClose(const FOnBidmadRewardCloseDelegate& OnClose) {
    OnCloseDelegate = OnClose;
}

void URewardInterface::BindEventToOnSkip(const FOnBidmadRewardSkipDelegate& OnSkip) {
    OnSkipDelegate = OnSkip;
}

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onLoadAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];
            
            if(IsValid(reward)){
                reward->OnLoadDelegate.ExecuteIfBound(fZoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onShowAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];
            
            if(IsValid(reward)){
                reward->OnShowDelegate.ExecuteIfBound(fZoneId);
                reward->Load(); //Ad Reload
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onLoadFailAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2, jstring error){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);
        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);
        const char *errorInfo = env->GetStringUTFChars(error, NULL);
        FString fError = FString(errorInfo);
        env->ReleaseStringUTFChars(error, errorInfo);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];

            if(IsValid(reward)){
                reward->OnFailDelegate.ExecuteIfBound(fZoneId, fError);
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCompleteAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];
            
            if(IsValid(reward)){
                reward->OnCompleteDelegate.ExecuteIfBound(fZoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCloseAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];
            
            if(IsValid(reward)){
                reward->OnCloseDelegate.ExecuteIfBound(fZoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onSkippedAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        FString fZoneId = FString(zoneId);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        FString fUnrealId = FString(unrealId);
        env->ReleaseStringUTFChars(str2, unrealId);

        if(URewardInterface::mRewardInterfaceMap.Contains(fUnrealId)){
            URewardInterface* reward = URewardInterface::mRewardInterfaceMap[fUnrealId];
            
            if(IsValid(reward)){
                reward->OnSkipDelegate.ExecuteIfBound(fZoneId);
            }
        }
    }
}
#elif PLATFORM_IOS
@implementation BidmadRewardInterface
+(BidmadRewardInterface *) getSharedInstance {
    static BidmadRewardInterface *sharedInstance = nil;
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
- (OpenBiddingUnrealReward *)newInstance:(NSString *)zoneID uuid:(NSString *)uuid {
    OpenBiddingUnrealReward * unrealReward = [[OpenBiddingUnrealReward alloc] initWithZoneId:zoneID uuid:uuid];
    [unrealReward setDelegate:self];
    return unrealReward;
}
- (OpenBiddingUnrealReward *)getInstance:(NSString *)uuid {
    OpenBiddingUnrealReward * unrealReward = [OpenBiddingUnrealReward getInstance:uuid];
    return unrealReward;
}
- (void)bidmadRewardUESkipped:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnSkipDelegate.ExecuteIfBound(mZoneId);
        }
    }
}
- (void)bidmadRewardUESucceed:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnCompleteDelegate.ExecuteIfBound(mZoneId);
        }
    }
}
- (void)bidmadRewardUEClose:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnCloseDelegate.ExecuteIfBound(mZoneId);
        }
    }
}
- (void)bidmadRewardUEShow:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnShowDelegate.ExecuteIfBound(mZoneId);
        }
    }
}
- (void)bidmadRewardUELoad:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnLoadDelegate.ExecuteIfBound(mZoneId);
        }
    }
}
- (void)bidmadRewardUEAllFail:(NSString * _Nullable)mZoneId errorReason:(NSString * _Nullable)reason uuid:(NSString * _Nullable)uuid {
    if(URewardInterface::mRewardInterfaceMap.Contains(uuid)){
        URewardInterface* reward = URewardInterface::mRewardInterfaceMap[uuid];

        if(IsValid(reward)){
            reward->OnFailDelegate.ExecuteIfBound(mZoneId, reason);
        }
    }
}

@end
#endif
