// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Activation/TorcherLayerTanH.h"
#include "Tensors/TorcherTensorFloat.h"
#include "UObject/Package.h"

UTorcherLayerTanH::UTorcherLayerTanH(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTorcherLayerTanH::InitializeLayerParams(const float Gain, const float Confidence)
{
}

TArray<TScriptInterface<ITorcherTensorBase>> UTorcherLayerTanH::GetParameters() const
{
	return TArray<TScriptInterface<ITorcherTensorBase>>();
}

bool UTorcherLayerTanH::Forward(const TScriptInterface<ITorcherTensorBase>& Input,
	TScriptInterface<ITorcherTensorBase>& Output) const
{
	at::Tensor InputTensor = *Input->GetData();
	at::Tensor OutTensor = torch::tanh(InputTensor);

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TanHLayerOptions.LayerDeviceType);
	Tensor->SetData(OutTensor);

	Output = TensorObject;
	return true;
}

bool UTorcherLayerTanH::SetGradientToZero(bool bSetToNone)
{
	return false;
}

void UTorcherLayerTanH::CloneData(TScriptInterface<ITorcherTensorBase>& OutClone, UObject* Outer)
{
}

void UTorcherLayerTanH::SetLayerDeviceType(ETorcherTensorDeviceType DeviceType)
{
	TanHLayerOptions.LayerDeviceType = DeviceType;
}

