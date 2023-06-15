// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CollectProps_Project : ModuleRules
{
	public CollectProps_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
