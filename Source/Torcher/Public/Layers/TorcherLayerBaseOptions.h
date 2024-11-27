// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TorcherLayerBaseOptions.generated.h"

namespace torch::nn
{
	class Module;
}

/**
 * 
 */
USTRUCT(BlueprintType, DisplayName = "Torcher Layer Base Options")
struct TORCHER_API FTorcherLayerBaseOptions
{
    GENERATED_BODY()

	/*
	 * Name of this layer
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category = "Layer Params")
	FString LayerName;

	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FTorcherLayerBaseOptions() noexcept;

	/*
	 * Sets the layer's name from a module
	 */
	void SetLayerName(const torch::nn::Module& Module) noexcept;
};
