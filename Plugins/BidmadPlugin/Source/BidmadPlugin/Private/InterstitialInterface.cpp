// Fill out your copyright notice in the Description page of Project Settings.


#include "InterstitialInterface.h"

TMap <FString, FInterstitialInterface*> FInterstitialInterface::mInterstitialInterfaceMap = TMap <FString, FInterstitialInterface*> ();

FInterstitialInterface::FInterstitialInterface(FString zoneId)
{
    #if PLATFORM_ANDROID || PLATFORM_IOS
    checkf(!zoneId.IsEmpty(), TEXT("[FInterstitialInterface::FInterstitialInterface] ZoneId is Empty #####"));
    #else
    if(zoneId.IsEmpty()){
        UE_LOG(FBidmadPlugin, Error, TEXT("[FInterstitialInterface::FInterstitialInterface] ZoneId is Empty #####"));
    }
    #endif

    mZoneId = zoneId;
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    SetActivity();//Android JNI Start
    MakeInterstitial();
    #endif
    
    SetAdInfo(); //AOS&iOS
    
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    DeleteRefMember(); //Android JNI END
    #endif
}


void FInterstitialInterface::GetInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/interstitial/UnrealInterstitial");
    
    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lcom/adop/sdk/interstitial/UnrealInterstitial;", false);

    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _zoneId);
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    unrealInterstitial = [[BidmadInterstitialInterface getSharedInstance] getInterstitialByZone:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

//Only Android Funtion START
#if PLATFORM_ANDROID && USE_ANDROID_JNI
void FInterstitialInterface::SetActivity() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setActivity", "(Landroid/app/Activity;)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, FAndroidApplication::GetGameActivityThis());
}

void FInterstitialInterface::MakeInterstitial() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "makeInterstitial", "()V", false);
    mEnv->CallVoidMethod(mJObj, midGet);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
}

void FInterstitialInterface::DeleteRefMember(){
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteGlobalRef(mJCls);
}
#endif
//Only Android Funtion END

void FInterstitialInterface::SetAdInfo() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setAdInfo", "(Ljava/lang/String;)V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _zoneId);
    
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    [unrealInterstitial setZoneID:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

void FInterstitialInterface::Load() {
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    if([unrealInterstitial isShowing]){
        UE_LOG(LogTemp,Display, TEXT("[FInterstitialInterface] Current Zone Is Showing() #####"));
        [[BidmadInterstitialInterface getSharedInstance] loadSameZone:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    }else{
        UE_LOG(LogTemp,Display, TEXT("[FInterstitialInterface] Current Zone Is Not Showing() #####"));
        [unrealInterstitial load];
    }
    #endif
}

void FInterstitialInterface::Show() {
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

bool FInterstitialInterface::IsLoaded() {
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

        FInterstitialCallback::OnLoadAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onShowAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FInterstitialCallback::OnShowAd.Broadcast(zoneId);

        //Ad ReLoad
        FInterstitialInterface ii = FInterstitialInterface(zoneId);
        ii.Load();
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onFailedAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FInterstitialCallback::OnFailedAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_interstitial_UnrealInterstitial_onCloseAdCb(JNIEnv *env, jobject obj, jstring str){
        
        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FInterstitialCallback::OnCloseAd.Broadcast(zoneId);
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
    if(self = [super init]){
        NSLog(@"BidmadRewardInterface init");
        interstitialList = [[NSMutableDictionary alloc] init];
        tempInterstitial = nil;
    }
    return self;
}

- (UnrealReward *)getInterstitialByZone:(NSString *)zoneID {
    if([interstitialList objectForKey:zoneID] == nil){
        NSLog(@"NewZoneID: %@ ", zoneID);
        UnrealInterstitial * interstitial = [[UnrealInterstitial alloc] init];
        [interstitial setDelegate:self];
        [interstitialList setObject:interstitial forKey:zoneID];
    }
    return [interstitialList objectForKey:zoneID];
}
- (void) loadSameZone:(NSString *)zoneId{
    tempInterstitial = [[UnrealInterstitial alloc] init];
    [tempInterstitial setZoneID:zoneId];
    [tempInterstitial setDelegate:self];
    [tempInterstitial setShowing:false];
    [tempInterstitial load];
}
- (void) updateInterstitialList:(NSString *) zoneId{
    UnrealInterstitial * temp = [interstitialList objectForKey:zoneId];
   
    if([temp isShowing]){
        if(tempInterstitial != nil){
            NSLog(@"[FInterstitial Same/Diff Object ");
            [tempInterstitial setShowing:false];
            [interstitialList setObject:tempInterstitial forKey:zoneId];
            tempInterstitial = nil;
        }
    }
}

- (void)BIDMADInterstitialClose:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;
    [self updateInterstitialList:nsZoneId];
    FInterstitialCallback::OnCloseAd.Broadcast(nsZoneId);
}
- (void)BIDMADInterstitialShow:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;
    FInterstitialCallback::OnShowAd.Broadcast(nsZoneId);
    
    FInterstitialInterface ii = FInterstitialInterface(nsZoneId);
    ii.Load();
}
-(void)BIDMADInterstitialLoad:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;
    FInterstitialCallback::OnLoadAd.Broadcast(nsZoneId);
}
- (void)BIDMADInterstitialAllFail:(BIDMADInterstitial *)core{
    NSString* nsZoneId = core.zoneID;
    FInterstitialCallback::OnFailedAd.Broadcast(nsZoneId);
}
@end

#endif
