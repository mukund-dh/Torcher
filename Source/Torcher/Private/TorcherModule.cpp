// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherModule.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif

#define LOCTEXT_NAMESPACE "ITorcherModule"

#if PLATFORM_WINDOWS
TArray<TUniquePtr<uint8, FDLLManager>> ITorcherModule::DLLHandles;
#endif

const FName ITorcherModule::ModuleName = TEXT("Torcher");

#if PLATFORM_WINDOWS
void FDLLManager::operator()(uint8* DLLHandle) const noexcept
{
	if (DLLHandle)
	{
		FPlatformProcess::FreeDllHandle(DLLHandle);
	}
}
#endif

bool ITorcherModule::GetLibraryPath(FString& OutPath) noexcept
{
	const IPlugin* const TorcherPlugin = IPluginManager::Get().FindPlugin(ModuleName.ToString()).Get();
	if (!TorcherPlugin)
		return false;

	OutPath = TorcherPlugin->GetBaseDir() / TEXT("Source/ThirdParty/LibTorch");

#if PLATFORM_WINDOWS
	OutPath /= "x64";
#elif
	return false;
#endif

	OutPath /= "lib";
	return true;
}

#undef LOCTEXT_NAMESPACE