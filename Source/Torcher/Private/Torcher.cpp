// Copyright Epic Games, Inc. All Rights Reserved.

#include "Torcher.h"
#include "CoreMinimal.h"

#include "Kismet/GameplayStatics.h"
#include "Macros/TorcherPreProcMacros.h"
#include "HAL/FileManager.h"

TORCH_INCLUDES_START
#include <torch/custom_class.h>
#include <torch/version.h>
TORCH_INCLUDES_END

#define LOCTEXT_NAMESPACE "FTorcherModule"

void FTorcherModule::StartupModule()
{
#ifndef WITH_LIBTORCH
	UE_LOG(LogInit, Fatal, TEXT("LibTorch is missing. Unable to start Torcher."));
#endif // !WITH_LIBTORCH

	FString LibraryPath;
	if (!GetLibraryPath(LibraryPath))
	{
		UE_LOG(LogInit, Fatal, TEXT("Cannot load LibTorch on Platform: %s"), *UGameplayStatics::GetPlatformName());
		return;
	}

	const TCHAR* const LibraryPathPointer = *LibraryPath;
	UE_LOG(LogTemp, Warning, TEXT("Loading LibTorch Libraries from: %s"), LibraryPathPointer);

#if PLATFORM_WINDOWS
	FPlatformProcess::AddDllDirectory(LibraryPathPointer);

	TArray<FString> DLLNames;
	IFileManager::Get().FindFilesRecursive(
		DLLNames,
		LibraryPathPointer,
		TEXT("*.dll"),
		true,
		false,
		false
	);

	DLLHandles.Reserve(DLLNames.Num());
	for (const FString& DLLName : DLLNames)
	{
		DLLHandles.Emplace(static_cast<uint8*>(FPlatformProcess::GetDllHandle(*DLLName)));
	}
#endif

	torch::init();
	UE_LOG(LogInit, Warning, TEXT("Loaded Torcher Plugin with Torch modules successfully!"));
}

void FTorcherModule::ShutdownModule()
{
	UE_LOG(LogInit, Warning, TEXT("Unloaded Torcher Plugin with Torch modules successfully!"));	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTorcherModule, Torcher)
