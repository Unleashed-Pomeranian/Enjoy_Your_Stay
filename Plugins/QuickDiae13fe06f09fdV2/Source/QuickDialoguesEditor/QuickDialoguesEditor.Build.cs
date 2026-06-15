//Copyright (c) 2025 Elia Cantini. All rights reserved.
using UnrealBuildTool;
 
public class QuickDialoguesEditor : ModuleRules
{
    public QuickDialoguesEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "QuickDialogues",
                "UMG",
                "CommonUI"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "UMGEditor",
                "UnrealEd",
                "ToolMenus",
                "GraphEditor",
                "Kismet",
                "AssetTools",
                "AssetDefinition",
                "PropertyEditor",
                "EditorStyle",
                "WorkspaceMenuStructure",
                "BlueprintGraph",
                "KismetWidgets",
                "BehaviorTreeEditor",
                "AIModule",
                "AIGraph",
                "ApplicationCore",
                "DeveloperSettings"
            }
        );
    }
}