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

UTorcherTensorBase::~UTorcherTensorBase()
{
}

void UTorcherTensorBase::SetData(const at::Tensor& InTensor) noexcept
{
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
	if (!std::is_same<T, uint8>::value && !std::is_same<T, int32>::value &&
		!std::is_same<T, int64>::value && !std::is_same<T, float>::value &&
		!std::is_same<T, double>::value && !std::is_same<T, bool>::value)
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
	if (!std::is_same<T, uint8>::value && !std::is_same<T, int32>::value &&
		!std::is_same<T, int64>::value && !std::is_same<T, float>::value &&
		!std::is_same<T, double>::value && !std::is_same<T, bool>::value)
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Requested type is not a supported type."));
		return std::vector<T>();
	}

	return std::vector<T>(InTensor.data_ptr<T>(), InTensor.data_ptr<T>() + InTensor.numel());
}
