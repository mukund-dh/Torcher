// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TorcherDeviceType.h"
#include "Macros/TorcherLogs.h"
#include "TorcherTensorScalarType.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END

#include "TorcherTensorBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TORCHER_API UTorcherTensorBase : public UObject
{
	GENERATED_BODY()

	// The tensor data
	TUniquePtr<at::Tensor> Data;

	// The generator, to ensure that random values we generate are consistent
	TUniquePtr<at::Generator> Generator;
	
protected:
	// The Dimensions of this tensor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torcher|Tensor Params")
	TArray<int64> Dimensions;

	// The Device Type of this tensor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Torcher|Tensor Params")
	ETorcherTensorDeviceType TensorDevice;

	// The Scalar Type of this tensor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Torcher|Tensor Params")
	ETorcherTensorScalarType TensorScalarType;

	// The Seed value for initializing the generator
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Torcher|Tensor Params")
	int64 Seed;

public:
	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UTorcherTensorBase(const FObjectInitializer& ObjectInitializer) noexcept;

protected:
	/*
	 * Does Data own a tensor, and is the tensor defined??
	 *
	 * @return bool
	 */
	FORCEINLINE bool IsDataDefined() const noexcept { return Data && Data->defined(); }
	
	/*
	 * Set Data to the at::tensor provided here
	 *
	 * @param NewTensor at::Tensor to set the Data to
	 */
	void SetData(const at::Tensor& InTensor) noexcept;

	/*
	 * Set Data to passed in TArray<T>. This is a templated function which
	 * will be used in derived classes.
	 *
	 * @param InArray Data will be set using data in this array
	 */
	template <typename T>
	void SetData(const TArray<T>& InArray) noexcept;

	/*
	 * Get Data as an at::Tensor
	 *
	 * @return The Value(s) stored in Data
	 */
	[[nodiscard]]
	FORCEINLINE at::Tensor GetData() const noexcept
	{
		// check if Data contains data
		if (IsDataDefined())
		{
			UE_LOG(LogTorcherTensor, Warning, TEXT("Data isn't defined. Skipping"));
			return at::Tensor();
		}
		return *Data;
	}

	/*
	 * Get the Data as a TArray<T>. Supported Types are currently limited to
	 *
	 * uint8
	 * int32
	 * int64
	 * float
	 * double
	 * bool
	 * undefined - this should ideally return an error.
	 *
	 * @return The Values as an array of one of the supported types
	 */
	template <typename T>
	[[nodiscard]]
	TArray<T> GetData() noexcept;

	/*
	 * Does this tensor require a gradient?
	 *
	 * @return bool
	 */
	virtual bool DoesRequireGradient() noexcept;

	/*
	 * Set requires gradient on this tensor
	 */
	virtual void SetRequiresGradient(const bool bRequiresGrad) noexcept;
	
private:
	/*
	 * Convert the given tensor to a std::vector
	 *
	 * @param InTensor The Tensor to convert
	 * @return std::vector<T>
	 */
	template <typename T>
	std::vector<T> ConvertTensorToVector(const at::Tensor& InTensor);
};
