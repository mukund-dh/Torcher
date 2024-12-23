// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorBase.h"

ITorcherTensorBase::ITorcherTensorBase()
	: Data(nullptr)
	, Generator(nullptr)
	, TensorDevice(ETorcherTensorDeviceType::Cpu)
	, TensorScalarType(ETorcherTensorScalarType::Undefined)
	, Seed(2147483647)
	, TensorLabel(NAME_None)
{
}

void ITorcherTensorBase::SetData(const at::Tensor& InTensor) noexcept
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

bool ITorcherTensorBase::DoesRequireGradient() noexcept
{
	return Data && Data->requires_grad();
}

void ITorcherTensorBase::SetRequiresGradient(const bool bRequiresGrad) noexcept
{
	if (Data)
	{
		SetData(Data->set_requires_grad(bRequiresGrad));
	}
}

ITorcherTensorBase::operator FString() const
{
	std::ostringstream Stream;
	Stream << *this;
	return Stream.str().c_str();
}

std::ostream& operator<<(std::ostream& OutStream, const ITorcherTensorBase& TorcherTensor)
{
	if (const at::Tensor* const Tensor = TorcherTensor.Data.Get())
	{
		OutStream << *Tensor;
	}
	return OutStream;
}

std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<const ITorcherTensorBase>& TorcherTensor)
{
	if (const ITorcherTensorBase* const Interface = TorcherTensor.GetInterface())
	{
		OutStream << *Interface;
	}
	return OutStream;
}
