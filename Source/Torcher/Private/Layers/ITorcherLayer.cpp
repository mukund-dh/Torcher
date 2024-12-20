// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/ITorcherLayer.h"

#include "Tensors/TorcherDeviceType.h"
#include "Tensors/TorcherTensorByte.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Tensors/TorcherTensorInt.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END

#define LOCTEXT_NAMESPACE "IITorcherLayer"

// Add default functionality here for any IITorcherLayer functions that are not pure virtual.
IITorcherLayer::IITorcherLayer() noexcept
	: bInitialized(false)
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
{
}

bool IITorcherLayer::OnForward_Implementation(const UTorcherTensorBase* InTensor,
	UTorcherTensorBase*& OutTensor)
{
	OutTensor = DuplicateObject(InTensor, nullptr);
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnForward is not implemented in: `%ls`"),
		*GetNameSafe(_getUObject()->GetClass()))));
}

bool IITorcherLayer::OnInitializeData_Implementation()
{
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnInitializeData is not implemented in: `%ls`"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
}

bool IITorcherLayer::InitializeData_Implementation()
{
	if (bInitialized)
		// The layer is already initialized
		return true;
	
	bInitialized = true;
	return bInitialized;
}

void IITorcherLayer::SetLayerDeviceType_Implementation(ETorcherTensorDeviceType NewDeviceType)
{
	LayerDeviceType = NewDeviceType;
}

bool IITorcherLayer::SetGradientToZero_Implementation(bool bSetToZero)
{
	return true;
}

bool IITorcherLayer::Forward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor)
{
	return true;
}

void IITorcherLayer::GetParameters_Implementation(const UClass* Class,
	TMap<FString, UTorcherTensorBase*>& OutValues) const
{
	
}


#undef LOCTEXT_NAMESPACE