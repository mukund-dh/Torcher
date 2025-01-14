// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tensors/TorcherDeviceType.h"
#include "TorcherLayerBaseOptions.generated.h"


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category = "Layer|Base Params")
	FString LayerName;

	/*
	 * Device type of this layer
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true), Category = "Layer|Base Params")
	ETorcherTensorDeviceType LayerDeviceType;

	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FTorcherLayerBaseOptions();

	/*
	 * Sets the layer's name from a module
	 */
	void SetLayerName(const FString& NewLayerName);
};
