
// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardInterface.h"


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
        UE_LOG(FBidmadPlugin, Error, TEXT("[URewardInterface::InitReward] ZoneId is Empty #####"));
    }
    #endif

    #if PLATFORM_ANDROID
    mZoneId = androidZoneId;
    #else //PLATFORM_IOS 
    mZoneId = iosZoneId;
    #endif

    //Android JNI Start
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    GetInstance(); 
    SetActivity();
    MakeReward();
    #elif PLATFORM_IOS
    NewiOSInstance();
    #endif
    
    SetAdInfo(); //AOS&iOS
    
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    DeleteRefMember(); //Android JNI END
    #endif
}

void URewardInterface::NewiOSInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    #elif PLATFORM_IOS
    unrealReward = [[BidmadRewardInterface getSharedInstance] newInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

void URewardInterface::GetInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/reward/UnrealReward");

    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lcom/adop/sdk/reward/UnrealReward;", false);

    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _zoneId);
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    unrealReward = [[BidmadRewardInterface getSharedInstance] getInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}
//Only Android Funtion START
#if PLATFORM_ANDROID && USE_ANDROID_JNI
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
#if PLATFORM_ANDROID && USE_ANDROID_JNI
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
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    [unrealReward load];
    #endif
}

void URewardInterface::Show() {
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
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
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
   
    
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "isLoaded", "()Z", false);
    result = FJavaWrapper::CallBooleanMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    result = [unrealReward isLoaded];
    #endif

    return result;
}

#if PLATFORM_ANDROID && USE_ANDROID_JNI
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onLoadAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnLoadBidmadRewardAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onShowAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnShowBidmadRewardAd.Broadcast(zoneId);
                Itr->Load(); //Ad Reload
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onFailedAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnFailedBidmadRewardAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCompleteAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnCompleteBidmadRewardAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCloseAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnCloseBidmadRewardAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onSkippedAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnSkippedBidmadRewardAd.Broadcast(zoneId);
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
- (UnrealReward *)newInstance:(NSString *)zoneID {
    UnrealReward * unrealReward = [[UnrealReward alloc] initWithZoneId:zoneID];
    [unrealReward setDelegate:self];
    return unrealReward;
}
- (UnrealReward *)getInstance:(NSString *)zoneID {
    UnrealReward * unrealReward = [UnrealReward getInstance:zoneID];
    return unrealReward;
}
- (void)BIDMADRewardSkipped:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnSkippedBidmadRewardAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADRewardVideoSucceed:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnCompleteBidmadRewardAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADRewardVideoClose:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnCloseBidmadRewardAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADRewardVideoShow:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnShowBidmadRewardAd.Broadcast(nsZoneId);
            Itr->InitReward(nil, nsZoneId);
            Itr->Load(); //Ad Reload
        }
    }
}
- (void)BIDMADRewardVideoLoad:(BIDMADRewardVideo *)core{
    NSString* nsZoneId = core.zoneID;
    UE_LOG(LogTemp,Display, TEXT("[URewardInterface] BIDMADRewardVideoLoad() #####"));
        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnLoadBidmadRewardAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADRewardVideoAllFail:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    UE_LOG(LogTemp,Display, TEXT("[URewardInterface] BIDMADRewardVideoLoad() #####"));
        for (TObjectIterator<URewardInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnFailedBidmadRewardAd.Broadcast(nsZoneId);
        }
    }
}

@end
#endif
