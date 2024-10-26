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
};

#undef LOCTEXT_NAMESPACE