// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tensors/TorcherTensorBase.h"
#include "TorcherTensorByte.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorByte"

/**
 * Torcher Tensor with a scalar type of bytes
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Byte")
class TORCHER_API UTorcherTensorByte : public UObject, public ITorcherTensorBase
{
	GENERATED_BODY()
public:

	// Constructor
	UE_NODISCARD_CTOR
	UTorcherTensorByte(const FObjectInitializer& ObjectInitializer) noexcept;

protected:
	// BP Function to get values and sizes of this tensor
	UFUNCTION(BlueprintPure, Category="Torcher|Tensor", DisplayName = "Get Values(uint8)", meta = (
		Keywords = "Torcher Tensor Byte uint8 Get Value Sizes"))
	FORCEINLINE void K2_GetValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) noexcept
	{
		OutValues = GetData<uint8>();
		OutSizes = GetDimensions();
	}

	// Blueprint Function to set the values and sizes of this tensor
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor", DisplayName = "Set Values(Byte)", meta = (
		Keywords = "Torcher Tensor Byte uint8 Set Value Sizes"))
	FORCEINLINE void K2_SetValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept
	{
		SetData<uint8>(Values);
	}
};

#undef LOCTEXT_NAMESPACE