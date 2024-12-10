// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Layers/ITorcherLayer.h"
#include "TorcherLayerLinearOptions.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/linear.h>
TORCH_INCLUDES_END

#include "TorcherLayerLinear.generated.h"

#define LOCTEXT_NAMESPACE "TorcherLayerLinear"

/**
 * Linear Layer Implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Linear Layer")
class TORCHER_API UTorcherLayerLinear : public UObject, public IITorcherLayer
{
	GENERATED_BODY()

protected:
	virtual bool OnForward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor);

	virtual bool OnInitializeData_Implementation();

	TSharedPtr<torch::nn::Linear> Module = nullptr;
	
	/*
	 * Structure containing the instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FTorcherLayerLinearOptions Options;
};

#undef LOCTEXT_NAMESPACE