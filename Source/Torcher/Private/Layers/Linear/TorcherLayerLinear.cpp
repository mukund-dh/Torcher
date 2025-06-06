﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinear.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorFloat.h"
#include "UObject/Package.h"

UTorcherLayerLinear::UTorcherLayerLinear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTorcherLayerLinear::InitializeLayerParams(const float Gain /*= 1.0*/, const float Confidence /*= 1.0*/)
{
	Weights = UTorcherTensorUtilities::CreateRandnTensor(
		UTorcherTensorFloat::StaticClass(),
		TorcherLinearLayerOptions.WeightsDimensions,
		TorcherLinearLayerOptions.LayerDeviceType
	);
	Weights->SetTensorLabel(TEXT("Weights"));

	// Sets the Gain of the Weights parameter to the passed value
	Weights->MultiplyByScalar(Gain);
	
	// Sets the Confidence of the Weights parameter to the passed value
	Weights->MultiplyByScalar(Confidence);

	Bias = nullptr;
	if (TorcherLinearLayerOptions.bUseBias)
	{
		Bias = UTorcherTensorUtilities::CreateZeroTensor(
			UTorcherTensorFloat::StaticClass(),
			TorcherLinearLayerOptions.BiasDimensions,
			TorcherLinearLayerOptions.LayerDeviceType
		);
		Bias->SetTensorLabel(TEXT("Bias"));

		// Sets the Confidence of the Bias parameter to the passed value
		Bias->MultiplyByScalar(Confidence);
	}
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
	if (TorcherLinearLayerOptions.bUseBias)
	{
		OutTensor = OutTensor.add(*Bias->GetData());
	}
	
	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TorcherLinearLayerOptions.LayerDeviceType);
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

	if (Bias != nullptr && Bias->GetData()->grad().defined())
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
	TorcherLinearLayerOptions.LayerDeviceType = DeviceType;
	Weights->SetTensorDevice(DeviceType);
	if (TorcherLinearLayerOptions.bUseBias && Bias != nullptr)
		Bias->SetTensorDevice(DeviceType);
}
