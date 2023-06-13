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
                    "UnityAds",
                    "../../ThirdParty/IOS/UnityAds.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "FBLPromises",
                    "../../ThirdParty/IOS/FBLPromises.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "ADOPUtility",
                    "../../ThirdParty/IOS/ADOPUtility.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadAdapterDynamic",
                    "../../ThirdParty/IOS/BidmadAdapterDynamic.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OpenBiddingHelper",
                    "../../ThirdParty/IOS/OpenBiddingHelper.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BidmadSDK",
                    "../../ThirdParty/IOS/BidmadSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AdFitSDK",
                    "../../ThirdParty/IOS/AdFitSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AdColony",
                    "../../ThirdParty/IOS/AdColony.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "AdColonyAdapter",
                    "../../ThirdParty/IOS/AdColonyAdapter.embeddedframework.zip"
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
                    "Resources/AppLovinSDKResources.bundle"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "FrameworkWrapper",
                    "../../ThirdParty/IOS/FrameworkWrapper.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BURelyAdSDK",
                    "../../ThirdParty/IOS/BURelyAdSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "BUAdSDK",
                    "../../ThirdParty/IOS/BUAdSDK.embeddedframework.zip"
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
                    "FyberAdapter",
                    "../../ThirdParty/IOS/FyberAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "GoogleAppMeasurement",
                    "../../ThirdParty/IOS/GoogleAppMeasurement.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "GoogleAppMeasurementIdentitySupport",
                    "../../ThirdParty/IOS/GoogleAppMeasurementIdentitySupport.embeddedframework.zip"
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
                    "GoogleUtilities",
                    "../../ThirdParty/IOS/GoogleUtilities.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "IASDKCore",
                    "../../ThirdParty/IOS/IASDKCore.embeddedframework.zip",
                    "Resources/IASDKResources.bundle"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "InMobiAdapter",
                    "../../ThirdParty/IOS/InMobiAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "InMobiSDK",
                    "../../ThirdParty/IOS/InMobiSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "IronSource",
                    "../../ThirdParty/IOS/IronSource.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "IronSourceAdapter",
                    "../../ThirdParty/IOS/IronSourceAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "nanopb",
                    "../../ThirdParty/IOS/nanopb.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "Tapjoy",
                    "../../ThirdParty/IOS/Tapjoy.embeddedframework.zip"
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
                    "UserMessagingPlatform",
                    "../../ThirdParty/IOS/UserMessagingPlatform.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "VungleAdapter",
                    "../../ThirdParty/IOS/VungleAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "VungleSDK",
                    "../../ThirdParty/IOS/VungleSDK.embeddedframework.zip"
                )
            );

            // MetaAdapter.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "MetaAdapter",
                    "../../ThirdParty/IOS/MetaAdapter.embeddedframework.zip"
                )
            );

            // OMSDK_Pubmatic.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OMSDK_Pubmatic",
                    "../../ThirdParty/IOS/OMSDK_Pubmatic.embeddedframework.zip"
                )
            );

            // OMSDK_Teadstv.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OMSDK_Teadstv",
                    "../../ThirdParty/IOS/OMSDK_Teadstv.embeddedframework.zip"
                )
            );

            // OneKit_Pangle.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OneKit_Pangle",
                    "../../ThirdParty/IOS/OneKit_Pangle.embeddedframework.zip"
                )
            );

            // OpenWrapHandlerDFP.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OpenWrapHandlerDFP",
                    "../../ThirdParty/IOS/OpenWrapHandlerDFP.embeddedframework.zip"
                )
            );

            // OpenWrapMeasurement.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OpenWrapMeasurement",
                    "../../ThirdParty/IOS/OpenWrapMeasurement.embeddedframework.zip"
                )
            );

            // OpenWrapSDK.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "OpenWrapSDK",
                    "../../ThirdParty/IOS/OpenWrapSDK.embeddedframework.zip"
                )
            );

            // PAGAdSDK.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "PAGAdSDK",
                    "../../ThirdParty/IOS/PAGAdSDK.embeddedframework.zip",
                    "Resources/PAGAdSDK.bundle"
                )
            );

            // PangleAdapter.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "PangleAdapter",
                    "../../ThirdParty/IOS/PangleAdapter.embeddedframework.zip"
                )
            );

            // RangersAPM_Pangle.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "RangersAPM_Pangle",
                    "../../ThirdParty/IOS/RangersAPM_Pangle.embeddedframework.zip",
                    "Resources/APMInsightCore.bundle"
                )
            );

            // RARegisterKit.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "RARegisterKit",
                    "../../ThirdParty/IOS/RARegisterKit.embeddedframework.zip"
                )
            );

            // TeadsSDK.embeddedframework
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "TeadsSDK",
                    "../../ThirdParty/IOS/TeadsSDK.embeddedframework.zip"
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
        }
    }
}