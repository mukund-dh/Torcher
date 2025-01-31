// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Activation/TorcherLayerTanHOptions.h"

FTorcherLayerTanHOptions::FTorcherLayerTanHOptions()
{
	LayerType = ETorcherNodeType::TanH;
	LayerName = TEXT("TanH Layer");
	LayerDeviceType = ETorcherTensorDeviceType::Cpu;
}
