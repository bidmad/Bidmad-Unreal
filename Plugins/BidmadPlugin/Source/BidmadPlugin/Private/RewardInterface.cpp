
// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardInterface.h"

TMap <FString, FRewardInterface*> FRewardInterface::mRewardInterfaceMap = TMap <FString, FRewardInterface*> ();

FRewardInterface::FRewardInterface(FString zoneId)
{
    #if PLATFORM_ANDROID || PLATFORM_IOS
    checkf(!zoneId.IsEmpty(), TEXT("[FRewardInterface::FRewardInterface] ZoneId is Empty #####"));
    #else
    if(zoneId.IsEmpty()){
        UE_LOG(FBidmadPlugin, Error, TEXT("[FRewardInterface::FRewardInterface] ZoneId is Empty #####"));
    }
    #endif

    mZoneId = zoneId;
    GetInstance(); //Android JNI Start
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    SetActivity();
    MakeReward();
    #endif
    
    SetAdInfo(); //AOS&iOS
    
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    DeleteRefMember(); //Android JNI END
    #endif
}


void FRewardInterface::GetInstance() {
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    mEnv = FAndroidApplication::GetJavaEnv();
    
    mJCls = FAndroidApplication::FindJavaClassGlobalRef("com/adop/sdk/reward/UnrealReward");

    jmethodID midGet = FJavaWrapper::FindStaticMethod(mEnv, mJCls, "getInstance", "(Ljava/lang/String;)Lcom/adop/sdk/reward/UnrealReward;", false);

    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    mJObj = mEnv->CallStaticObjectMethod(mJCls, midGet, _zoneId);
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    unrealReward = [[BidmadRewardInterface getSharedInstance] getRewardVideoByZone:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}
//Only Android Funtion START
#if PLATFORM_ANDROID && USE_ANDROID_JNI
void FRewardInterface::SetActivity() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setActivity", "(Landroid/app/Activity;)V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, FAndroidApplication::GetGameActivityThis());
}

void FRewardInterface::MakeReward() {
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "makeReward", "()V", false);
    mEnv->CallVoidMethod(mJObj, midGet);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);
}

void FRewardInterface::DeleteRefMember(){
    mEnv->DeleteLocalRef(mJObj);
    mEnv->DeleteGlobalRef(mJCls);
}
#endif
//Only Android Funtion END

void FRewardInterface::SetAdInfo() {
#if PLATFORM_ANDROID && USE_ANDROID_JNI
    jstring _zoneId = mEnv->NewStringUTF(TCHAR_TO_ANSI(*mZoneId));
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "setAdInfo", "(Ljava/lang/String;)V", false);

    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet, _zoneId);
    
    mEnv->DeleteLocalRef(_zoneId);
    #elif PLATFORM_IOS
    [unrealReward setZoneID:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    #endif
}

void FRewardInterface::Load() {
    GetInstance();
    #if PLATFORM_ANDROID && USE_ANDROID_JNI
    jmethodID midGet = FJavaWrapper::FindMethod(mEnv, mJCls, "load", "()V", false);
    FJavaWrapper::CallVoidMethod(mEnv, mJObj, midGet);

    DeleteRefMember();
    #elif PLATFORM_IOS
    if([unrealReward isShowing]){
        UE_LOG(LogTemp,Display, TEXT("[FRewardInterface] Current Zone Is Showing() #####"));
        [[BidmadRewardInterface getSharedInstance] loadSameZone:[NSString stringWithUTF8String: TCHAR_TO_UTF8(*mZoneId)]];
    }else{
        UE_LOG(LogTemp,Display, TEXT("[FRewardInterface] Current Zone Is Not Showing() #####"));
        [unrealReward load];
    }
    #endif
}

void FRewardInterface::Show() {
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

bool FRewardInterface::IsLoaded() {
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

        FRewardCallback::OnLoadAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onShowAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnShowAd.Broadcast(zoneId);

        FRewardInterface ri = FRewardInterface(zoneId);
        ri.Load();
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onFailedAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnFailedAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCompleteAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnCompleteAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onCloseAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnCloseAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onClickAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnClickAd.Broadcast(zoneId);
    }

    JNIEXPORT void JNICALL Java_com_adop_sdk_reward_UnrealReward_onSkippedAdCb(JNIEnv *env, jobject obj, jstring str){

        const char *zoneId = env->GetStringUTFChars(str, NULL);
        env->ReleaseStringUTFChars(str, zoneId);

        FRewardCallback::OnSkippedAd.Broadcast(zoneId);
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
    if(self = [super init]){
        NSLog(@"BidmadRewardInterface init");
        rewardList = [[NSMutableDictionary alloc] init];
        tempReward = nil;
    }

    return self;
}

- (UnrealReward *)getRewardVideoByZone:(NSString *)zoneID {
    if([rewardList objectForKey:zoneID] == nil){
        NSLog(@"NewZoneID: %@ ", zoneID);
        UnrealReward * unrealReward = [[UnrealReward alloc] init];
        [unrealReward setDelegate:self];
        [rewardList setObject:unrealReward forKey:zoneID];
    }
    return [rewardList objectForKey:zoneID];
}
- (void) loadSameZone:(NSString *)zoneId{
    tempReward = [[UnrealReward alloc] init];
    [tempReward setZoneID:zoneId];
    [tempReward setDelegate:self];
    [tempReward setShowing:false];
    [tempReward load];
}
- (void) updateRewardList:(NSString *) zoneId{
    UnrealReward * temp = [rewardList objectForKey:zoneId];
   
    if([temp isShowing]){
        if(tempReward != nil){
            NSLog(@" 새로운 객체 생성  뉴페이스 등극 ");
            [tempReward setShowing:false];
            [rewardList setObject:tempReward forKey:zoneId];
            tempReward = nil;
        }
    }
}
- (void)BIDMADRewardSkipped:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    FRewardCallback::OnSkippedAd.Broadcast([nsZoneId UTF8String]);
}
- (void)BIDMADRewardVideoSucceed:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    FRewardCallback::OnCompleteAd.Broadcast([nsZoneId UTF8String]);
}
- (void)BIDMADRewardVideoClose:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    [self updateRewardList:nsZoneId];
    
    FRewardCallback::OnCloseAd.Broadcast([nsZoneId UTF8String]);
}
- (void)BIDMADRewardVideoShow:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    FRewardCallback::OnShowAd.Broadcast([nsZoneId UTF8String]);
}
- (void)BIDMADRewardVideoLoad:(BIDMADRewardVideo *)core{
    NSString* nsZoneId = core.zoneID;
    UE_LOG(LogTemp,Display, TEXT("[FRewardInterface] BIDMADRewardVideoLoad() #####"));
    FRewardCallback::OnLoadAd.Broadcast([nsZoneId UTF8String]);
}
- (void)BIDMADRewardVideoAllFail:(BIDMADRewardVideo *)core {
    NSString* nsZoneId = core.zoneID;
    UE_LOG(LogTemp,Display, TEXT("[FRewardInterface] BIDMADRewardVideoLoad() #####"));
    FRewardCallback::OnFailedAd.Broadcast([nsZoneId UTF8String]);
}

@end
#endif
