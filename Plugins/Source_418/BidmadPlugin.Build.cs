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
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "Bidmad_UPL.xml")));
        }else if (Target.Platform == UnrealTargetPlatform.IOS){

            string PluginPathIOS = Path.GetFullPath(Path.Combine(ModuleDirectory, "../.."));
            PublicIncludePaths.Add(Path.Combine(PluginPathIOS, "ThirdParty/IOS/PromisesObjCHeaders"));

            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "PromisesObjC",
                    "../../ThirdParty/IOS/PromisesObjC.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "ADOPUtility",
                    "../../ThirdParty/IOS/ADOPUtility.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BidmadAdapterFC",
                    "../../ThirdParty/IOS/BidmadAdapterFC.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BidmadAdapterFNC",
                    "../../ThirdParty/IOS/BidmadAdapterFNC.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "OpenBiddingHelper",
                    "../../ThirdParty/IOS/OpenBiddingHelper.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BidmadSDK",
                    "../../ThirdParty/IOS/BidmadSDK.embeddedframework.zip"
                )
            );

            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "UnityAdapter",
                    "../../ThirdParty/IOS/UnityAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "AdColony",
                    "../../ThirdParty/IOS/AdColony.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "AdColonyAdapter",
                    "../../ThirdParty/IOS/AdColonyAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "AppLovinAdapter",
                    "../../ThirdParty/IOS/AppLovinAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "AppLovinSDK",
                    "../../ThirdParty/IOS/AppLovinSDK.embeddedframework.zip",
                    "Resources/AppLovinSDKResources.bundle"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BURelyAdSDK",
                    "../../ThirdParty/IOS/BURelyAdSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BURelyFoundation_Global",
                    "../../ThirdParty/IOS/BURelyFoundation_Global.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BUAdSDK",
                    "../../ThirdParty/IOS/BUAdSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BUFoundation",
                    "../../ThirdParty/IOS/BUFoundation.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "BUVAAuxiliary",
                    "../../ThirdParty/IOS/BUVAAuxiliary.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "FyberAdapter",
                    "../../ThirdParty/IOS/FyberAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "GoogleAppMeasurement",
                    "../../ThirdParty/IOS/GoogleAppMeasurement.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "GoogleAppMeasurementIdentitySupport",
                    "../../ThirdParty/IOS/GoogleAppMeasurementIdentitySupport.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "GoogleMobileAds",
                    "../../ThirdParty/IOS/GoogleMobileAds.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "GoogleUtilities",
                    "../../ThirdParty/IOS/GoogleUtilities.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "IASDKCore",
                    "../../ThirdParty/IOS/IASDKCore.embeddedframework.zip",
                    "Resources/IASDKResources.bundle"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "InMobiAdapter",
                    "../../ThirdParty/IOS/InMobiAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "InMobiSDK",
                    "../../ThirdParty/IOS/InMobiSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "IronSource",
                    "../../ThirdParty/IOS/IronSource.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "IronSourceAdapter",
                    "../../ThirdParty/IOS/IronSourceAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "nanopb",
                    "../../ThirdParty/IOS/nanopb.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "PAGAdSDK",
                    "../../ThirdParty/IOS/PAGAdSDK.embeddedframework.zip",
                    "Resources/PAGAdSDK.bundle"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "PangleAdapter",
                    "../../ThirdParty/IOS/PangleAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "Tapjoy",
                    "../../ThirdParty/IOS/Tapjoy.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "UnityAdapter",
                    "../../ThirdParty/IOS/UnityAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "UnityAds",
                    "../../ThirdParty/IOS/UnityAds.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "UserMessagingPlatform",
                    "../../ThirdParty/IOS/UserMessagingPlatform.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "VungleAdapter",
                    "../../ThirdParty/IOS/VungleAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new UEBuildFramework(
                    "VungleSDK",
                    "../../ThirdParty/IOS/VungleSDK.embeddedframework.zip"
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
