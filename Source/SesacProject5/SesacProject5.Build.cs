// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SesacProject5 : ModuleRules
{
	public SesacProject5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"Networking", "Sockets", "EnhancedInput", "AIModule", "NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        
        PrivateDependencyModuleNames.AddRange(new string[]
        {
	        "OnlineSubsystem", "OnlineSubsystemEOS", "EOSShared", "EOSVoiceChat", "OnlineServicesEOS",
	        "SocketSubsystemEOS", "OnlineSubsystemUtils"
        });
        
        PrivateDependencyModuleNames.AddRange(new string[]
        {
	        "ProceduralFPSAnimation"
        });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}