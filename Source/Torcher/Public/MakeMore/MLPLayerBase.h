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
 * 
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
	
	template <typename T>
	TArray<T> GetOutTensorAsArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsArray_Int32(TArray<int32>& OutArray) noexcept
	{
		OutArray = GetOutTensorAsArray<int32>();
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsArray_Float(TArray<float>& OutArray) noexcept
	{
		OutArray = GetOutTensorAsArray<float>();
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void GetOutTensorAsArray_UInt8(TArray<uint8>& OutArray) noexcept
	{
		OutArray = GetOutTensorAsArray<uint8>();
	}
	
	// Forward Pass on this layer
	virtual at::Tensor Forward(const at::Tensor& InTensor) noexcept;

protected:
	// Set the value of the TensorPtr to the passed NewTensor
	void SetTensor(at::Tensor*& TensorPtr, const at::Tensor& NewTensor) noexcept;

	// Set the value of the TensorPtr to the passed TArray
	template <typename T>
	void SetTensor(at::Tensor*& TensorPtr, const TArray<T>& InArray, const TArray<int32>& Dimensions);

	// Convert at::Tensor to a flat TArray<T>. This eschews the for-loop method, which would've
	// taken a bit and a half to convert data. This is a slightly more direct model.
	template <typename T>
	std::vector<T> ConvertTensorToVector(const at::Tensor& InTensor);
};


