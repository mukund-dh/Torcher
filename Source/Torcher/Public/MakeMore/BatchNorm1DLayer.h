// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MakeMore/MLPLayerBase.h"
#include "BatchNorm1DLayer.generated.h"

/**
 * The BatchNorm Layer, will only be a one dimensional one for now.
 */
UCLASS()
class TORCHER_API UBatchNorm1DLayer : public UMLPLayerBase
{
	GENERATED_BODY()

public:

	// Constructor
	/*UE_NODISCARD_CTOR
	UBatchNorm1DLayer(const FObjectInitializer& ObjectInitializer);

	// Destructor
	~UBatchNorm1DLayer()
	{
		// Clear any pointers which haven't been already handled
		if (Gamma)
			delete Gamma;

		if (Beta)
			delete Beta;

		if (RunningMean)
			delete RunningMean;

		if (RunningVariance)
			delete RunningVariance;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torcher|BatchNorm Params")
	TArray<int32> TensorDimensions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torcher|BatchNorm Params")
	float Epsilon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torcher|BatchNorm Params")
	float Momentum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Torcher|BatchNorm Params")
	float bTraining;

protected:
	// Parameters; Trained with backpropagation
	at::Tensor* Gamma;
	at::Tensor* Beta;

	// Buffers; trained with running momentum update
	at::Tensor* RunningMean;
	at::Tensor* RunningVariance;

public:
	// Function to Initialize Weights and Biases
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	void InitTensors() noexcept;
	
	// Getters of various types for Gamma, Beta, RunningMean and RunningVariance
	[[nodiscard]]
	FORCEINLINE at::Tensor* GetGamma() const noexcept { return Gamma; }

	[[nodiscard]]
	FORCEINLINE at::Tensor* GetBeta() const noexcept { return Beta; }

	[[nodiscard]]
	FORCEINLINE at::Tensor* GetRunningMean() const noexcept { return RunningMean; }

	[[nodiscard]]
	FORCEINLINE at::Tensor* GetRunningVariance() const noexcept { return RunningVariance; }

	// Get Tensors as TArray<float>
	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<float> GetGammaAsFloatArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<float> GetBetaAsFloatArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<float> GetRunningMeanAsFloatArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<float> GetRunningVarianceAsFloatArray() noexcept;

	// Get Tensors as TArray<int32>
	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<int32> GetGammaAsIntArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<int32> GetBetaAsIntArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<int32> GetRunningMeanAsIntArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<int32> GetRunningVarianceAsIntArray() noexcept;

	// Get Tensors as TArray<uint8>
	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<uint8> GetGammaAsByteArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<uint8> GetBetaAsByteArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<uint8> GetRunningMeanAsByteArray() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	TArray<uint8> GetRunningVarianceAsByteArray() noexcept;

	// Setters of various types for Gamma, Beta, RunningMean, RunningVariance
	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetGammaFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<int32>(Gamma, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetBetaFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<int32>(Beta, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningMeanFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<int32>(RunningMean, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningVarianceFromIntArray(const TArray<int32>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<int32>(RunningVariance, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetGammaFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<float>(Gamma, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetBetaFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<float>(Beta, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningMeanFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<float>(RunningMean, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningVarianceFromFloatArray(const TArray<float>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<float>(RunningVariance, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetGammaFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<uint8>(Gamma, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetBetaFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<uint8>(Beta, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningMeanFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<uint8>(RunningMean, InArray, Dimensions);
	}

	UFUNCTION(BlueprintCallable, Category = "Torcher|BatchNormParams")
	FORCEINLINE void SetRunningVarianceFromByteArray(const TArray<uint8>& InArray, const TArray<int32>& Dimensions) noexcept
	{
		SetTensor<uint8>(RunningVariance, InArray, Dimensions);
	}

	virtual at::Tensor operator()(const at::Tensor& InTensor) noexcept override;

private:

	std::vector<int64_t> dims;*/
};
