// SnakeGame project

using UnrealBuildTool;

public class SnakeGame : ModuleRules
{
    public SnakeGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "EnhancedInput", "Niagara" });

        PublicIncludePaths.AddRange(new string[] { "SnakeGame" });

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.Add("FunctionalTesting");
        }
    }
}
