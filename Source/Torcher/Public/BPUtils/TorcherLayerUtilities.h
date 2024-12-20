// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TorcherLayerUtilities.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "Torcher Layer Utilities")
class TORCHER_API UTorcherLayerUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	 * Create a new layer
	 */
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Layers", DisplayName = "Create Layer", meta =(
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Create Layer",
		Keywords = "Torcher Layer Create"
	))
	static UObject* CreateLayer(
		UPARAM(meta=(MustImplement = "/Script/Torcher.ITorcherLayer")) const UClass* Class,
		ETorcherTensorDeviceType TensorDeviceType);
};
