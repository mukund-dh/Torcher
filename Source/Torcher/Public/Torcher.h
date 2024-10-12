// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TorcherModule.h"

#define LOCTEXT_NAMESPACE "FTorcherModule"

class FTorcherModule : public ITorcherModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Handle to the test dll we will load */
	void*	ExampleLibraryHandle;
};

#undef LOCTEXT_NAMESPACE