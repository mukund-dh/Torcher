// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TorcherTensorRetainGraphMode.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorRetainGraphMode"
/**
 * Represents what to do with the graph from the TorcherTensor::Backward method
 */
UENUM(BlueprintType, Category="Torcher|Tensor", DisplayName="Torcher Tensor Retain Graph Mode", meta=(
    Keywords="Torcher Tensor Retain Graph Mode"
))
enum class ETorcherTensorRetainGraphMode : uint8
{
	IfCreated UMETA(DisplayName="If Created"),  // Retains the graph only if it was created
	Never UMETA(DisplayName="Never"), // Never Retain the graph, even if it's created
	Always UMETA(DisplayName="Always") // Always Retain the graph, even if not created
};

#undef LOCTEXT_NAMESPACE