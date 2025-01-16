// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherLayerTanHOptions.generated.h"

/**
 * TanH Layer Options
 */
USTRUCT(BlueprintType, DisplayName = "Torcher TanH Layer Options")
struct TORCHER_API FTorcherLayerTanHOptions : public  FTorcherLayerBaseOptions
{
	GENERATED_BODY()

	UE_NODISCARD_CTOR
	FTorcherLayerTanHOptions();
};
