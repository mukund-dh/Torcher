﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherRuntimeGraph.generated.h"

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

/**
 * Holds data for runtime pin generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimePin : public UObject
{
    GENERATED_BODY()
public:
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinId;

	UPROPERTY()
	UTorcherRuntimePin* Connection = nullptr;
};

/**
 * Holds data for runtime node generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimeNode : public UObject
{
    GENERATED_BODY()

public:
	UPROPERTY()
	ETorcherNodeType NodeType = ETorcherNodeType::Default;
	
	UPROPERTY()
	UTorcherRuntimePin* InputPin;

	UPROPERTY()
	TArray<UTorcherRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Location;

	UPROPERTY()
	FString LayerName;

	UPROPERTY()
	ETorcherTensorDeviceType LayerDeviceType;

	virtual void SetLayerOptions(const FTorcherLayerBaseOptions& Options);
	
	virtual void GetLayerOptions(FTorcherLayerBaseOptions& Options);
};

/**
 * Holds data for runtime graph generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UTorcherRuntimeNode*> GraphNodes;
};
