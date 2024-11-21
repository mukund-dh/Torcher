// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/MLPLayerBase.h"
#include "Macros/TorcherLogs.h"


UMLPLayerBase::UMLPLayerBase(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
	, Out(nullptr)
{
}

at::Tensor UMLPLayerBase::Forward(const at::Tensor& InTensor) noexcept
{
	// Just a basic implementation that takes in the passed Tensor
	// and sets it as the OutTensor.
	SetTensor(Out, InTensor);
	return InTensor;
}

void UMLPLayerBase::SetTensor(at::Tensor*& TensorPtr, const at::Tensor& NewTensor) noexcept
{
	if (TensorPtr)
	{
		delete TensorPtr;
		TensorPtr = nullptr;
	}

	TensorPtr = new at::Tensor(NewTensor.clone());
}

template <typename T>
TArray<T> UMLPLayerBase::GetTensorAsArray(at::Tensor*& TensorPtr) noexcept
{
	TArray<T> OutVec;
	// Extract values from Out
	if (TensorPtr && TensorPtr->defined())
	{
		if (std::is_same<T, int32>::value || std::is_same<T, int64>::value ||
			std::is_same<T, float>::value || std::is_same<T, uint8>::value)
		{
			std::vector<T> WeightsVec = ConvertTensorToVector<T>(*TensorPtr);
			OutVec.Append(&WeightsVec[0], WeightsVec.size());
		}
		else
		{
			UE_LOG(LogTorcherTensor, Error, TEXT("Invalid Output Requested"));
		}
	}
	return OutVec;
}

template <typename T>
void UMLPLayerBase::SetTensor(at::Tensor*& TensorPtr, const TArray<T>& InArray, const TArray<int32>& Dimensions) noexcept
{
	if (TensorPtr)
	{
		delete TensorPtr;
		TensorPtr = nullptr;
	}

	// Get the dimensions as an std::vector<int64_t> 
	std::vector<int64_t> dims = std::vector<int64_t>(Dimensions.GetData(), Dimensions.GetData() + Dimensions.Num());

	// Convert TArray to an std::Vector
	std::vector<T> OutVec(InArray.GetData(), InArray.GetData() + InArray.Num());
	
	// Determine the type of Tensor T
	at::TensorOptions options;
	if (std::is_same<T, int32>::value || std::is_same<T, int64>::value)
	{
		options = at::TensorOptions().dtype(at::kInt).device(at::kCPU);
	}
	else if (std::is_same<T, float>::value)
	{
		options = at::TensorOptions().dtype(at::kFloat).device(at::kCPU);
	}
	else if (std::is_same<T, uint8>::value)
	{
		options = at::TensorOptions().dtype(at::kByte).device(at::kCPU);
	}
	else
	{
		UE_LOG(LogTorcherTensor, Error, TEXT("Invalid TArray Type passed"));
		return;
	}

	// Convert TArray to at::Tensor
	TensorPtr = new at::Tensor(torch::from_blob(OutVec.data(), dims, options).clone());
}

template <typename T>
std::vector<T> UMLPLayerBase::ConvertTensorToVector(const at::Tensor& InTensor)
{
	if (!std::is_same<T, int32>::value &&
		!std::is_same<T, int64>::value &&
		!std::is_same<T, float>::value &&
		!std::is_same<T, uint8>::value)
	{
		// If the requested type is none of the supported types, return an empty
		// vector of the passed type
		UE_LOG(LogTorcherTensor, Error, TEXT("Invalid TArray Type Requested!"));
		return std::vector<T>();
	}
	return std::vector<T>(InTensor.data_ptr<T>(), InTensor.data_ptr<T>() + InTensor.numel());
}
