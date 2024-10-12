// Mukund Dhananjay - 2024

using Microsoft.Extensions.Logging;
using System.IO;
using UnrealBuildTool;

public class LibTorch : ModuleRules
{
    public LibTorch(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PCHUsage = PCHUsageMode.NoPCHs;
        IWYUSupport = IWYUSupport.Full;
        CppStandard = CppStandardVersion.Cpp20;

        bUseRTTI = true;
        bUseUnity = false;
        bUsePrecompiled = false;
        bEnableExceptions = true;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.AddRange(
                new string[]
                {
                    "NO_EXPORT",
                    "WITH_LIBTORCH"
                });

            // Add the import libraries
            LinkLibraryFiles();
        }
        else
        {
            EpicGames.Core.Log.Logger.LogError("LibTorch can only be loaded on the Win64 platform.");
        }

        // Add in the include files
        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "x64", "include"),
                Path.Combine(ModuleDirectory, "x64", "include/torch/csrc/api/include")
            }
        );
    }

    private void LinkLibraryFiles()
    {
        // Library folders should ideally be on $ModuleDirectory/x64/lib
        string libPath = Path.Combine(ModuleDirectory, "x64", "lib");
        var files = Directory.GetFiles(libPath, "*", SearchOption.AllDirectories);
        foreach (var filePath in files)
        {
            var fileName = Path.GetFileName(filePath);

            if (fileName.EndsWith(".lib"))
            {
                PublicAdditionalLibraries.Add(filePath);
            }
            else if (fileName.EndsWith(".dll"))
			{
				RuntimeDependencies.Add(filePath);
				PublicDelayLoadDLLs.Add(fileName);
			}
            else
            {
                System.Console.WriteLine("Ignored FilePath {0}", filePath);
            }
        }
    }
} 