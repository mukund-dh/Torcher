// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tensors/TorcherTensor.h"
#include "TorcherTensorFloat.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorFloat"

/**
 * Tensor with a scalar type of float
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Float")
class TORCHER_API UTorcherTensorFloat : public UObject, public ITorcherTensor, public TTorcherSensor<float>
{
	GENERATED_BODY()

public:

	// Constructor
	UE_NODISCARD_CTOR
	UTorcherTensorFloat() noexcept;

protected:
	// BP Function to get values and sizes of this tensor
	UFUNCTION(BlueprintPure, Category="Torcher|Tensor", DisplayName = "Get Values(Float)", meta = (
		Keywords = "Torcher Tensor Float float Get Value Sizes"))
	FORCEINLINE void K2_GetValues(TArray<float>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	// Blueprint Function to set the values and sizes of this tensor
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor", DisplayName = "Set Values(Float)", meta = (
		Keywords = "Torcher Tensor Float float Set Value Sizes"))
	FORCEINLINE void K2_SetValues(const TArray<float>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE