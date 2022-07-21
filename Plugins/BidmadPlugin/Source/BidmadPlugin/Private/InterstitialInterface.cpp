#include "InterstitialInterface.h"

DEFINE_LOG_CATEGORY(FBidmadInterstitial);

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
        UE_LOG(FBidmadInterstitial, Error, TEXT("[UInterstitialInterface::InitInterstitial] ZoneId is Empty #####"));
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

    #if PLATFORM_ANDROID
    GetInstance();
    SetActivity();//Android JNI Start
    MakeInterstitial();
    #elif PLATFORM_IOS
    NewiOSInstance();
    #endif
    
    SetAdInfo(); //AOS&iOS
    
    #if PLATFORM_ANDROID
    DeleteRefMember(); //Android JNI END
    #endif 
}

void UInterstitialInterface::NewiOSInstance() {
    #if PLATFORM_ANDROID
    #elif PLATFORM_IOS
    unrealInterstitial = [[BidmadInterstitialInterface getSharedInstance] newInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)] uuid:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mId)]];
    #endif
}

void UInterstitialInterface::GetInstance() {
    #if PLATFORM_ANDROID
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("ad/helper/openbidding/interstitial/UnrealInterstitial");
    
    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lad/helper/openbidding/interstitial/UnrealInterstitial;", false);

    jstring _mId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _mId);
    mEnv->DeleteLocalRef(_mId);
    #elif PLATFORM_IOS
    unrealInterstitial = [[BidmadInterstitialInterface getSharedInstance] getInstance:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mId)]];
    #endif
}

//Only Android Funtion START
#if PLATFORM_ANDROID
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
    #if PLATFORM_ANDROID
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
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    [unrealInterstitial load];
    #endif
}

void UInterstitialInterface::Show() {
    GetInstance();
    #if PLATFORM_ANDROID
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
    #if PLATFORM_ANDROID
    
    UE_LOG(FBidmadInterstitial, Warning, TEXT("Interstitial Ad IsLoaded!!!!!! #####"));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "isLoaded", "()Z", false);
    result = FJavaWrapper::CallBooleanMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    result = [unrealInterstitial isLoaded];
    #endif

    return result;
}

void UInterstitialInterface::BindEventToOnLoad(const FOnBidmadInterstitialLoadDelegate& OnLoad) {
    mOnLoadDelegate = OnLoad;
}

void UInterstitialInterface::BindEventToOnShow(const FOnBidmadInterstitialShowDelegate& OnShow) {
    mOnShowDelegate = OnShow;
}

void UInterstitialInterface::BindEventToOnFail(const FOnBidmadInterstitialFailDelegate& OnFail) {
    mOnFailDelegate = OnFail;
}

void UInterstitialInterface::BindEventToOnClose(const FOnBidmadInterstitialCloseDelegate& OnClose) {
    mOnCloseDelegate = OnClose;
}

bool UInterstitialInterface::CheckMyId(const FString& getId){
    bool result = false;

    if(!mId.IsEmpty() && !getId.IsEmpty()){
        result = (mId == getId);
    }

    return result;
}


#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onLoadAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnLoadDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }
        
        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
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

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onFailedAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnFailDelegate.ExecuteIfBound(zoneId);
                }
            }
        }
    }

    JNIEXPORT void JNICALL Java_ad_helper_openbidding_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *env, jobject obj, jstring str1, jstring str2){
        if(str1 == NULL || str2 == NULL){
            return;
        }

        const char *zoneId = env->GetStringUTFChars(str1, NULL);
        env->ReleaseStringUTFChars(str1, zoneId);

        const char *unrealId = env->GetStringUTFChars(str2, NULL);
        env->ReleaseStringUTFChars(str2, unrealId);

        for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
        {
            if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
            {
                if(Itr->CheckMyId(unrealId)){
                    Itr->mOnCloseDelegate.ExecuteIfBound(zoneId);
                }
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
- (OpenBiddingUnrealInterstitial *)newInstance:(NSString *)zoneID uuid:(NSString *)uuid {
    OpenBiddingUnrealInterstitial * interstitial = [[OpenBiddingUnrealInterstitial alloc] initWithZoneId:zoneID uuid:uuid];
    [interstitial setDelegate:self];
    return interstitial;
}
- (OpenBiddingUnrealInterstitial *)getInstance:(NSString *)uuid {
    OpenBiddingUnrealInterstitial * interstitial = [OpenBiddingUnrealInterstitial getInstance:uuid];
    return interstitial;
}

- (void)bidmadInterstitialUEClose:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnCloseDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadInterstitialUEShow:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnShowDelegate.ExecuteIfBound(mZoneId);
                Itr->InitInterstitial(nil, mZoneId);
                Itr->Load(); //Ad Reload
            }
        }
    }
}
- (void)bidmadInterstitialUELoad:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
    {
        if (Itr->GetWorld() != nullptr && (Itr->GetWorld()->WorldType == EWorldType::Game || Itr->GetWorld()->WorldType == EWorldType::PIE) && (!Itr->IsPendingKill()))
        {
            if(Itr->CheckMyId(uuid)){
                Itr->mOnLoadDelegate.ExecuteIfBound(mZoneId);
            }
        }
    }
}
- (void)bidmadInterstitialUEAllFail:(NSString * _Nullable)mZoneId uuid:(NSString * _Nullable)uuid {
    for (TObjectIterator<UInterstitialInterface> Itr; Itr; ++Itr)
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
