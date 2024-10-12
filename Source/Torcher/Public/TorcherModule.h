// Mukund Dhananjay - 2024.

#pragma once

#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "ITorcherModule"

#if PLATFORM_WINDOWS

/**
 * Store the DLL handles which need to be removed safely 
 */
struct FDLLManager
{
	// Unlink the DLL as soon as the pointer is deleted
	void operator()(uint8* DLLHandle) const noexcept;
};

#endif

/**
 * Runtime Interface to the Torcher Module
 */
class TORCHER_API ITorcherModule : public IModuleInterface
{
protected:

#if PLATFORM_WINDOWS
	// Collection of Smart Pointer objects which store the loaded DLLs
	static TArray<TUniquePtr<uint8, FDLLManager>> DLLHandles;
#endif

public:

	// Module Name
	static const FName ModuleName;

	static FORCEINLINE FString GetContentDirectory(const FString& AppendedPath = TEXT("")) noexcept
	{
		return IPluginManager::Get().FindPlugin(ModuleName.ToString())->GetContentDir() / AppendedPath;
	}

	// Finds where the library path(s) are located
	static bool GetLibraryPath(FString& OutPath) noexcept;

	// Check if the module is available
	[[nodiscard]]
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }

	// Load and get this module by name
	[[nodiscard]]
	static FORCEINLINE ITorcherModule& GetModule() { return FModuleManager::LoadModuleChecked<ITorcherModule>(ModuleName); }

#if PLATFORM_WINDOWS

	// Getter for DLL Handles
	[[nodiscard]]
	static FORCEINLINE const TArray<TUniquePtr<uint8, FDLLManager>>& GetDLLHandles() noexcept { return DLLHandles; }

#endif
	
};

#undef LOCTEXT_NAMESPACE
