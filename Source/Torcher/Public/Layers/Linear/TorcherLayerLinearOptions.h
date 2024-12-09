// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
TORCH_INCLUDES_END

#include "TorcherLayerLinearOptions.generated.h"

#define LOCTEXT_NAMESPACE "TorcherLayerLinearOptions"

/**
 * Options structure for the linear layer
 */
USTRUCT(BlueprintType, DisplayName = "Torcher Linear Layer Options")
struct FTorcherLayerLinearOptions : public FTorcherLayerBaseOptions
{
    GENERATED_BODY()

	/*
	 * Size of each input sample
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int64 InFeatures;

	/*
	 * Size of each output sample
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int64 OutFeatures;

	/*
	 * Determines if the layer will learn an additive bias or not
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool bBias;

	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FTorcherLayerLinearOptions();

	/*
	 * Returns the layer as the libtorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::LinearOptions() const
	{ return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias); }

	/*
	 * Copies the data from a libtorch structure
	 *
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::LinearOptions& Options);
};

#undef LOCTEXT_NAMESPACE