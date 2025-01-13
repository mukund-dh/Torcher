using UnrealBuildTool;

public class TorcherEditor : ModuleRules
{
    public TorcherEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseRTTI = true;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
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
                "Projects",
                "AssetTools",
                "Torcher",
                "UnrealEd",
                "PropertyEditor",
                "ToolMenus",
                "GraphEditor"
            }
        );
    }
}