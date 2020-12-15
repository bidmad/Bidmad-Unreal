// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
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
                "Runtime/Launch/Public" //JNI
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
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "Bidmad_UPL.xml"));
        }else if (Target.Platform == UnrealTargetPlatform.IOS){
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
                    "AppLovinSDK",
                    "../../ThirdParty/IOS/AppLovinSDK.embeddedframework.zip"
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
                    "BidmadSDK",
                    "../ThirdParty/IOS/BidmadSDK.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "Chartboost",
                    "../../ThirdParty/IOS/Chartboost.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "ChartboostAdapter",
                    "../../ThirdParty/IOS/ChartboostAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "FBSDKCoreKit",
                    "../../ThirdParty/IOS/FBSDKCoreKit.embeddedframework.zip"
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
                    "FacebookAdapter",
                    "../../ThirdParty/IOS/FacebookAdapter.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "FBAudienceNetworkBiddingKit",
                    "../../ThirdParty/IOS/FBAudienceNetworkBiddingKit.embeddedframework.zip"
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
                    "GoogleAppMeasurement",
                    "../../ThirdParty/IOS/GoogleAppMeasurement.embeddedframework.zip"
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
                    "nanopb",
                    "../../ThirdParty/IOS/nanopb.embeddedframework.zip"
                )
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                    "PromisesObjC",
                    "../../ThirdParty/IOS/PromisesObjC.embeddedframework.zip"
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
                    "UnityAds",
                    "../ThirdParty/IOS/UnityAds.embeddedframework.zip"
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
                    "VungleSDK",
                    "../../ThirdParty/IOS/VungleSDK.embeddedframework.zip"
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
        }
	}
}
