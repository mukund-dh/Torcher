// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Activation/TorcherLayerTanHOptions.h"

FTorcherLayerTanHOptions::FTorcherLayerTanHOptions()
{
	LayerName = TEXT("TanH Layer");
	LayerDeviceType = ETorcherTensorDeviceType::Cpu;
}
