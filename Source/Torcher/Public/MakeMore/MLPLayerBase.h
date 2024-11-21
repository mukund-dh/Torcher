// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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

	// Destructor
	virtual ~UMLPLayerBase() noexcept
	{
		// Make sure we delete Out before we exit
		if (Out)
		{
			delete Out;
		}
	}

protected:
	// Tensor to store the outputs for this layer.
	at::Tensor* Out;

public:
	// Get the at::Tensor* for Out
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetOut() const noexcept { return Out; }

	/* 
	 * Template function to get the Out Tensor as a TArray
	 *
	 * Supported types: int32, float, uint8
	 */
	template <typename T>
	[[nodiscard]]
	TArray<T> GetTensorAsArray(at::Tensor*& TensorPtr) noexcept;
 	
	/*
	 * Blueprint Callable Function to get the Out Tensor as a TArray<int32>
	 *
	 * @param TArray<int32>& OutArray The array to populate the tensor values with
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsIntArray(TArray<int32>& OutArray) noexcept
	{
		OutArray = GetTensorAsArray<int32>(Out);
	}

	/*
	 * Blueprint Callable Function to get the Out Tensor as a TArray<float>
	 *
	 * @param TArray<float>& OutArray The array to populate the tensor values with
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsFloatArray(TArray<float>& OutArray) noexcept
	{
		OutArray = GetTensorAsArray<float>(Out);
	}

	/*
	 * Blueprint Callable Function to get the Out Tensor as a TArray<uint8>
	 *
	 * @param TArray<uint8>& OutArray The array to populate the tensor values with
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsByteArray(TArray<uint8>& OutArray) noexcept
	{
		OutArray = GetTensorAsArray<uint8>(Out);
	}

	/*
	 * Blueprint Callable Function to set the Out Tensor from a TArray<int32>
	 *
	 * @param TArray<int32>& InArray The array to populate the tensor values from
	 * @param const TArray<int32>& Dimensions The dimensions of the Out tensor
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetOutTensorFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor(Out, InArray, Dimensions);
	}

	/*
	 * Blueprint Callable Function to set the Out Tensor from a TArray<float>
	 *
	 * @param TArray<float>& InArray The array to populate the tensor values from
	 * @param const TArray<int32>& Dimensions The dimensions of the Out tensor
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetOutTensorFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor(Out, InArray, Dimensions);
	}

	/*
	 * Blueprint Callable Function to set the Out Tensor from a TArray<uint8>
	 *
	 * @param TArray<uint8>& InArray The array to populate the tensor values from
	 * @param const TArray<int32>& Dimensions The dimensions of the Out tensor
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetOutTensorFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor(Out, InArray, Dimensions);
	}
	
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

protected:
	/*
	 * Set the value of the TensorPtr to the passed NewTensor
	 *
	 * @param at::Tensor*& TensorPtr Address to the Tensor pointer you want to set
	 * @param const at::Tensor& NewTensor The new set of values you want to set the TensorPtr to 
	 */
	void SetTensor(at::Tensor*& TensorPtr, const at::Tensor& NewTensor) noexcept;

	/*
	 * Template function to set the value of the TensorPtr to the passed TArray
	 * Supported types are: int32, float, uint8
	 *
	 * @param at::Tensor*& TensorPtr Address to the Tensor pointer you want to set
	 * @param const TArray<T>& InArray The input TArray
	 * const TArray<int32>& Dimensions The Dimensions of the tensor
	 */
	template <typename T>
	void SetTensor(at::Tensor*& TensorPtr, const TArray<T>& InArray, const TArray<int32>& Dimensions) noexcept;

	// Convert at::Tensor to a flat TArray<T>. This eschews the for-loop method, which would've
	// taken a bit and a half to convert data. This is a slightly more direct model.
	template <typename T>
	std::vector<T> ConvertTensorToVector(const at::Tensor& InTensor);
};


