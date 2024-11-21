// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Package.h"
#include "MakeMore/MLPLayerBase.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/function.h>
#include <torch/torch.h>
TORCH_INCLUDES_END

#include "LinearLayer.generated.h"

/**
 * Data Asset definition of a Linear Layer, which uses a float tensor
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API ULinearLayer : public UMLPLayerBase
{
	GENERATED_BODY()

public:
	// Constructor
	UE_NODISCARD_CTOR
	ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept;

	// Destructor to de-initialize the at::Tensor pointers
	~ULinearLayer() noexcept;

	// Dimension1 for the tensor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Inits")
	int32 FanIn;

	// The Dimension2 for the tensor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Inits")
	int32 FanOut;

	// Does this layer use it's bias?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Params")
	bool bHasBias;

	// The seed for the generator
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Params")
	int64 Seed;

protected:
	// Tensor which stores the weights for this layer
	at::Tensor* Weights;
	
	// Tensor to store bias(es) for this layer
	at::Tensor* Bias;

public:

	// Function to Initialize Weights and Biases
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void InitTensors() noexcept;

	// Forward Pass on this layer
	virtual at::Tensor operator()(const at::Tensor& InTensor) noexcept override;

	// Basic Debug Function. USE AT YOUR OWN RISK
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor")
	float GetValueAtIndex(TArray<int32> IndexArray) const;

	// Get the Weights as a TArray<int32>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetWeightsAsIntArray(TArray<int32>& WeightsArray)
	{
		WeightsArray = GetTensorAsArray<int32>(Weights);
	}
	
	// Get the Weights as a TArray<float>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetWeightsAsFloatArray(TArray<float>& WeightsArray)
	{
		WeightsArray = GetTensorAsArray<float>(Weights);
	}

	// Get the Weights as a TArray<int32>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetWeightsAsByteArray(TArray<uint8>& WeightsArray)
	{
		WeightsArray = GetTensorAsArray<uint8>(Weights);
	}

	// Get the Weights as a TArray<int32>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetBiasAsIntArray(TArray<int32>& BiasArray)
	{
		BiasArray = GetTensorAsArray<int32>(Bias);
	}
	
	// Get the Weights as a TArray<float>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetBiasAsFloatArray(TArray<float>& BiasArray)
	{
		BiasArray = GetTensorAsArray<float>(Bias);
	}

	// Get the Weights as a TArray<int32>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	FORCEINLINE void GetBiasAsByteArray(TArray<uint8>& BiasArray)
	{
		BiasArray = GetTensorAsArray<uint8>(Bias);
	}

	// Convert the given flat int32 array to Weights
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetWeightsFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Weights, InArray, Dimensions);
	}
	
	// Convert the given flat float array to Weights
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetWeightsFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Weights, InArray, Dimensions);
	}

	// Convert the given flat byte array to Weights
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetWeightsFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Weights, InArray, Dimensions);
	}

	// Convert the given flat int32 array to a Bias tensor
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetBiasFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Bias, InArray, Dimensions);
	}
	
	// Convert the given flat float array to a Bias tensor
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetBiasFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Bias, InArray, Dimensions);
	}

	// Convert the given flat uint8 array to a Bias tensor
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	FORCEINLINE void SetBiasFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions)
	{
		SetTensor(Bias, InArray, Dimensions);
	}

	// Get the at::Tensor* for Weights
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetWeights() const noexcept { return Weights; }

	// Get the at::Tensor* for Bias
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetBias() const noexcept { return Bias; }

	// Set the Weights tensor from an input
	FORCEINLINE void SetWeightsFromTensor(const at::Tensor& NewWeights) noexcept
	{
		SetTensor(Weights, NewWeights);
	}

	// Set the Bias tensor from an input
	FORCEINLINE void SetBiasFromTensor(const at::Tensor& NewBias) noexcept
	{
		SetTensor(Bias, NewBias);
	}
};
