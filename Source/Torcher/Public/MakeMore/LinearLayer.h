// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/Package.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Macros/TorcherPreProcMacros.h"

#include "LinearLayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API ULinearLayer : public UDataAsset
{
	GENERATED_BODY()

	UE_NODISCARD_CTOR
	ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer Inits")
	int32 FanIn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer Inits")
	int32 FanOut;

	UObject* Weights;
	UObject* Bias;

public:

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor")
	void InitTensors() noexcept;
};
