// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Enjoy_Your_Stay : ModuleRules
{
	public Enjoy_Your_Stay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Enjoy_Your_Stay",
			"Enjoy_Your_Stay/Variant_Horror",
			"Enjoy_Your_Stay/Variant_Horror/UI",
			"Enjoy_Your_Stay/Variant_Shooter",
			"Enjoy_Your_Stay/Variant_Shooter/AI",
			"Enjoy_Your_Stay/Variant_Shooter/UI",
			"Enjoy_Your_Stay/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
