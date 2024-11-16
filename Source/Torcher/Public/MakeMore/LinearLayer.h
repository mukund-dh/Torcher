// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/Package.h"
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
class TORCHER_API ULinearLayer : public UDataAsset
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

private:
	// Tensor which stores the weights for this layer
	at::Tensor* Weights;
	
	// Tensor to store bias(es) for this layer
	at::Tensor* Bias;

	// Tensor to store the output for this layer
	at::Tensor* Out;

public:

	// Function to Initialize Weights and Biases
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void InitTensors() noexcept;

	// Forward Pass on this layer
	at::Tensor Forward(const at::Tensor& InTensor) noexcept;

	// Basic Debug Function. USE AT YOUR OWN RISK
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor")
	float GetValueAtIndex(TArray<int32> IndexArray) const;

	// Get the Parameters Weights and Bias as TArray<float>. Mostly use as a debug to
	// pass around in blueprints; Maybe build better usecases for this?
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	void GetParameters(TArray<float>& WeightVals, TArray<float>& Biases);

	// Similar to GetParameters, here get Out as TArray<float>
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void GetOutputs(TArray<float>& OutVals);

	// Convert the given flat array to Weights
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void SetWeightsFromArray(const TArray<float>& InArray, const TArray<int32>& Dimensions);

	// Convert the given flat array to Bias
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void SetBiasFromArray(const TArray<float>& InArray, const TArray<int32>& Dimensions);

	// Get the at::Tensor* for Weights
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetWeights() const noexcept { return Weights; }

	// Get the at::Tensor* for Bias
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetBias() const noexcept { return Bias; }

	// Get the at::Tensor* for Out
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetOut() const noexcept { return Out; }

	// Set the Weights tensor from an input
	FORCEINLINE void SetWeightsFromTensor(const at::Tensor& NewWeights) noexcept
	{
		if (Weights)
		{
			delete Weights;
			Weights = nullptr;
		}

		Weights = new at::Tensor(NewWeights.clone());
	}

	// Set the Bias tensor from an input
	FORCEINLINE void SetBiasFromTensor(const at::Tensor& NewBias) noexcept
	{
		if (Bias)
		{
			delete Bias;
			Bias = nullptr;
		}

		Bias = new at::Tensor(NewBias.clone());
	}
	
private:

	// Convert at::Tensor to a flat TArray<float>. This eschews the for-loop method, which would've
	// taken a bit and a half to convert data. This is a slightly more direct model.
	std::vector<float> ConvertTensorToVector(const at::Tensor& InTensor);
	
};
