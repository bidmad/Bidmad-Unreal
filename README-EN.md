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

For iOS, additional project settings are required as shown below.<br>
​*If you're looking for a guide to the privacy requirements of the Apple Store, [see here](https://github.com/bidmad/Bidmad-Unreal/wiki/Apple-privacy-survey%5BENG%5D).

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

*Add NSUserTrackingUsageDescription and SKAdNetworkItems to AdditionalPlistData for prepare in iOS 14 or higher.
```
AdditionalPlistData=
    ...
    <key>NSUserTrackingUsageDescription</key>
    <string>Write your description here</string>
    <key>SKAdNetworkItems</key>
    <array>
      <dict>
       <key>SKAdNetworkIdentifier</key>
       <string>cstr6suwn9.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>v9wttpbfk9.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>n38lu8286q.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4dzt52r2t5.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>bvpn9ufa9b.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>2u9pt9hc89.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4468km3ulz.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4fzdc2evr5.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>7ug5zh24hu.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>8s468mfl3y.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9rd848q2bz.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9t245vhmpl.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>av6w8kgt66.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>f38h382jlk.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>hs6bdukanm.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>kbd757ywx3.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ludvb6z3bs.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>m8dbw4sv7c.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>mlmmfzh3r3.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>prcb7njmu6.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>t38b2kh725.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>tl55sbb4fm.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>wzmmz9fp6w.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>yclnxrl5pm.skadnetwork</string>
      </dict>
      <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ydx93a7ass.skadnetwork</string>
      </dict>
    </array>
bGenerateXCArchive=True
```

*After completing the above tasks, the contents added to **DefaultEngine.ini** are as follows.
```
AdditionalLinkerFlags=-ObjC
AdditionalPlistData=<key>GADApplicationIdentifier</key><string>ca-app-pub-3940256099942544~1458002511</string><key>NSAppTransportSecurity</key><dict><key>NSAllowsArbitraryLoads</key><true/><key>NSAllowsArbitraryLoadsForMedia</key><true/><key>NSAllowsArbitraryLoadsInWebContent</key><true/></dict><key>NSUserTrackingUsageDescription</key><string>언리얼 테스트</string><key>SKAdNetworkItems</key><array><dict><key>SKAdNetworkIdentifier</key><string>cstr6suwn9.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>v9wttpbfk9.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>n38lu8286q.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>4dzt52r2t5.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>bvpn9ufa9b.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>2u9pt9hc89.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>4468km3ulz.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>4fzdc2evr5.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>7ug5zh24hu.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>8s468mfl3y.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>9rd848q2bz.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>9t245vhmpl.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>av6w8kgt66.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>f38h382jlk.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>hs6bdukanm.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>kbd757ywx3.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>ludvb6z3bs.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>m8dbw4sv7c.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>mlmmfzh3r3.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>prcb7njmu6.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>t38b2kh725.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>tl55sbb4fm.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>wzmmz9fp6w.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>yclnxrl5pm.skadnetwork</string></dict><dict><key>SKAdNetworkIdentifier</key><string>ydx93a7ass.skadnetwork</string></dict></array>
bGenerateXCArchive=True
```

2. In case of setting the project through xcodeprj file, set BuildSetting> Bitcode to YES.
(For Unreal Engine, default bitcode=YES)

### 3. Interstitial

The following is how to request (Load) an interstitial advertisement and show the advertisement through the plugin.<br>

#### 3.1 Init

Bidmad is issued each ZoneId for Android / iOS, and sets the issued ZoneId in the Init function according to the OS.

![InitInterstitial](./Readme_Contents/Interstitial_InitInterstitial.png)

#### 3.2 AD Load

If you have called the Init function, then the Load function is called to request an advertisement.<br>
*For iOS14 or higher, it is recommended to load after confirming that the user has consented to app tracking authorization.
You can check the load result through Callback.

![InterstitialLoad](./Readme_Contents/Interstitial_Load.png)

*After requesting Interstitial advertisement, there is a certain time delay until advertisement is loaded.<br>
In order not to expose the load delay to the view, it is recommended to request an advertisement immediately when the app starts.

#### 3.3 Ad IsLoaded

Before calling the Show function, the IsLoaded function is called to check whether the advertisement is loaded.

![InterstitialIsLoad](./Readme_Contents/Interstitial_IsLoaded.png)

#### 3.4 Ad Show

If the advertisement request is successful through the Load function, the advertisement is displayed.

![InterstitialShow](./Readme_Contents/Interstitial_Show.png)

*If the advertisement is shown, the plugin loads again.<br>
At this time, if the result of the called Load is Fail, Load is not called again.

#### 3.5 Ad Callback

Interstitial provides 4 types of Callbacks: Load / Show / Close / Failed.

![InterstitialCallbacks](./Readme_Contents/Interstitial_Callbacks.png)

### 4. Reward

The following is how to request (Load) rewarded advertisement through plugin and show (Show) advertisement.<br>

#### 4.1 Init

Bidmad is issued each ZoneId for Android / iOS, and sets the issued ZoneId in the Init function according to the OS.

![RewardInitReward](./Readme_Contents/Reward_InitReward.png)

#### 4.2 Load

If you have called the Init function, then the Load function is called to request an advertisement.<br>
*For iOS14 or higher, it is recommended to load after confirming that the user has consented to app tracking authorization.
You can check the load result through Callback.

![RewardLoad](./Readme_Contents/Reward_Load.png)

*After requesting Reward advertisement, there is a certain time delay until advertisement is loaded.<br>
In order not to expose the load delay to the view, it is recommended to request an advertisement immediately when the app starts.

#### 4.3 IsLoaded

Before calling the Show function, the IsLoaded function is called to check whether the advertisement is loaded.

![RewardIsLoaded](./Readme_Contents/Reward_IsLoaded.png)

#### 4.4 Show

If the advertisement request is successful through the Load function, the advertisement is displayed.

![RewardShow](./Readme_Contents/Reward_Show.png)

*If the advertisement is shown, the plugin loads again.<br>
At this time, if the result of the called Load is Fail, Load is not called again.

#### 4.5 Ad Callback

Reward provides 6 types of Callbacks: Load / Show / Close / Failed / Complete / Skipped.

![RewardCallbacks](./Readme_Contents/Reward_Callbacks.png)

### 5. Common

Common is a component that provides functions other than advertisements such as debugging mode and iOS14 AppTrackingAuthorization function.

#### 5.1 SetDebugging

Debugging log is output when calling SetDebugging True.

![CommonSetDebugging](./Readme_Contents/Common_SetDebugging.png)

#### 5.2 ReqAdTrackingAuthorization

In iOS 14, the app tracking transparency consent popup is exposed, and the resulting callback is provided.

![CommonReqAdTrackingAuthorization](./Readme_Contents/Common_ReqAdTrackingAuthorization.png)

#### 5.2 SetAdvertiserTrackingEnabled

When obtaining app tracking transparency consent through a method other than ReqAdTrackingAuthorization provided by Plugin, 
<br>pass agrees(True) and rejected(False) through SetAdvertiserTrackingEnabled.

![CommonSetAdvertiserTrackingEnabled](./Readme_Contents/Common_SetAdvertiserTrackingEnabled.png)

#### 5.2 GetAdvertiserTrackingEnabled

Check the value set through SetAdvertiserTrackingEnabled.

![CommonGetAdvertiserTrackingEnabled](./Readme_Contents/Common_GetAdvertiserTrackingEnabled.png)

#### References
- [Unreal GDPR Guide KOR](./Readme_Contents/Unreal_GDPR_Guide_[KOR].md)
- [Unreal GDPR Guide ENG](./Readme_Contents/Unreal_GDPR_Guide_[ENG].md)
