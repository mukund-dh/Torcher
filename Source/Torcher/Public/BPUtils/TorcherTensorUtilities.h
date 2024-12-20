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
	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Empty")
	static UTorcherTensorFloat* CreateEmptyFloatTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Empty")
	static UTorcherTensorInt* CreateEmptyIntTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Empty")
	static UTorcherTensorByte* CreateEmptyByteTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	/////////// Create randn Tensors
	/// Only contains a float tensor (as there's no point in supporting int/byte/bool tensors
	/// double support will come later
	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Randn")
	static UTorcherTensorFloat* CreateRandnFloatTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	/////////// Create rand Tensors
	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Rand")
	static UTorcherTensorFloat* CreateRandFloatTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Rand")
	static UTorcherTensorInt* CreateRandIntTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

	UFUNCTION(BlueprintCallable, Category = "Torcher|Create Tensor|Rand")
	static UTorcherTensorByte* CreateRandByteTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType);

};
