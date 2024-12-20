// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinear.h"
#include "Tensors/TorcherTensorFloat.h"

UTorcherLayerLinear::UTorcherLayerLinear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTorcherLayerLinear::InitializeLayerParams()
{
	Weights = FTorcherLayerParam(TEXT("Weights"), UTorcherTensorFloat::StaticClass(), TArray<int64>{4, 4}, ETorcherTensorDeviceType::Cpu);
}

TArray<FTorcherLayerParam> UTorcherLayerLinear::GetParameters() const
{
	TArray<FTorcherLayerParam> Params;
	Params.Add(Weights);
	return Params;
}
