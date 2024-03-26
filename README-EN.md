# BidmadPlugin

BidmadPlugin is a plugin for using Bidmad, a mobile app advertisement SDK, in Unreal.<br>
You can use the plugin to serve interstitial/rewarded ads in Unreal mobile apps.<br>

- [Download the latest version and sample project](https://github.com/bidmad/Bidmad-Unreal/archive/master.zip)

## Get started
### 1. Plugin addition and setting
Copy the folder and file of **Plugins/BidmadPlugin** included in the downloaded sample project to the Plugins folder of the project to which the plugin will be applied.<br>
And, add BidmadPlugin to PublicDependencyModuleNames.AddRange declared in the **Source/Project.Build.cs** file in the project.

```
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "BidmadPlugin" });
```

#### 1.1 Android Settings

For AOS, additional settings are required in AndroidManifest.xml for Admob Application ID settings. <br>
*Check the value of com.google.android.gms.ads.APPLICATION_ID in the Admob dashboard.


1. Edit → ProjectSettings → Platform-Android → Advance APK Package → Extra Settings for <application> section, add the project settings by putting the following values : <br>
![Bidmad-AOS-Guide-1](https://i.imgur.com/kUhtsXg.png)<br>
```
<meta-data \n android:name="com.google.android.gms.ads.APPLICATION_ID" \n android:value="Your GAID"/>
```

#### 1.2 iOS settings

- When using 1.7.0 or higher versions of Bidmad Unreal Plugin, please use Xcode 15 or higher for app builds & distribution.<br>

- When using the example, download and unzip the iOS library separately through [iOS Dependency Download Link](https://drive.google.com/file/d/1cAXIsBMvVGxBU4_CojycVQvKUZZIqVLS/view?usp=sharing)<br>. Inside the example project, place the unzipped downloaded folder under the Plugins -> BidmadPlugin -> ThirdParty folder<br>

- Before proceeding with the settings below, the Unreal Engine Build Tool code needs to be modified. For the modification guide, please follow the [Unreal Build Tool Modification Guide](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-Build-Tool-Modification-Guide-for-iOS-Build). After completing the modification guide. Please proceed to the project settings below.<br>

- Please refer to the following link if you need a guide on Apple Store Privacy Survey: [Link](https://github.com/bidmad/Bidmad-Unreal/wiki/Apple-privacy-survey%5BKOR%5D).

1. Go inside the settings panel (Settings → Project Settings → Platforms → iOS)<br>

![Bidmad-iOS-Guide-1](https://i.imgur.com/zXC4whT.png)<br>
​
2. Go to the Additional Plist Data property, and set the values (GADApplicationIdentifier, NSAppTransportSecurity, NSUserTrackingUsageDescription, and SKAdNetworkItems) below.

![Bidmad-iOS-Guide-2](https://i.imgur.com/hYqnLJs.png)<br>

**Please change the <string>ca-app-pub-XXXX~XXXX</string> into the value given by the admob App ID for iOS.**<br>

<details markdown="1">
<summary><strong>Click to reveal the GADApplicationIdentifier, NSAppTransportSecurity, NSUserTrackingUsageDescription, and SKAdNetworkItems values to be added to Additional Plist Data.</strong></summary>
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

3. Enter the "-ObjC" to Additional Non-Shipping Linker Flags / Additional Shipping Linker Flags, as below.

![Bidmad-iOS-Guide-1](https://i.imgur.com/fPOvYUO.png)<br>

4. Set 'Support bitcode in Shipping' to OFF.

![Bidmad-iOS-Guide-4](https://i.imgur.com/UhdG6dG.png)<br>

### 2. Migration Guide (Only for users updating from v1.5.1 or below to v1.6.0 or higher)

- When referencing CommonInterface class, please call Get Common Interface Instance method first and use the interface from the CommonInterface class instance returned from the method.

![Bidmad-Unreal-Migration-CommonInterface-BP](https://i.imgur.com/na7D1D1.jpg)<br>

```
UCommonInterface* CommonInterface = UCommonInterface::GetCommonInterfaceInstance(); 
```

### 3. BidmadSDK Initialization (v1.5.0 or above)

Performs tasks required to run BidmadSDK. The SDK won't allow ads to load unless you call the initializeSdk method.<br>
The initializeSdk method receives the App Key as a parameter, and the App Key can be copied from ADOP Insight. You can get the App Key by referring to the [Find your App Key](https://github.com/bidmad/SDK/wiki/Find-your-app-key%5BEN%5D) guide.<br>
Before loading ads, call the initializeSdk method as shown in the following example at the beginning of app.

![InitializeSdkUnrealWithoutCallback](https://i.imgur.com/UJhYyPv.jpg)

Or, you can check the initialization status by calling initializeSdkWithCallback

![InitializeSdkUnrealWithCallback](https://i.imgur.com/gboXzkq.jpg)

### 4. Interstitial

The following is how to request (Load) an interstitial advertisement and show the advertisement through the plugin.<br>

#### 3.1 Init

Bidmad is issued each ZoneId for Android / iOS, and sets the issued ZoneId in the Init function according to the OS.

![InitInterstitial](https://i.imgur.com/bg5oJAS.png)

#### 3.2 AD Load

If you have called the Init function, then the Load function is called to request an advertisement.<br>
*For iOS14 or higher, it is recommended to load after confirming that the user has consented to app tracking authorization.
You can check the load result through Callback.

![InterstitialLoad](https://i.imgur.com/qrTIWL4.png)

*After requesting Interstitial advertisement, there is a certain time delay until advertisement is loaded.<br>
In order not to expose the load delay to the view, it is recommended to request an advertisement immediately when the app starts.

#### 3.3 Ad IsLoaded

Before calling the Show function, the IsLoaded function is called to check whether the advertisement is loaded.

![InterstitialIsLoad](https://i.imgur.com/kZIpv0j.png)

#### 3.4 Ad Show

If the advertisement request is successful through the Load function, the advertisement is displayed.

![InterstitialShow](https://i.imgur.com/PzZn4GS.png)

*If the advertisement is shown, the plugin loads again.<br>
At this time, if the result of the called Load is Fail, Load is not called again.

#### 3.5 Ad Callback

Interstitial provides 4 types of Callbacks: Load / Show / Close / Failed.

![InterstitialCallbacks](https://i.imgur.com/3jvL5Ds.png)

### 5. Reward

The following is how to request (Load) rewarded advertisement through plugin and show (Show) advertisement.<br>

#### 4.1 Init

Bidmad is issued each ZoneId for Android / iOS, and sets the issued ZoneId in the Init function according to the OS.

![RewardInitReward](https://i.imgur.com/lNGm4KF.png)

#### 4.2 Load

If you have called the Init function, then the Load function is called to request an advertisement.<br>
*For iOS14 or higher, it is recommended to load after confirming that the user has consented to app tracking authorization.
You can check the load result through Callback.

![RewardLoad](https://i.imgur.com/t27Bkzr.png)

*After requesting Reward advertisement, there is a certain time delay until advertisement is loaded.<br>
In order not to expose the load delay to the view, it is recommended to request an advertisement immediately when the app starts.

#### 4.3 IsLoaded

Before calling the Show function, the IsLoaded function is called to check whether the advertisement is loaded.

![RewardIsLoaded](https://i.imgur.com/5ZJlmXT.png)

#### 4.4 Show

If the advertisement request is successful through the Load function, the advertisement is displayed.

![RewardShow](https://i.imgur.com/daz2mqc.png)

*If the advertisement is shown, the plugin loads again.<br>
At this time, if the result of the called Load is Fail, Load is not called again.

#### 4.5 Ad Callback

Reward provides 6 types of Callbacks: Load / Show / Close / Failed / Complete / Skipped.

![RewardCallbacks](https://i.imgur.com/RiGEi7I.png)

### 6. Common

Common is a component that provides functions other than advertisements such as debugging mode and iOS14 AppTrackingAuthorization function.

#### 5.1 SetDebugging

Debugging log is output when calling SetDebugging True.

![CommonSetDebugging](https://i.imgur.com/ejEIn1w.jpg)

#### 5.2 ReqAdTrackingAuthorization

In iOS 14, the app tracking transparency consent popup is exposed, and the resulting callback is provided.

![CommonReqAdTrackingAuthorization](https://i.imgur.com/ygbgJQr.png)

#### 5.2 SetAdvertiserTrackingEnabled

When obtaining app tracking transparency consent through a method other than ReqAdTrackingAuthorization provided by Plugin, 
<br>pass agrees(True) and rejected(False) through SetAdvertiserTrackingEnabled.

![CommonSetAdvertiserTrackingEnabled](https://i.imgur.com/N6GdBFG.png)

#### 5.4 GetAdvertiserTrackingEnabled

Check the value set through SetAdvertiserTrackingEnabled.

![CommonGetAdvertiserTrackingEnabled](https://i.imgur.com/53vlLEU.png)

#### 5.5 SetCUID 

Set the customer id for server-side callbacks

![CommonSetCUID](https://i.imgur.com/ftRQ1Ao.png)

#### 5.6 SetChildDirected

Set if your app is for child or not

![CommonSetChildDirected](https://i.imgur.com/UoXFund.png)

#### 5.7 BindEventToOnInitializeSdk

When using the InitializeSdkWithCallback method, set up events that can receive callbacks. A bool value means whether to initialize

![CommonBindEventToOnInitializeSdk](https://i.imgur.com/YNl8KRZ.png)

#### 5.8 InitializeSdkWithCallback

Callback event occurs after calling SDK initialization.

![CommonInitializeSdkWithCallback](https://i.imgur.com/DxS1cgR.png)

#### 5.9 InitializeSdk

Calling SDK initialization methods, without callbacks

![CommonInitializeSdk](https://i.imgur.com/LFx7ceN.png)

#### References
- Unreal GDPR Guide [KOR](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-GDPR-Guide-%5BKOR%5D) | [ENG](https://github.com/bidmad/Bidmad-Unreal/wiki/Unreal-GDPR-Guide-%5BENG%5D)
- [Blueprint Sample Image](https://github.com/bidmad/Bidmad-Unreal/wiki/Blueprint-Sample-Image)
- C++ Sample Code [KOR](https://github.com/bidmad/Bidmad-Unreal/wiki/CPP-%EC%BD%94%EB%93%9C-%EC%83%98%ED%94%8C) | [ENG](https://github.com/bidmad/Bidmad-Unreal/wiki/CPP-Code-Sample)
