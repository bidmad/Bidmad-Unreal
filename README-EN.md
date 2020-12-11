# BidmadPlugin

BidmadPlugin is a plugin for using Bidmad, a mobile app advertisement SDK, in Unreal.<br>
You can use the plugin to serve interstitial/rewarded ads in Unreal mobile apps.<br>

- [Download the latest version and sample project](https://github.com/bidmad/Bidmad-Unreal/archive/master.zip)

## Get started
### 1. Requirements 

|OS|Version|Note|
|---|---|---|
|Android|TargetSDK 29 / MinSDK 19|TargetSDK will change according to Google policy.<br>("[Google Play's target API level requirement](https://developer.android.com/distribute/best-practices/develop/target-sdk?hl=en)") |
|iOS|Target10.0||

### 2. Plugin addition and setting
Copy the folder and file of **Plugins/BidmadPlugin** included in the downloaded sample project to the Plugins folder of the project to which the plugin will be applied.<br>
And, add BidmadPlugin to PublicDependencyModuleNames.AddRange declared in the **Source/Project.Build.cs** file in the project.

```
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "BidmadPlugin" });
```

#### 2.1 iOS settings

For iOS, additional project settings are required as shown below.
​
1. Add the following project settings to the **DefaultEngine.ini** file.

```
AdditionalLinkerFlags=-ObjC
AdditionalPlistData=
    <key>GADApplicationIdentifier</key>
    <string>ca-app-pub-XXXX~XXXX</string>
    <key>NSAppTransportSecurity</key>
    <dict>
    <key>NSAllowsArbitraryLoads</key><true/>
    <key>NSAllowsArbitraryLoadsForMedia</key><true/>
    <key>NSAllowsArbitraryLoadsInWebContent</key><true/>
    </dict>
bGenerateXCArchive=True
```

Among the above setting values, change <string>ca-app-pub-XXXX~XXXX</string> to the GADApplicationIdentifier of the account running the advertisement.<br>
The GADApplicationIdentifier value is the ID of the app registered in your Google Admob account, which can be found in the Admob Dashboard.

2. In case of setting the project through xcodeprj file, set BuildSetting> Bitcode to YES.
(For Unreal Engine, default bitcode=YES)

### 3. How to use Plugin

The method of requesting and showing advertisement through plugin is as follows.<br>
(*Please refer to item 4 for details on the function.)

#### 3.1 AD Load

How to load an ad is simple.<br>
Call NewInstance and Load Function provided by Plugin in order.<br><br>

You can check the result of calling Load through Callback.

![UnrealADLoad](./Readme_Contents/UnrealADLoad.png)

*After requesting Reward / Interstitial advertisement, there is a certain time delay until advertisement is loaded.<br>
In order not to expose the load delay to the view, it is recommended to request an advertisement immediately when the app starts.

#### 3.2 Ad Show

Plugin provides IsLoaded Function that can check whether advertisement is loaded.<br>
After calling IsLoaded to confirm that the ad has been loaded, and calling Show, the ad is exposed.

![UnrealADShow](./Readme_Contents/UnrealADShow.png)

*If the advertisement is shown, the plugin loads again.<br>
At this time, if the result of the called Load is Fail, Load is not called again.

#### 3.3 Ad Callback

Plugin provides callback function according to advertisement event.<br>
If you need to process after an event related to advertisement such as Load / Show / Fail, register and use the Callback function.<br>
(*Please refer to the 5th section for details.)

```cpp
#include "RewardCallback.h"
....
ABidmadPluginSampleGameMode::ABidmadPluginSampleGameMode(){
    if(FBidmadPluginModule::isBidmadModuleStart){
        FRewardCallback::OnLoadAd.AddUObject(this, &ABidmadPluginSampleGameMode::OnRewardLoadAd);
        FRewardCallback::OnFailedAd.AddUObject(this, &ABidmadPluginSampleGameMode::OnRewardFailedAd);
        ...
    }
}

void ABidmadPluginSampleGameMode::OnRewardLoadAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardLoadAd] #####"));
}
void ABidmadPluginSampleGameMode::OnRewardFailedAd(const FString& zoneId){
    UE_LOG(LogTemp, Warning, TEXT("[OnRewardFailedAd] #####"));
}
...
```

### 4. Plugin Function

BidmadPlugin provides BluePrintFunction for Interstitial / Reward ad types.

#### 4.1 NewInstance

Creates a new instance based on the ZoneId.<br>
There is only 1 Instance for the same ZoneId.

```cpp
UFUNCTION(BlueprintCallable,Category="BidmadReward")
static void NewRewardInstance(FString zoneId);

UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
static void NewInterstitialInstance(FString zoneId);
```

#### 4.2 Load

Request an advertisement through Instance created with NewInstance.

```cpp
UFUNCTION(BlueprintCallable,Category="BidmadReward")
static void LoadReward(FString zoneId);

UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
static void LoadInterstitial(FString zoneId);
```

#### 4.3 IsLoaded

This is a function to check whether the advertisement has been normally received after the Instance has performed Load. If the Instance has received an advertisement, it returns true.

```cpp
UFUNCTION(BlueprintCallable,Category="BidmadReward")
static bool IsLoadedReward(FString zoneId);

UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
static bool IsLoadedInterstitial(FString zoneId);
```

#### 4.4 Show

If the Instance has requested/received an advertisement through Load, the received advertisement is exposed.<br>
After performing the show, the plugin loads the advertisement again.
Show를 수행 후 Plugin에서 광고를 다시 Load 합니다.

```cpp
UFUNCTION(BlueprintCallable,Category="BidmadReward")
static void ShowReward(FString zoneId);

UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
static void ShowInterstitial(FString zoneId);
```

#### 4.5 DeleteInstance

Use when you need to deallocate an instance created with NewInstance.<br>
NewInstance must be called again to call Load, IsLoaded, and Show after calling DeleteInstance.

```cpp
UFUNCTION(BlueprintCallable,Category="BidmadReward")
static void DeleteRewardInstance(FString zoneId);

UFUNCTION(BlueprintCallable,Category="BidmadInterstitial")
static void DeleteInstanceInterstitial(FString zoneId);
```

### 5. Callback Delegate

BidmadPlugin notifies the occurrence of an ad-related event to a callback function through a callback delegate.<br>
If processing according to the occurrence of an event is required, it must be processed according to each event.

#### 5.1 Reward

```cpp
//FRewardCallback
static FOnLoadAd OnLoadAd; //Occurs when advertisement is normally received after performing advertisement load.
static FOnShowAd OnShowAd; //Occurs when performing an advertisement show.
static FOnFailedAd OnFailedAd; //Occurs when advertisement is not received after performing advertisement load
static FOnCompleteAd OnCompleteAd; //Occurs when the reward payment standard is achieved in reward advertisement.
static FOnCloseAd OnCloseAd; //Occurs when the advertisement is closed.
static FOnClickAd OnClickAd; //Occurs when an advertisement is clicked.
static FOnSkippedAd OnSkippedAd; //Occurs when the Reward payment standard is not achieved and the advertisement ends in a reward advertisement.
```

#### 5.2 Interstitial

```cpp
//FInterstitialCallback
static FOnLoadAd OnLoadAd; //Occurs when advertisement is normally received after performing advertisement load.
static FOnShowAd OnShowAd; //Occurs when performing an advertisement show.
static FOnFailedAd OnFailedAd; //Occurs when advertisement is not received after performing advertisement load.
static FOnCloseAd OnCloseAd; //Occurs when the advertisement is closed.
```
