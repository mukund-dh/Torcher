// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Normalization/TorcherLayerBatchNorm1DOptions.h"

FTorcherLayerBatchNorm1DOptions::FTorcherLayerBatchNorm1DOptions()
{
	LayerType = ETorcherNodeType::BatchNorm1D;
	LayerName = TEXT("BatchNorm1D Layer");
	LayerDeviceType = ETorcherTensorDeviceType::Cpu;
	Eps = 0.00001f;
	Dimensions = 4;
	Momentum = 0.1f;
	bIsTraining = true;
}
