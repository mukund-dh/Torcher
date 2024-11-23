// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorBase.h"

UTorcherTensorBase::UTorcherTensorBase(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
	, Data(nullptr)
	, Generator(nullptr)
	, TensorDevice(ETorcherTensorDeviceType::Cpu)
	, TensorScalarType(ETorcherTensorScalarType::Undefined)
	, Seed(2147483647)
{
}

void UTorcherTensorBase::SetData(const at::Tensor& InTensor) noexcept
{
	// Set the TensorScalarType to the appropriate type if it's undefined
	if (TensorScalarType == ETorcherTensorScalarType::Undefined)
	{
		TensorScalarType = TorcherEnums::Cast(InTensor.scalar_type());
		// if it's still undefined then skip the SetData
		if (TensorScalarType == ETorcherTensorScalarType::Undefined)
		{
			UE_LOG(LogTorcherTensor, Error, TEXT("Invalid Scalar Type of Tensor encountered. Skipping."));
			return;
		}
	}
	
	if (TorcherEnums::Cast(InTensor.device().type()) != TensorDevice)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Device Type Mismatch between Data and InTensor. Please check."));
		return;
	}
	
	// Make sure that the Tensor Scalar Type from the InTensor matches our scalar type.
	Data.Reset(new at::Tensor(InTensor.to(TorcherEnums::Cast(TensorScalarType)).clone()));

	// Ensure that the now set tensor's sizes are also set to the Dimensions array
	Dimensions.Empty();
	Dimensions.Reserve(InTensor.sizes().size());
	for (const auto& Size : InTensor.sizes())
	{
		Dimensions.Add(static_cast<int64>(Size));
	}
}

bool UTorcherTensorBase::DoesRequireGradient() noexcept
{
	return Data && Data->requires_grad();
}

void UTorcherTensorBase::SetRequiresGradient(const bool bRequiresGrad) noexcept
{
	if (Data)
	{
		SetData(Data->set_requires_grad(bRequiresGrad));
	}
}

template <typename T>
void UTorcherTensorBase::SetData(const TArray<T>& InArray) noexcept
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
TArray<T> UTorcherTensorBase::GetData() noexcept
{
	// check if Data contains data
	if (IsDataDefined())
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
	std::vector<T> OutVec = ConvertTensorToVector<T>(Data->data());
	OutArray.Append(&OutVec[0], OutVec.size());
	return OutArray;
}

template <typename T>
std::vector<T> UTorcherTensorBase::ConvertTensorToVector(const at::Tensor& InTensor)
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
