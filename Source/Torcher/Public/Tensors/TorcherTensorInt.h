// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tensors/TorcherTensor.h"
#include "TorcherTensorInt.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorInt"

/**
 * Tensor with a scalar type of Integer
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Int")
class TORCHER_API UTorcherTensorInt : public UObject, public ITorcherTensor, public TTorcherSensor<int32>
{
	GENERATED_BODY()

public:

	// Constructor
	UE_NODISCARD_CTOR
	UTorcherTensorInt() noexcept;

protected:
	// BP Function to get values and sizes of this tensor
	UFUNCTION(BlueprintPure, Category="Torcher|Tensor", DisplayName = "Get Values(Int)", meta = (
		Keywords = "Torcher Tensor Int int32 Get Value Sizes"))
	FORCEINLINE void K2_GetValues(TArray<int32>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	// Blueprint Function to set the values and sizes of this tensor
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor", DisplayName = "Set Values(Int)", meta = (
		Keywords = "Torcher Tensor Int int32 Set Value Sizes"))
	FORCEINLINE void K2_SetValues(const TArray<int32>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE