// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/TorcherLayerBaseOptions.h"


FTorcherLayerBaseOptions::FTorcherLayerBaseOptions()
	: LayerName(TEXT("UNNAMED_LAYER"))
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
{
}

void FTorcherLayerBaseOptions::SetLayerName(const FString& NewLayerName)
{
	LayerName = NewLayerName;
}
