// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinearOptions.h"

FTorcherLayerLinearOptions::FTorcherLayerLinearOptions()
{
	LayerName = TEXT("Linear Layer");
	LayerDeviceType = ETorcherTensorDeviceType::Cpu;
	WeightsDimensions = TArray<int64>{4, 4};
	BiasDimensions = TArray<int64>{WeightsDimensions.Last()};
	bUseBias = true;
}
