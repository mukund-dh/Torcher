// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherLayerLinearOptions.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Torcher Linear Layer Options")
struct TORCHER_API FTorcherLayerLinearOptions : public FTorcherLayerBaseOptions
{
	GENERATED_BODY()

	/*
	 * Dimensions of the Weights Tensor
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layer|Linear Layer")
	TArray<int64> WeightsDimensions;

	/*
	 * Dimensions of the Bias Tensor. This should *ideally* be equal to the last dimension
	 * of the Weights Tensor.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layer|Linear Layer")
	TArray<int64> BiasDimensions;

	/*
	 * Should we use Bias?
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Layer|Linear Layer")
	bool bUseBias;

	UE_NODISCARD_CTOR
	FTorcherLayerLinearOptions();
};
