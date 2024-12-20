// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tensors/TorcherDeviceType.h"
#include "TorcherTensorUtilities.generated.h"

class UTorcherTensorFloat;
class UTorcherTensorInt;
class UTorcherTensorByte;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Utilities")
class TORCHER_API UTorcherTensorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/////////// Create Empty Tensors
	
};
