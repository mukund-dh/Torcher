// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TorcherDeviceType.h"
#include "Macros/TorcherLogs.h"
#include "TorcherTensorScalarType.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END

#include "TorcherTensorBase.generated.h"

// DON'T MODIFY!!!!!
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "Torcher Tensor Base")
class UTorcherTensorBase : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TORCHER_API ITorcherTensorBase
{
	GENERATED_BODY()

	// The tensor data
	TUniquePtr<at::Tensor> Data;

	// The generator, to ensure that random values we generate are consistent
	TUniquePtr<at::Generator> Generator;
	
protected:
	// The Dimensions of this tensor
	TArray<int64> Dimensions;

	// The Device Type of this tensor
	ETorcherTensorDeviceType TensorDevice;

	// The Scalar Type of this tensor
	ETorcherTensorScalarType TensorScalarType;

	// The Seed value for initializing the generator
	int64 Seed;

	// The "label" of this tensor
	FName TensorLabel;

public:
	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	ITorcherTensorBase();
	
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
	FORCEINLINE at::Tensor* GetData() const noexcept
	{
		// check if Data contains data
		if (IsDataDefined())
		{
			UE_LOG(LogTorcherTensor, Warning, TEXT("Data isn't defined. Skipping"));
			return nullptr;
		}
		return Data.Get();
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

	/*
	 * Get the value of the Dimensions
	 */
	FORCEINLINE TArray<int64> GetDimensions() const { return Dimensions; }
	
	/*
	 * Get the value of the TorcherDeviceType
	 */
	FORCEINLINE ETorcherTensorDeviceType GetTensorDevice() const { return TensorDevice; }

	/*
	 * Get the value of the TensorScalarType
	 */
	FORCEINLINE ETorcherTensorScalarType GetTensorScalarType() const { return TensorScalarType; }

	/*
	 * Get the value of the Seed
	 */
	FORCEINLINE int64 GetSeed() const { return Seed; }

	/*
	 * Set the value of the Dimensions
	 *
	 * @param NewDimensions Array of int64 to set the dimensions to.
	 */
	FORCEINLINE void SetDimensions(const TArray<int64>& NewDimensions) { Dimensions = NewDimensions; }

	/*
	 * Set the value of the TorcherDeviceType
	 *
	 * @param NewDeviceType The type of the new torcher device
	 */
	FORCEINLINE void SetTensorDevice(ETorcherTensorDeviceType NewDeviceType) { TensorDevice = NewDeviceType; }

	/*
	 * Set the value of the TensorScalarType
	 *
	 * @param NewScalarType The type of the torcher scalar
	 */
	FORCEINLINE void SetTensorScalarType(ETorcherTensorScalarType NewScalarType) { TensorScalarType = NewScalarType; }

	/*
	 * Set the value of the Seed
	 *
	 * @param NewSeed The new seed value
	 */
	FORCEINLINE void SetSeed(int64 NewSeed) { Seed = NewSeed; }

	/*
	 * Writes this tensor as aa string inside a stream by overloading the << operator
	 *
	 * @param OutStream Output Stream
	 * @param TorcherTensor The Tensor
	 * @return The modified stream
	 */
	friend std::ostream& operator<<(std::ostream& OutStream, const ITorcherTensorBase& TorcherTensor);

	/**
	 * Writes this tensor as a string inside a stream by overloading the << operator
	 * 
	 * @param OutStream Output stream
	 * @param AtumTensor The tensor
	 * @return The modified stream
	 */
	friend std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<ITorcherTensorBase>& TorcherTensor);
	
	/*
	 * Returns a tensor as a string by overloading the FString cast operator
	 */
	[[nodiscard]]
	explicit operator FString() const;

	/*
	 * Cast this tensor to a string
	 *
	 * @return This tensor as a string
	 */
	[[nodiscard]]
	FORCEINLINE FString ToString() const { return static_cast<FString>(*this); }

	/*
	 * Set the tensor label
	 *
	 * @param NewLabel The label of the tensor
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensors")
	virtual void SetTensorLabel(const FName NewLabel) { TensorLabel = NewLabel; }

	/*
	 * Get the tensor label
	 *
	 * @return The label of the tensor
	 */
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors")
	virtual FName GetTensorLabel() const { return TensorLabel; }
	
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

template <typename T>
void ITorcherTensorBase::SetData(const TArray<T>& InArray) noexcept
{
	// Don't set the Array data if we don't have a defined scalar type.
	if (TensorScalarType == ETorcherTensorScalarType::Undefined)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Invalid Scalar Type of Tensor encountered. Skipping."));
		return;
	}
	
	// Sanity Check; first ensure that we have enough elements in the InArray to fill the tensor.
	int64 TotalElements = 1;
	for (int64 Dim : Dimensions)
	{
		TotalElements *= Dim;
	}

	if (InArray.Num() != TotalElements)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Number of elements in the InArray %d dom't match the expected number of elements %lld"), InArray.Num(), TotalElements);
		return;
	}
	
	// Get the dimensions as an std::vector<int64_t> 
	std::vector<int64_t> Dims = std::vector<int64_t>(Dimensions.GetData(), Dimensions.GetData() + Dimensions.Num());

	// Convert TArray to an std::Vector
	std::vector<T> OutVec(InArray.GetData(), InArray.GetData() + InArray.Num());

	// Set the Tensor Options dtype to the type we get from the TensorScalarType
	torch::TensorOptions TensorOptions = torch::TensorOptions().dtype(TorcherEnums::Cast(TensorScalarType));
	Data = MakeUnique<at::Tensor>(torch::from_blob(OutVec.data(), Dims, TensorOptions));
}

template <typename T>
TArray<T> ITorcherTensorBase::GetData() noexcept
{
	// check if Data contains data
	if (!IsDataDefined())
	{
		UE_LOG(LogTorcherTensor, Warning, TEXT("Data isn't defined. Skipping"));
		return TArray<T>();
	}
	
	TArray<T> OutArray;

	// Sanity Check: see if the requested type is a supported type
	if (!std::is_same_v<T, uint8> && !std::is_same_v<T, int32> &&
		!std::is_same_v<T, int64> && !std::is_same_v<T, float> &&
		!std::is_same_v<T, double> && !std::is_same_v<T, bool>)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Requested type is not a supported type."));
		return TArray<T>();
	}

	// Convert the data safely to a std::vector<T> and then pass it out to the OutArray.
	// But first, convert the tensor to a CPU tensor
	at::Tensor cpu_tensor = Data->to(torch::kCPU);
	std::vector<T> OutVec = ConvertTensorToVector<T>(cpu_tensor);
	OutArray.Append(&OutVec[0], OutVec.size());
	return OutArray;
}

template <typename T>
std::vector<T> ITorcherTensorBase::ConvertTensorToVector(const at::Tensor& InTensor)
{
	// Sanity check; Do this just in case we're called from a function without type checks
	if (!std::is_same_v<T, uint8> && !std::is_same_v<T, int32> &&
		!std::is_same_v<T, int64> && !std::is_same_v<T, float> &&
		!std::is_same_v<T, double> && !std::is_same_v<T, bool>)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Requested type is not a supported type."));
		return std::vector<T>();
	}

	return std::vector<T>(InTensor.data_ptr<T>(), InTensor.data_ptr<T>() + InTensor.numel());
}
