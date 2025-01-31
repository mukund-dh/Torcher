// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "TorcherTypes.generated.h"

UENUM()
enum class ETorcherNodeType
{
	// The Start Node
	Input,

	Default, // The default node type which gets created when the graph is initialized

	// Linear Layer
	Linear,

	// Normalization Layers
	BatchNorm1D,

	// Activation Layers
	TanH,

	// The End Node
	Output
};