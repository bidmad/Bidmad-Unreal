#include "RewardInterface.h"

DEFINE_LOG_CATEGORY(FBidmadReward);

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
    
    SetAdInfo(); //AOS&iOS
    
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
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("ad/helper/openbidding/reward/UnrealReward");

    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lad/helper/openbidding/reward/UnrealReward;", false);

    jstring _mId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _mId);
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
    mEnv->DeleteGlobalRef(mJCls);
}
#endif
//Only Android Funtion END

void URewardInterface::SetAdInfo() {
#if PLATFORM_ANDROID
    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setAdInfo", "(Ljava/lang/String;)V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _zoneId);
    
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    [unrealReward setZoneID:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

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
    mOnLoadDelegate = OnLoad;
}

void URewardInterface::BindEventToOnShow(const FOnBidmadRewardShowDelegate& OnShow) {
    mOnShowDelegate = OnShow;
}

void URewardInterface::BindEventToOnFail(const FOnBidmadRewardFailDelegate& OnFail) {
    mOnFailDelegate = OnFail;
}

void URewardInterface::BindEventToOnComplete(const FOnBidmadRewardCompleteDelegate& OnComplete) {
    mOnCompleteDelegate = OnComplete;
}

void URewardInterface::BindEventToOnClose(const FOnBidmadRewardCloseDelegate& OnClose) {
    mOnCloseDelegate = OnClose;
}

void URewardInterface::BindEventToOnSkip(const FOnBidmadRewardSkipDelegate& OnSkip) {
    mOnSkipDelegate = OnSkip;
}

bool URewardInterface::CheckMyId(const FString& getId){
    bool result = false;
    UE_LOG(FBidmadInterstitial, Warning, TEXT("CheckMyId!!!!!! %s #####"), &getId);
    if(!mId.IsEmpty() && !getId.IsEmpty()){
        result = (mId == getId);
    }

    UE_LOG(FBidmadInterstitial, Error, TEXT("[URewardInterface::URewardInterface] checkMyId : %d #####"), result);

    return result;
}

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onLoadAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnLoadDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onShowAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnShowDelegate.ExecuteIfBound(zoneId);
                    Itr->Load(); //Ad Reload
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onFailedAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnFailDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCompleteAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnCompleteDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onCloseAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnCloseDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_reward_UnrealReward_onSkippedAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnSkipDelegate.ExecuteIfBound(zoneId);
                }
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
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnSkipDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadRewardUESucceed:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnCompleteDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadRewardUEClose:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnCloseDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadRewardUEShow:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnShowDelegate.ExecuteIfBound(mZoneId);
                Itr->InitReward(nil, mZoneId);
                Itr->Load(); //Ad Reload
            }
        }
    }
}
- (void)bidmadRewardUELoad:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    UE_LOG(FBidmadReward, Display, TEXT("[URewardInterface] BIDMADReward Load #####"));
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnLoadDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadRewardUEAllFail:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    UE_LOG(FBidmadReward, Display, TEXT("[URewardInterface] BIDMADReward Load Fail #####"));
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnFailDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}

@end
#endif
