﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorBase.h"
#include "UObject/Package.h"

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

bool ITorcherTensorBase::IsBroadcastableWith(const TScriptInterface<ITorcherTensorBase>& BroadcastTensor) const
{
	if (!IsDataDefined() || BroadcastTensor == nullptr || !BroadcastTensor->IsDataDefined())
		return false;

	const int32 DimsCount = GetDimensions().Num();
	TArray<int64> BroadcastDims = BroadcastTensor->GetDimensions();
	int32 BroadcastDimsCount = BroadcastDims.Num();

	if (DimsCount < BroadcastDimsCount)
		return BroadcastTensor->IsBroadcastableWith(_getUObject());

	while (DimsCount != BroadcastDimsCount)
	{
		BroadcastDims.Insert(1LL, 0);
		++BroadcastDimsCount;
	}

	for (int32 Index = DimsCount - 1; Index >= 0; --Index)
	{
		const int32 BroadcastSize = BroadcastDims[Index];
		if (
			const int32 Size = GetDimensions()[Index];
			Size == 0LL || BroadcastSize == 0LL || (Size != BroadcastSize && Size != 1LL && BroadcastSize != 1LL)
			)
			return false;
	}

	return true;
}

bool ITorcherTensorBase::BroadcastTo(const TScriptInterface<ITorcherTensorBase>& BroadcastTensor) const
{
	if (!IsBroadcastableWith(BroadcastTensor))
		return false;

	TArray<int64> BroadcastDims = BroadcastTensor->GetDimensions();

	const int64* const SizeData = BroadcastDims.GetData();
	*Data = at::broadcast_to(*Data, at::IntArrayRef(SizeData, SizeData + BroadcastDims.Num()));
	return true;
}

void ITorcherTensorBase::Detach(TScriptInterface<ITorcherTensorBase>& OutDetachedTensor) const
{
	if (OutDetachedTensor = IsDataDefined() ? DuplicateObject(_getUObject(), nullptr) : nullptr; OutDetachedTensor)
	{
		OutDetachedTensor->SetData(Data->detach());
	}
}

void ITorcherTensorBase::GetGradient(TScriptInterface<ITorcherTensorBase>& OutGradient) const
{
	if (OutGradient = IsDataDefined() ? DuplicateObject(_getUObject(), nullptr) : nullptr; OutGradient)
	{
		OutGradient->SetData(Data->grad());
	}
}

TScriptInterface<ITorcherTensorBase> ITorcherTensorBase::SetGradientToZero() const
{
	at::Tensor ZeroTensor = GetData()->mutable_grad().zero_();

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(GetTensorDevice());
	Tensor->SetData(ZeroTensor);
	return TensorObject;
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
