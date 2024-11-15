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
	UE_NODISCARD_CTOR
	ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept;

	~ULinearLayer() noexcept;

	// The Fan In for the tensor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Inits")
	int32 FanIn;

	// The Fan Out for the tensor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Inits")
	int32 FanOut;

	// Does this layer use it's bias?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Params")
	bool bHasBias;

	// The seed for the generator
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Layer|Params")
	int64 Seed;

	// Tensor which stores the weights for this layer
	at::Tensor* Weights;
	
	// Tensor to store bias(es) for this layer
	at::Tensor* Bias;

	// Tensor to store the output for this layer
	at::Tensor* Out;

public:

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor")
	void InitTensors() noexcept;
	
	at::Tensor Forward(const at::Tensor& InTensor) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor")
	float GetValueAtIndex(TArray<int32> IndexArray) const;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Options")
	void GetParameters(TArray<float>& WeightVals, TArray<float>& Biases);

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void GetOutputs(TArray<float>& OutVals);

private:

	std::vector<float> ConvertTensorToVector(const at::Tensor& InTensor);

	// at::Tensor ConvertArrayToTensor(const TArray<float>& Array, const std::vector<int64_t>& Sizes) const;
};
