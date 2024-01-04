#include "GoogleGdprConsentInterface.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(FBidmadGoogleGDPR);

UGoogleGdprConsentInterface* UGoogleGdprConsentInterface::mGoogleGdprConsentInterface;

UGoogleGdprConsentInterface::UGoogleGdprConsentInterface()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UGoogleGdprConsentInterface::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


// Called every frame
void UGoogleGdprConsentInterface::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UGoogleGdprConsentInterface::GetInstance(){
    #if PLATFORM_ANDROID
    mEnv = FAndroidApplication::GetJavaEnv();
    mJCls = FAndroidApplication::FindJavaClass("com/adop/sdk/userinfo/consent/GoogleGDPRConsent");
    jmethodID jniM = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Landroid/app/Activity;)Lcom/adop/sdk/userinfo/consent/GoogleGDPRConsent;", false);
    mJObj = mEnv->CallStaticObjectMethod(mJCls, jniM, FAndroidApplication::GetGameActivityThis());
    #elif PLATFORM_IOS

    [BidmadGdprConsentInterface getSharedInstance];

    #endif
}

void UGoogleGdprConsentInterface::SetDebug(FString testDeviceId, bool isEEA){
    GetInstance();
    #if PLATFORM_ANDROID
    jstring _testDeviceId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*testDeviceId));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setDebug", "(Ljava/lang/String;Z)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _testDeviceId, isEEA);
    mEnv->DeleteLocalRef(_testDeviceId);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] setDebug: [NSString stringWithUTF8String:TCHAR_TO_ANSI(*testDeviceId)] isEEA: isEEA];

    #endif
}

bool UGoogleGdprConsentInterface::IsConsentFormAvailable(){
    bool result = false;

    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "isConsentFormAvailable", "()Z", false);
    result = FJavaWrapper::CallBooleanMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    result = [[BidmadGdprConsentInterface getSharedInstance] isConsentFormAvailable];

    #endif

    return result;
}

int UGoogleGdprConsentInterface::GetConsentStatus(){
    int result = 0;

    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "getConsentStatus", "()I", false);
    result = FJavaWrapper::CallIntMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    result = [[BidmadGdprConsentInterface getSharedInstance] getConsentStatus];

    #endif

    return result;
}

void UGoogleGdprConsentInterface::Reset(){
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "reset", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] reset];

    #endif
}

void UGoogleGdprConsentInterface::RequestConsentInfoUpdate(){
    GetInstance();

    mGoogleGdprConsentInterface = this;

    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "requestConsentInfoUpdate", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] requestConsentInfoUpdate];

    #endif
}

void UGoogleGdprConsentInterface::LoadForm(){
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "loadForm", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] loadForm];

    #endif
}

void UGoogleGdprConsentInterface::ShowForm(){
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "showForm", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] showForm];

    #endif
}

void UGoogleGdprConsentInterface::SetListener(){
    GetInstance();
    #if PLATFORM_ANDROID
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setListenerForCpp", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
    DeleteRefMember();
    #elif PLATFORM_IOS

    [[BidmadGdprConsentInterface getSharedInstance] setListener];
    [[BidmadGdprConsentInterface getSharedInstance] setDelegate];

    #endif
}

#if PLATFORM_ANDROID
void UGoogleGdprConsentInterface::DeleteRefMember(){
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteLocalRef(mJCls);
}
#endif

#if PLATFORM_ANDROID
extern "C"{
    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateSuccessCb(JNIEnv *env, jobject obj){
        UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateSuccessCb #####"));
        if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
            UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentInfoUpdateSuccess.Broadcast();
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateFailureCb(JNIEnv *env, jobject obj, jstring errorMsg){
        UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentInfoUpdateFailureCb #####"));
        const char *msg = env->GetStringUTFChars(errorMsg, NULL);
        FString fMsg = FString(msg);
        env->ReleaseStringUTFChars(errorMsg, msg);

        if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
            UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentInfoUpdateFailure.Broadcast(fMsg);
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadSuccessCb(JNIEnv *env, jobject obj){
        UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadSuccessCb #####"));
        if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
            UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormLoadSuccess.Broadcast();
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadFailureCb(JNIEnv *env, jobject obj, jstring errorMsg){
        UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormLoadFailureCb #####"));
        const char *msg = env->GetStringUTFChars(errorMsg, NULL);
        FString fMsg = FString(msg);
        env->ReleaseStringUTFChars(errorMsg, msg);

        if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
            UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormLoadFailure.Broadcast(fMsg);
        }
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormDismissedCb(JNIEnv *env, jobject obj, jstring errorMsg){
        UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] Java_com_adop_sdk_userinfo_consent_GoogleGDPRConsent_onConsentFormDismissedCb #####"));
        const char *msg = env->GetStringUTFChars(errorMsg, NULL);
        FString fMsg = FString(msg);
        env->ReleaseStringUTFChars(errorMsg, msg);

        if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
            UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormDismissed.Broadcast(fMsg);
        }
    }
}
#elif PLATFORM_IOS

@implementation BidmadGdprConsentInterface
+(BidmadGdprConsentInterface *) getSharedInstance {
    static BidmadGdprConsentInterface *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance  = [[[self class] alloc] init];
    });

    return sharedInstance;
}

-(id)init{
    self = [super init];
    [UnrealGDPRforGoogle sharedInstance];
    return self;
}

-(void)setDelegate{
    [[UnrealGDPRforGoogle sharedInstance] setDelegate: self];
}

-(void)setListener{
    [[UnrealGDPRforGoogle sharedInstance] setListener];
}

-(void)setDebug:(NSString*)testDeviceId isEEA:(BOOL)isTestEurope{
    [[UnrealGDPRforGoogle sharedInstance] setDebug:testDeviceId isTestEurope:isTestEurope];
}

-(bool)isConsentFormAvailable{
    return [[UnrealGDPRforGoogle sharedInstance] isConsentFormAvailable] == YES ? true : false;
}

-(int)getConsentStatus{
    int result = [[[UnrealGDPRforGoogle sharedInstance] getConsentStatus] intValue];
    return result;
}

-(void)reset{
    [[UnrealGDPRforGoogle sharedInstance] reset];
}

-(void)requestConsentInfoUpdate{
    [[UnrealGDPRforGoogle sharedInstance] requestConsentInfoUpdate];
}

-(void)loadForm{
    [[UnrealGDPRforGoogle sharedInstance] loadForm];
}

-(void)showForm{
    [[UnrealGDPRforGoogle sharedInstance] showForm];
}

//Bidmad Callback

- (void)onConsentFormDismissed:(NSError *)formError {
    UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] onConsentFormDismissed #####"));
    if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
        FString FormErrorDescription = UTF8_TO_TCHAR([formError.localizedDescription UTF8String]);
        UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormDismissed.Broadcast(FormErrorDescription);
    }
}

- (void)onConsentFormLoadFailure:(NSError *)formError {
    UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] onConsentFormLoadFailure #####"));
    if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
        FString FormErrorDescription = UTF8_TO_TCHAR([formError.localizedDescription UTF8String]);
        UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormLoadFailure.Broadcast(FormErrorDescription);
    }
}

- (void)onConsentFormLoadSuccess {
    UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] onConsentFormLoadSuccess #####"));
    if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
        UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentFormLoadSuccess.Broadcast();
    }
}

- (void)onConsentInfoUpdateFailure:(NSError *)formError {
    UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] onConsentInfoUpdateFailure #####"));
    if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
        FString FormErrorDescription = UTF8_TO_TCHAR([formError.localizedDescription UTF8String]);
        UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentInfoUpdateFailure.Broadcast(FormErrorDescription);
    }
}

- (void)onConsentInfoUpdateSuccess {
    UE_LOG(FBidmadGoogleGDPR, Warning, TEXT("[UGoogleGdprConsentInterface] onConsentInfoUpdateSuccess #####"));
    if(IsValid(UGoogleGdprConsentInterface::mGoogleGdprConsentInterface)){
        UGoogleGdprConsentInterface::mGoogleGdprConsentInterface->OnConsentInfoUpdateSuccess.Broadcast();
    }
}

@end

#endif


