// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "TorcherRuntimeGraph.generated.h"

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
	UTorcherRuntimePin* InputPin;

	UPROPERTY()
	TArray<UTorcherRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Location;
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
