// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherRuntimeGraph.h"

void UTorcherRuntimeNode::SetLayerOptions(const FTorcherLayerBaseOptions& Options)
{
	LayerName = Options.LayerName;
	LayerDeviceType = Options.LayerDeviceType;
}

void UTorcherRuntimeNode::GetLayerOptions(FTorcherLayerBaseOptions& Options)
{
	Options.LayerName = LayerName;
	Options.LayerDeviceType = LayerDeviceType;
}
