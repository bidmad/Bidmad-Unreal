# BidmadPlugin

BidmadPlugin은 모바일 앱 광고 SDK인 Bidmad를 Unreal에서 사용하기 위한 Plugin입니다.<br>
Plugin을 사용하여 Unreal 모바일 앱에서 전면 / 보상형 광고를 게재 할 수 있습니다.<br>

- [최신 버전 및 샘플 프로젝트 다운로드](https://github.com/bidmad/Bidmad-Unreal/archive/master.zip)

## 시작하기
### 1. Plugin 추가 및 설정
샘플 프로젝트에 포함된 **Plugins/BidmadPlugin**의 폴더와 파일을 Plugin을 적용할 프로젝트의 Plugins폴더로 복사합니다.<br>
그리고, 프로젝트 내 **Source/프로젝트.Build.cs**파일에 선언된 PublicDependencyModuleNames.AddRange에 BidmadPlugin을 추가합니다.

```
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "BidmadPlugin" });
```
#### 1.1 Android 설정

AOS의 경우 Admob Application ID Settings 을 위한 AndroidManifest.xml에 추가 설정이 필요합니다. <br>
*com.google.android.gms.ads.APPLICATION_ID의 value는 Admob 대시보드에서 확인 바랍니다.


1. Edit → ProjectSettings → Platform-Android → Advance APK Package → Extra Settings for <application> section 에서, 다음과 같은 값을 넣어 프로젝트 설정을 추가합니다. <br>
![Bidmad-AOS-Guide-1](https://i.imgur.com/kUhtsXg.png)<br>
```
<meta-data \n android:name="com.google.android.gms.ads.APPLICATION_ID" \n android:value="Your GAID"/>
```

#### 1.2 iOS 설정

- App Store에 애플리케이션을 제출할 때 다음 가이드를 참고하여 개인정보 보호 정책 및 설문조사를 올바르게 설정하세요: [Guide for Privacy Manifest & Privacy Survey](https://github.com/bidmad/Bidmad-iOS/wiki/Guide-for-Privacy-Manifest-&-Privacy-Survey-%5BKR%5D)

- 언리얼 플러그인 1.7.1 버전 이상 사용 시, Xcode 15.3 이상을 사용하십시오<br>

- 예제 사용 시, 예제 프로젝트 내부에 [iOS 디펜던시 다운로드 링크](https://drive.google.com/file/d/19tl6TaAbEtHAifW742FYfaBvEvmCxQ5t/view?usp=sharing)를 통해 iOS 라이브러리 따로 다운로드 및 압축 해제 이후, "IOS" 폴더를 Plugins -> BidmadPlugin -> ThirdParty 폴더 아래에 넣어주세요<br>

- 아래 설정을 진행하기 이전, Unreal Engine Build Tool 코드 수정이 필요합니다. 수정 가이드는 [Unreal Build Tool 수정 가이드](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-Build-Tool-Modification-Guide-for-iOS-Build)를 통해 확인해주세요. 수정 가이드를 진행한 이후 아래 프로젝트 세팅을 진행해주세요.<br>

- Apple Store에서 요구하는 개인정보 보호에 관한 가이드가 필요한 경우 [이곳](https://github.com/bidmad/Bidmad-Unreal/wiki/Apple-privacy-survey%5BKOR%5D)을 참고하세요.<br>

1. Settings → Project Settings → Platforms → iOS 세팅 패널 내부에서, 다음과 같이 프로젝트 설정을 추가합니다.<br>

![Bidmad-iOS-Guide-1](https://i.imgur.com/zXC4whT.png)<br>
​
2. Additional Plist Data 에 GADApplicationIdentifier, NSAppTransportSecurity, NSUserTrackingUsageDescription, SKAdNetworkItems 를 추가합니다.

![Bidmad-iOS-Guide-2](https://i.imgur.com/hYqnLJs.png)<br>

**아래 설정 값 중 <string>ca-app-pub-XXXX~XXXX</string> 을 광고를 집행하는 애드몹 계정의 iOS용 App ID 로 변경하십시오.**<br> 

<details markdown="1">
<summary><strong>클릭해서 Additional Plist Data에 추가할 GADApplicationIdentifier, NSAppTransportSecurity, NSUserTrackingUsageDescription, SKAdNetworkItems 값을 확인하세요</strong></summary>
<br>

```
<key>GADApplicationIdentifier</key>
<string>ca-app-pub-XXXX~XXXX</string>
<key>NSAppTransportSecurity</key>
<dict>
    <key>NSAllowsArbitraryLoads</key>
    <true/>
    <key>NSAllowsArbitraryLoadsForMedia</key>
    <true/>
    <key>NSAllowsArbitraryLoadsInWebContent</key>
    <true/>
</dict>
<key>NSUserTrackingUsageDescription</key>
<string>This identifier will be used to deliver personalized ads to you.</string>
<key>SKAdNetworkItems</key>
<array>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>22mmun2rn5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>238da6jt44.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>24t9a8vw3c.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>24zw6aqk47.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>252b5q8x7y.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>275upjj5gd.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>294l99pt4k.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>2fnua5tdw4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>2u9pt9hc89.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>32z4fx6l9h.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>3l6bd9hu43.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>3qcr597p9d.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>3qy4746246.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>3rd42ekr43.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>3sh42y64q3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>424m5254lk.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4468km3ulz.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>44jx6755aq.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>44n7hlldy6.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>47vhws6wlr.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>488r3q3dtq.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4dzt52r2t5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4fzdc2evr5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4mn522wn87.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4pfyvq9l8r.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>4w7y6s5ca2.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>523jb4fst2.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>52fl2v3hgk.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>54NZKQM89Y.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>54nzkqm89y.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>578prtvx9j.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>5a6flpkh64.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>5l3tpt7t6e.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>5lm9lj6jb7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>5tjdwbrq8w.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6964rsfnh4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6g9af3uyq4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6p4ks3rnbw.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6v7lgmsu45.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6xzpu9s2p8.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>6yxyv74ff7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>737z793b9f.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>74b6s63p6l.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>7953jerfzd.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>79pbpufp6p.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>7fmhfwg9en.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>7rz58n8ntl.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>7ug5zh24hu.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>84993kbrcf.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>89z7zv988g.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>8c4e2ghe7u.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>8m87ys6875.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>8r8llnkz5a.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>8s468mfl3y.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>97r2b46745.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9b89h5y424.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9g2aggbj52.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9nlqeag3gk.skadnetwork</string>
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
        <string>9vvzujtq5s.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>9yg77x724h.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>a2p9lx4jpn.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>a7xqa6mtl2.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>a8cz6cu7e5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>av6w8kgt66.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>b9bk5wbcq9.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>bmxgpxpgc.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>bvpn9ufa9b.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>bxvub5ada5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>c3frkrj4fj.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>c6k4g5qg8m.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>cg4yq2srnc.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>cj5566h2ga.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>cp8zw746q7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>cs644xg564.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>cstr6suwn9.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>dbu4b84rxf.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>dkc879ngq3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>dzg6xy7pwj.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>e5fvkxwrpn.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ecpz2srf59.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>eh6m2bh4zr.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ejvt5qm6ak.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>f38h382jlk.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>f73kdq92p3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>f7s53z58qe.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>feyaarzu9v.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>g28c52eehv.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>g2y4y55b64.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ggvn48r87g.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>glqzh8vgby.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>gta8lk7p23.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>gta9lk7p23.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>gvmwg8q7h5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>h65wbv5k3f.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>hb56zgv37p.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>hdw39hrw9y.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>hs6bdukanm.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>k674qkevps.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>k6y4y55b64.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>kbd757ywx3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>kbmxgpxpgc.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>klf5c3l5u5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>krvm3zuq6h.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>lr83yxwka7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ludvb6z3bs.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>m297p6643m.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>m5mvw97r93.skadnetwork</string>
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
        <string>mls7yz5dvl.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>mp6xlyr22a.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>mqn7fxpca7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>mtkv5xtk9e.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>n38lu8286q.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>n66cz3y3bx.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>n6fk4nfna4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>n9x2a789qt.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>nu4557a4je.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>nzq8sh4pbs.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>p78axxw29g.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ppxm28t8ap.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>prcb7njmu6.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>pu4na253f3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>pwa73g5rt2.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>pwdxu55a5a.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>qqp299437r.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>qu637u8glc.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>qwpu75vrh2.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>r26jy69rpl.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>r45fhb6rf7.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>rvh3l7un93.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>rx5hdcabgc.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>s39g8k73mm.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>s69wq72ugq.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>sczv5946wb.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>su67r6k2v3.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>t38b2kh725.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>t6d3zquu66.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>tl55sbb4fm.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>tmhh9296z4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>tvvz7th9br.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>u679fj5vs4.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>uw77j35x4d.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>v4nxqhlyqp.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>v72qych5uu.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>v79kvwwj4g.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>v9wttpbfk9.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>vcra2ehyfk.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>vutu7akeur.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>w9q455wk68.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>wg4vff78zm.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>wzmmZ9fp6w.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>wzmmz9fp6w.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>x2jnk7ly8j.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>x44k69ngh6.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>x5l83yy675.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>x8jxxk4ff5.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>x8uqf25wch.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>xy9t38ct57.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>y45688jllp.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>y5ghdn5j9k.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>yclnxrl5pm.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>ydx93a7ass.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>yrqqpx2mcb.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>z24wtl6j62.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>z4gj7hsk7h.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>zmvfpc5aq8.skadnetwork</string>
    </dict>
    <dict>
        <key>SKAdNetworkIdentifier</key>
        <string>zq492l623r.skadnetwork</string>
    </dict>
</array>
```

</details>

3. Additional Non-Shipping Linker Flags / Additional Shipping Linker Flags 에 "-ObjC" 를 아래 이미지와 같이 기입해주십시오.

![Bidmad-iOS-Guide-3](https://i.imgur.com/fPOvYUO.png)<br>

4. Support bitcode in Shipping 값을 아래 이미지와 같이 OFF 로 세팅하십시오.

![Bidmad-iOS-Guide-4](https://i.imgur.com/UhdG6dG.png)<br>

### 2. Migration 가이드 (v1.5.1 이하 버전에서 v1.6.0 이상 버전으로 업데이트 하는 경우)

- CommonInterface 참조 시, 아래와 같이 Get Common Interface Instance 메서드를 먼저 호출해 CommonInterface 클래스 인스턴스를 반환 받은 이후 인터페이스를 사용하십시오.

![Bidmad-Unreal-Migration-CommonInterface-BP](https://i.imgur.com/na7D1D1.jpg)<br>

```
UCommonInterface* CommonInterface = UCommonInterface::GetCommonInterfaceInstance(); 
```

### 3. BidmadSDK 초기화 (v1.5.0 이상)

BidmadSDK 실행에 필요한 작업을 수행합니다. initializeSdk 메서드를 호출하지 않은 경우, SDK는 광고 로드를 허용하지 않습니다.<br>
initializeSdk 메서드는 ADOP Insight 에서 확인가능한 App Key를 인자값으로 받고 있습니다. App Key는 [App Key 찾기](https://github.com/bidmad/SDK/wiki/Find-your-app-key%5BKR%5D) 가이드를 참고해 가져올 수 있습니다.<br>
광고를 로드하기 전, 앱 실행 초기에 다음 예시와 같이 initializeSdk 메서드를 호출해주십시오.

![InitializeSdkUnrealWithoutCallback](https://i.imgur.com/UJhYyPv.jpg)

혹은, initializeSdkWithCallback 메서드를 호출해 SDK의 초기화 여부를 확인할 수 있습니다.

![InitializeSdkUnrealWithCallback](https://i.imgur.com/gboXzkq.jpg)

### 4. Interstitial

Plugin을 통해 전면 광고를 요청(Load)하고 광고를 노출(Show)하는 방법은 다음과 같습니다.<br>

#### 4.1 Init

Bidmad는 Android / iOS에 대한 ZoneId가 각각 발급되며, 발급 받은 ZoneId를 OS에 맞게 Init 함수에 세팅합니다.

![InitInterstitial](https://i.imgur.com/bg5oJAS.png)

#### 4.2 AD Load

Init 함수를 호출했다면 그 다음으로 Load 함수를 호출하여 광고를 요청합니다.<br>
*iOS14 이상에서는 사용자가 앱 추적 승인에 동의한 것을 확인 후 Load 하기를 권장 드립니다. 
Load에 대한 결과는 Callback을 통해서 확인할 수 있습니다.

![InterstitialLoad](https://i.imgur.com/qrTIWL4.png)

*Reward / Interstitial 광고 요청 후 광고가 Load 되기까지 일정 시간 딜레이가 발생합니다.<br>
Load 딜레이를 View단에 노출시키지 않기 위해 앱 시작 시 바로 광고를 요청하는 것을 권장 드립니다.

#### 4.3 Ad IsLoaded

Show 함수를 호출하기전 IsLoaded 함수를 호출하여 광고 Load 여부를 확인합니다.

![InterstitialIsLoad](https://i.imgur.com/kZIpv0j.png)

#### 4.4 Ad Show

Load 함수를 통해 광고요청에 성공하였다면, 광고를 노출시킵니다.

![InterstitialShow](https://i.imgur.com/PzZn4GS.png)

*광고를 Show했다면 Plugin에서 다시 Load를 수행합니다.<br>
이때 호출된 Load의 결과가 Fail인 경우에는 Load를 재호출 하지 않습니다.

#### 4.5 Ad Callback

Interstitial에서는 Load / Show / Close / Failed 4종의 Callback을 제공합니다.

![InterstitialCallbacks](https://i.imgur.com/3jvL5Ds.png)

### 5. Reward

Plugin을 통해 보상형 광고를 요청(Load)하고 광고를 노출(Show)하는 방법은 다음과 같습니다.<br>

#### 5.1 Init

Bidmad는 Android / iOS에 대한 ZoneId가 각각 발급되며, 발급 받은 ZoneId를 OS에 맞게 Init 함수에 세팅합니다.

![RewardInitReward](https://i.imgur.com/lNGm4KF.png)

#### 5.2 Load

Init 함수를 호출했다면 그 다음으로 Load 함수를 호출하여 광고를 요청합니다.<br>
*iOS14 이상에서는 사용자가 앱 추적 승인에 동의한 것을 확인 후 Load 하기를 권장 드립니다. 
Load에 대한 결과는 Callback을 통해서 확인할 수 있습니다.

![RewardLoad](https://i.imgur.com/t27Bkzr.png)

#### 5.3 IsLoaded

Show 함수를 호출하기전 IsLoaded 함수를 호출하여 광고 Load 여부를 확인합니다.

![RewardIsLoaded](https://i.imgur.com/5ZJlmXT.png)

#### 5.4 Show

Load 함수를 통해 광고요청에 성공하였다면, 광고를 노출시킵니다.

![RewardShow](https://i.imgur.com/daz2mqc.png)

*광고를 Show했다면 Plugin에서 다시 Load를 수행합니다.<br>
이때 호출된 Load의 결과가 Fail인 경우에는 Load를 재호출 하지 않습니다.

#### 5.5 Ad Callback

Reward에서는 Load / Show / Close / Failed / Complete / Skipped 6종의 Callback을 제공합니다.

![RewardCallbacks](https://i.imgur.com/RiGEi7I.png)

### 6. Common

Common는 디버깅 모드, iOS14 AppTrackingAuthorization 기능 등 광고 외 기능을 제공하는 컴포넌트 입니다.

#### 6.1 SetDebugging

SetDebugging True를 호출 시 디버깅 로그가 출력됩니다.

![CommonSetDebugging](https://i.imgur.com/ejEIn1w.jpg)

#### 6.2 ReqAdTrackingAuthorization

iOS 14에서 앱 추적 투명성 동의 팝업을 노출 시키고, 그에 대한 결과 Callback을 제공합니다.

![CommonReqAdTrackingAuthorization](https://i.imgur.com/ygbgJQr.png)

#### 6.3 SetAdvertiserTrackingEnabled

Plugin에서 제공하는 ReqAdTrackingAuthorization이 아닌 다른 방법을 통해 앱 추적 투명성 동의를 얻는 경우,
<br>사용자가 동의했다면 True, 거부했다면 False를 SetAdvertiserTrackingEnabled를 통해 전달하세요.

![CommonSetAdvertiserTrackingEnabled](https://i.imgur.com/N6GdBFG.png)

#### 6.4 GetAdvertiserTrackingEnabled

SetAdvertiserTrackingEnabled을 통해 세팅한 값을 확인합니다.

![CommonGetAdvertiserTrackingEnabled](https://i.imgur.com/53vlLEU.png)

#### 6.5 SetCUID 

서버 사이드 콜백을 위한 CUID 설정

![CommonSetCUID](https://i.imgur.com/ftRQ1Ao.png)

#### 6.6 SetChildDirected

어린이 사용이 가능한 앱인지 설정

![CommonSetChildDirected](https://i.imgur.com/UoXFund.png)

#### 6.7 BindEventToOnInitializeSdk

InitializeSdkWithCallback 메서드 사용 시, 콜백을 받을 수 있는 이벤트를 설정. bool 값은 초기화 여부를 의미 

![CommonBindEventToOnInitializeSdk](https://i.imgur.com/YNl8KRZ.png)

#### 6.8 InitializeSdkWithCallback

SDK 초기화 호출 이후, 콜백 이벤트 발생.

![CommonInitializeSdkWithCallback](https://i.imgur.com/DxS1cgR.png)

#### 6.9 InitializeSdk

콜백 없이, SDK 초기화 메서드 호출

![CommonInitializeSdk](https://i.imgur.com/LFx7ceN.png)

#### 6.10 isAdFree 

쿠팡 광고에 의한 광고 차단여부 확인.

![CommonIsAdFree](https://i.imgur.com/PhbimpP.jpg)

#### 6.11 BindEventToOnAdFree

쿠팡 광고에 의한 광고 차단 변경 콜백 이벤트 발생. 

![CommonIsAdFree](https://i.imgur.com/IP53Q0y.jpg)


#### References
- Unreal GDPR Guide [KOR](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-GDPR-Guide-%5BKOR%5D) | [ENG](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-GDPR-Guide-%5BENG%5D)
- [Blueprint Sample Image](https://github.com/bidmad/Bidmad-Unreal/wiki/Blueprint-Sample-Image)
- C++ Sample Code [KOR](https://github.com/bidmad/Bidmad-Unreal/wiki/CPP-%EC%BD%94%EB%93%9C-%EC%83%98%ED%94%8C) | [ENG](https://github.com/bidmad/Bidmad-Unreal/wiki/CPP-Code-Sample)
- [쿠팡 네트워크 광고 차단 인터페이스 가이드](https://github.com/bidmad/Bidmad-Unreal/wiki/쿠팡-네트워크-광고-차단-인터페이스-가이드)
