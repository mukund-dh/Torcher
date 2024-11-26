// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/ITorcherLayer.h"
#include "Tensors/TorcherDeviceType.h"
#include "Tensors/TorcherTensorByte.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Tensors/TorcherTensorInt.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END

// Add default functionality here for any IITorcherLayer functions that are not pure virtual.
IITorcherLayer::IITorcherLayer() noexcept
	: LayerDeviceType(ETorcherTensorDeviceType::Cpu)
{
}

void IITorcherLayer::SetBaseModule(torch::nn::Module* Value) noexcept
{
}

void IITorcherLayer::SetLayerDeviceType_Implementation(ETorcherTensorDeviceType NewDeviceType)
{
	LayerDeviceType = NewDeviceType;
}

bool IITorcherLayer::SetGradientToZero_Implementation(bool bSetToZero)
{
	torch::nn::Module* const BaseModule = GetBaseModule();
	if (BaseModule == nullptr)
		return false;

	BaseModule->zero_grad(bSetToZero);
	return true;
}

bool IITorcherLayer::Forward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor)
{
	return false;
}

void IITorcherLayer::GetParameters_Implementation(const UClass* Class,
	TMap<FString, UTorcherTensorBase*>& OutValues) const
{
	const torch::nn::Module* BaseModule = GetBaseModule();
	if (BaseModule == nullptr)
		return;

	for (const torch::OrderedDict<std::string, at::Tensor>::Item& Parameter : BaseModule->named_parameters())
	{
		const at::Tensor& Value = Parameter.value();
		if (!Value.defined())
			continue;

		ETorcherTensorScalarType TensorScalarType = TorcherEnums::Cast(Value.scalar_type());
		if (TensorScalarType == ETorcherTensorScalarType::Undefined)
		{
			UE_LOG(LogTorcherLayer, Warning, TEXT("Incompatible Tensor. Skipping"));
			continue;
		}

		if (TensorScalarType == ETorcherTensorScalarType::Int)
		{
			UTorcherTensorInt* IntTensor = NewObject<UTorcherTensorInt>();
			IntTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(IntTensor));
		}
		else if (TensorScalarType == ETorcherTensorScalarType::Float)
		{
			UTorcherTensorFloat* FloatTensor = NewObject<UTorcherTensorFloat>();
			FloatTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(FloatTensor));
		}
		else if (TensorScalarType == ETorcherTensorScalarType::Byte)
		{
			UTorcherTensorByte* ByteTensor = NewObject<UTorcherTensorByte>();
			ByteTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(ByteTensor));
		}
		else
		{
			UE_LOG(LogTorcherLayer, Warning, TEXT("Tensors of type long, double and bool haven't been implemented yet."));
			continue;
		}
	}
}

const torch::nn::Module* IITorcherLayer::GetBaseModule() const noexcept
{
	return nullptr;
}