// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinear.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorFloat.h"

UTorcherLayerLinear::UTorcherLayerLinear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
	, WeightsDims(TArray<int64>{4, 4})
	, BiasDims(TArray<int64>{4})
{
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
	return Params;
}
