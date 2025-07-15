// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using System;
using UnrealBuildTool;

public class BidmadPlugin : ModuleRules
{
    public BidmadPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        //PrivatePCHHeaderFile = "Public/BidmadPluginPCH.h";
        
        PublicIncludePaths.AddRange(
            new string[] {
                // ... add public include paths required here ...
                Path.Combine(ModuleDirectory, "Public"),
            }
        );
                
        
        PrivateIncludePaths.AddRange(
            new string[] {
                // ... add other private include paths required here ...
                Path.Combine(ModuleDirectory, "Private"),
            }
        );
            
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                // ... add other public dependencies that you statically link with here ...
            }
        );
            
        
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                // ... add private dependencies that you statically link with here ...  
            }
        );
        
        
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );
            
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicIncludePaths.AddRange(
                new string[] {
                    "Runtime/Launch/Public" //JNI
                }
            );

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "Bidmad_AOS_UPL.xml"));
        }else if (Target.Platform == UnrealTargetPlatform.IOS){
            AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(ModuleDirectory, "Bidmad_IOS_UPL.xml"));

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AdMixer",
                    "../../ThirdParty/IOS/AdMixer.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AdMixerMediation",
                    "../../ThirdParty/IOS/AdMixerMediation.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AppLovinAdapter",
                    "../../ThirdParty/IOS/AppLovinAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AppLovinSDK",
                    "../../ThirdParty/IOS/AppLovinSDK.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadAdmixerAdapter",
                    "../../ThirdParty/IOS/BidmadAdmixerAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadAppLovinAdapter",
                    "../../ThirdParty/IOS/BidmadAppLovinAdapter.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadFyberAdapter",
                    "../../ThirdParty/IOS/BidmadFyberAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadGoogleAdManagerAdapter",
                    "../../ThirdParty/IOS/BidmadGoogleAdManagerAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadGoogleAdMobAdapter",
                    "../../ThirdParty/IOS/BidmadGoogleAdMobAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadMobwithAdapter",
                    "../../ThirdParty/IOS/BidmadMobwithAdapter.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadORTBAdapter",
                    "../../ThirdParty/IOS/BidmadORTBAdapter.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadPangleAdapter",
                    "../../ThirdParty/IOS/BidmadPangleAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadSDK",
                    "../../ThirdParty/IOS/BidmadSDK.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadTaboolaAdapter",
                    "../../ThirdParty/IOS/BidmadTaboolaAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadTeadsAdapter",
                    "../../ThirdParty/IOS/BidmadTeadsAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadUnityAdsAdapter",
                    "../../ThirdParty/IOS/BidmadUnityAdsAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadVungleAdapter",
                    "../../ThirdParty/IOS/BidmadVungleAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "DTExchangeAdapter",
                    "../../ThirdParty/IOS/DTExchangeAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "FBAudienceNetwork",
                    "../../ThirdParty/IOS/FBAudienceNetwork.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "GoogleMobileAds",
                    "../../ThirdParty/IOS/GoogleMobileAds.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "IASDKCore",
                    "../../ThirdParty/IOS/IASDKCore.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "LiftoffMonetizeAdapter",
                    "../../ThirdParty/IOS/LiftoffMonetizeAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MetaAdapter",
                    "../../ThirdParty/IOS/MetaAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MintegralAdapter",
                    "../../ThirdParty/IOS/MintegralAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDK",
                    "../../ThirdParty/IOS/MTGSDK.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKBanner",
                    "../../ThirdParty/IOS/MTGSDKBanner.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKBidding",
                    "../../ThirdParty/IOS/MTGSDKBidding.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKInterstitialVideo",
                    "../../ThirdParty/IOS/MTGSDKInterstitialVideo.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKNativeAdvanced",
                    "../../ThirdParty/IOS/MTGSDKNativeAdvanced.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKNewInterstitial",
                    "../../ThirdParty/IOS/MTGSDKNewInterstitial.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKReward",
                    "../../ThirdParty/IOS/MTGSDKReward.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MTGSDKSplash",
                    "../../ThirdParty/IOS/MTGSDKSplash.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OMSDK_Teadstv",
                    "../../ThirdParty/IOS/OMSDK_Teadstv.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OpenBiddingHelper",
                    "../../ThirdParty/IOS/OpenBiddingHelper.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "PAGAdSDK",
                    "../../ThirdParty/IOS/PAGAdSDK.embeddedframework.zip",
                    "Resources/PAGAdSDK.bundle"
                 )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "PangleAdapter",
                    "../../ThirdParty/IOS/PangleAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "TaboolaSDK",
                    "../../ThirdParty/IOS/TaboolaSDK.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "TeadsSDK",
                    "../../ThirdParty/IOS/TeadsSDK.embeddedframework.zip",
                    null,
                    true
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "UnityAdapter",
                    "../../ThirdParty/IOS/UnityAdapter.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "UnityAds",
                    "../../ThirdParty/IOS/UnityAds.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "UserMessagingPlatform",
                    "../../ThirdParty/IOS/UserMessagingPlatform.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new Framework(
                    "VungleAdsSDK",
                    "../../ThirdParty/IOS/VungleAdsSDK.embeddedframework.zip"
                )
            );

            PublicFrameworks.AddRange(
                new string[] {
                    "StoreKit",
                    "MobileCoreServices",
                    "WebKit",
                    "MediaPlayer",
                    "CoreMedia",
                    "AVFoundation",
                    "CoreTelephony",
                    "SystemConfiguration",
                    "AdSupport",
                    "CoreMotion",
                    "Accelerate",
                    "Security",
                    "JavaScriptCore",
                    "AudioToolbox"
                }
            );

            string SDKPATH = "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/usr/lib";
            PublicAdditionalLibraries.Add(SDKPATH + "/libresolv.9.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libc++.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libz.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libsqlite3.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libbz2.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libxml2.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libiconv.tbd");
            PublicAdditionalLibraries.Add(SDKPATH + "/libc++abi.tbd");
            
            PublicSystemLibraries.Add("xml2");
            PublicSystemLibraries.Add("sqlite3");
            PublicSystemLibraries.Add("resolv");
            
            string SDKROOT = Utils.RunLocalProcessAndReturnStdOut("/usr/bin/xcrun", "--sdk iphoneos --show-sdk-path");
            PublicSystemLibraryPaths.Add(SDKROOT + "/usr/lib/swift");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.0/iphoneos");
            PublicSystemLibraryPaths.Add(SDKROOT + "../../../../../../Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.5/iphoneos");
            PublicSystemLibraries.Add("z");
            PublicSystemLibraries.Add("bz2");
            PublicSystemLibraries.Add("c++abi");
        }
    }
}
