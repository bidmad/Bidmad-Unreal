// Fill out your copyright notice in the Description page of Project Settings.


#include "InterstitialInterface.h"

UInterstitialInterface::UInterstitialInterface()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UInterstitialInterface::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


// Called every frame
void UInterstitialInterface::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UInterstitialInterface::InitInterstitial(FString androidZoneId, FString iosZoneId){
    #if PLATFORM_ANDROID
    checkf(!androidZoneId.IsEmpty(), TEXT("[UInterstitialInterface::InitInterstitial] ZoneId is Empty #####"));
    #elif PLATFORM_IOS
    checkf(!iosZoneId.IsEmpty(), TEXT("[UInterstitialInterface::InitInterstitial] ZoneId is Empty #####"));
    #else
    if(androidZoneId.IsEmpty() || androidZoneId.IsEmpty()){
        UE_LOG(FBidmadPlugin, Error, TEXT("[UInterstitialInterface::InitInterstitial] ZoneId is Empty #####"));
    }
    #endif

    #if PLATFORM_ANDROID
    mZoneId = androidZoneId;
    #else //PLATFORM_IOS 
    mZoneId = iosZoneId;
    #endif

    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    GetInstance();
    SetActivity();//Android JNI Start
    MakeInterstitial();
    #elif PLATFORM_IOS
    NewiOSInstance();
    #endif
    
    SetAdInfo(); //AOS&iOS
    
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    DeleteRefMember(); //Android JNI END
    #endif 
}

void UInterstitialInterface::NewiOSInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    #elif PLATFORM_IOS
    unrealInterstitial = [[BidmadInterstitialInterface getSharedInstance] newInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

void UInterstitialInterface::GetInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/interstitial/UnrealInterstitial");
    
    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lcom/adop/sdk/interstitial/UnrealInterstitial;", false);

    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _zoneId);
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    unrealInterstitial = [[BidmadInterstitialInterface getSharedInstance] getInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

//Only Android Funtion START
#if PLATFORM_ANDROID && USE_ANDROID_JNI
void UInterstitialInterface::SetActivity() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setActivity", "(Landroid/app/Activity;)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, FAndroidApplication::GetGameActivityThis());
}

void UInterstitialInterface::MakeInterstitial() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "makeInterstitial", "()V", false);
    mEnv->CallVoidMethod(mJObj, midGet);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
}

void UInterstitialInterface::DeleteRefMember(){
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteGlobalRef(mJCls);
}
#endif
//Only Android Funtion END

void UInterstitialInterface::SetAdInfo() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setAdInfo", "(Ljava/lang/String;)V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _zoneId);
    
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    [unrealInterstitial setZoneID:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

void UInterstitialInterface::Load() {
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    [unrealInterstitial load];
    #endif
}

void UInterstitialInterface::Show() {
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    
    UE_LOG(LogTemp, Warning, TEXT("Interstitial Ad Show!!!!!! #####"));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "show", "()V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    
    #elif PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(), ^{
        [unrealInterstitial show];
    });
    #endif
}

bool UInterstitialInterface::IsLoaded() {
    bool result = false;
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    
    UE_LOG(LogTemp, Warning, TEXT("Interstitial Ad IsLoaded!!!!!! #####"));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "isLoaded", "()Z", false);
    result = FJavaWrapper::CallBooleanMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    result = [unrealInterstitial isLoaded];
    #endif

    return result;
}


#if PLATFORM_ANDROID && USE_ANDROID_JNI
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onLoadAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnLoadBidmadInterstitialAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnShowBidmadInterstitialAd.Broadcast(zoneId);
                Itr->Load(); //Ad Reload
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onFailedAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnFailedBidmadInterstitialAd.Broadcast(zoneId);
            }
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                Itr->OnCloseBidmadInterstitialAd.Broadcast(zoneId);
            }
        }
    }
}
#elif PLATFORM_IOS
@implementation BidmadInterstitialInterface
+(BidmadInterstitialInterface *) getSharedInstance {
    static BidmadInterstitialInterface *sharedInstance = nil;
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
- (UnrealInterstitial *)newInstance:(NSString *)zoneID {
    UnrealInterstitial * interstitial = [[UnrealInterstitial alloc] initWithZoneId:zoneID];
    [interstitial setDelegate:self];
    return interstitial;
}
- (UnrealInterstitial *)getInstance:(NSString *)zoneID {
    UnrealInterstitial * interstitial = [UnrealInterstitial getInstance:zoneID];
    return interstitial;
}

- (void)BIDMADInterstitialClose:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;

    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnCloseBidmadInterstitialAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADInterstitialShow:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;
    
    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnShowBidmadInterstitialAd.Broadcast(nsZoneId);
            Itr->InitInterstitial(nil, nsZoneId);
            Itr->Load(); //Ad Reload
        }
    }
}
-(void)BIDMADInterstitialLoad:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;

    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnLoadBidmadInterstitialAd.Broadcast(nsZoneId);
        }
    }
}
- (void)BIDMADInterstitialAllFail:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;

    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            Itr->OnFailedBidmadInterstitialAd.Broadcast(nsZoneId);
        }
    }
}
@end

#endif
