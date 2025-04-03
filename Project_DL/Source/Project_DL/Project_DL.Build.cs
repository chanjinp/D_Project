// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class Project_DL : ModuleRules
{
	public Project_DL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			"Project_DL"
		});

		PublicDependencyModuleNames.AddRange(new string[] { "Core",
			"CoreUObject",
			"Engine",
			"InputCore",
            "EnhancedInput",
            "GameplayTags",
            "GameplayTasks", //GAS
			"GameplayAbilities", //GAS
			"NavigationSystem", // AI 길찾기 등 관련 시스템
			"AIModule", //AI
			"Niagara",
			"UMG" //UI 관련 시스템
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
