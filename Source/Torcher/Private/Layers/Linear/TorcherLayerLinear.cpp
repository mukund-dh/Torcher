// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinear.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorFloat.h"
#include "UObject/Package.h"

UTorcherLayerLinear::UTorcherLayerLinear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
	, WeightsDims(TArray<int64>{4, 4})
	, bUseBias(true)
{
	// Set the bias to the last dimension in the weights
	BiasDims = {WeightsDims.Last()};
}

void UTorcherLayerLinear::InitializeLayerParams()
{
	Weights = UTorcherTensorUtilities::CreateRandnTensor(UTorcherTensorFloat::StaticClass(), WeightsDims, LayerDeviceType);
	Weights->SetTensorLabel(TEXT("Weights"));

	Bias = UTorcherTensorUtilities::CreateZeroTensor(UTorcherTensorFloat::StaticClass(), BiasDims, LayerDeviceType);
	Bias->SetTensorLabel(TEXT("Bias"));
}

TArray<TScriptInterface<ITorcherTensorBase>> UTorcherLayerLinear::GetParameters() const
{
	TArray<TScriptInterface<ITorcherTensorBase>> Params;
	Params.Add(Weights);
	Params.Add(Bias);
	return Params;
}

bool UTorcherLayerLinear::Forward(const TScriptInterface<ITorcherTensorBase>& Input,
	TScriptInterface<ITorcherTensorBase>& Output) const
{
	bool bIsBroadcastable = Weights->IsBroadcastableWith(Input);
	if (!bIsBroadcastable)
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("The provided input is not broadcastable with wieghts."));
		return false;
	}
	
	at::Tensor OutTensor = torch::matmul(*Input->GetData(), *Weights->GetData());
	if (bUseBias)
	{
		OutTensor = OutTensor.add(*Bias->GetData());
	}
	
	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(LayerDeviceType);
	Tensor->SetData(OutTensor);

	Output = TensorObject;
	return true;
}

bool UTorcherLayerLinear::SetGradientToZero(bool bSetToNone)
{
	if (Weights->GetData()->grad().defined())
	{
		Weights->SetGradientToZero();
	}

	if (Bias->GetData()->grad().defined())
	{
		Bias->SetGradientToZero();
	}
	return true;
}

void UTorcherLayerLinear::CloneData(TScriptInterface<ITorcherTensorBase>& OutClone, UObject* Outer)
{
}

void UTorcherLayerLinear::SetLayerDeviceType(ETorcherTensorDeviceType DeviceType)
{
	LayerDeviceType = DeviceType;
	Weights->SetTensorDevice(DeviceType);
	Bias->SetTensorDevice(DeviceType);
}
