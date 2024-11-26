// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/function.h>
#include <torch/torch.h>
TORCH_INCLUDES_END

#include "MLPLayerBase.generated.h"

/**
 * Base layer for a layer description in a multi layer perceptron
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API UMLPLayerBase : public UDataAsset
{
	GENERATED_BODY()

public:
	// Constructor
	UE_NODISCARD_CTOR
	UMLPLayerBase(const FObjectInitializer& ObjectInitializer) noexcept;

protected:
	// Tensor to store the outputs for this layer.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MLP|Tensors")
	UTorcherTensorFloat* Out;

public:
	
	/*
	 * override the "call" operator, which allows us to call this object as a function
	 *
	 * @param at::Tensor& InTensor The InTensor to perform the forward pass with
	 */
	virtual at::Tensor operator()(const at::Tensor& InTensor) noexcept
	{
		// Default behaviour, do nothing and just return the InTensor as is.
		return InTensor;
	}
	
};


