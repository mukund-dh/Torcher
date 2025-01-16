// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherLayerBatchNorm1DOptions.generated.h"

/**
 * BatchNorm1D Options
 */
USTRUCT(BlueprintType, DisplayName="Torcher BatchNorm1D Layer Options")
struct TORCHER_API FTorcherLayerBatchNorm1DOptions : public FTorcherLayerBaseOptions
{
	GENERATED_BODY()

	/*
	 * Dimensions of the Tensors. Will be common to all.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	int64 Dimensions;

	/*
	 * Epsilon value. Constant for a layer.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	float Eps;

	/*
	 * Momentum of the normalization.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	float Momentum;
	
	/*
	 * Is this training?
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	bool bIsTraining;

	UE_NODISCARD_CTOR
	FTorcherLayerBatchNorm1DOptions();
};
