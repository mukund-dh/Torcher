// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/TorcherLayerBaseOptions.h"

#include "torch/nn/module.h"

FTorcherLayerBaseOptions::FTorcherLayerBaseOptions() noexcept
	: LayerName(TEXT("UNNAMED_LAYER"))
{
}

void FTorcherLayerBaseOptions::SetLayerName(const torch::nn::Module& Module) noexcept
{
	LayerName = Module.name().c_str();
}
