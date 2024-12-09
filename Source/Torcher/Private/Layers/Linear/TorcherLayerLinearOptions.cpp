// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinearOptions.h"

#define LOCTEXT_NAMESPACE "TorcherLayerLinearOptions"

FTorcherLayerLinearOptions::FTorcherLayerLinearOptions()
	: InFeatures(0LL)
	, OutFeatures(0LL)
	, bBias(true)
{
}

void FTorcherLayerLinearOptions::SetFrom(const torch::nn::LinearOptions& Options)
{
	InFeatures = Options.in_features();
	OutFeatures = Options.out_features();
	bBias = Options.bias();
}

#undef LOCTEXT_NAMESPACE