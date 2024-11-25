// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tensors/TorcherTensorBase.h"
#include "TorcherTensorFloat.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorFloat"

/**
 * Tensor with a scalar type of float
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Float")
class TORCHER_API UTorcherTensorFloat : public UTorcherTensorBase
{
	GENERATED_BODY()

public:

	// Constructor
	UE_NODISCARD_CTOR
	UTorcherTensorFloat(const FObjectInitializer& ObjectInitializer) noexcept;

protected:
	// BP Function to get values and sizes of this tensor
	UFUNCTION(BlueprintPure, Category="Torcher|Tensor", DisplayName = "Get Values(Float)", meta = (
		Keywords = "Torcher Tensor Float float Get Value Sizes"))
	FORCEINLINE void K2_GetValues(TArray<float>& OutValues, TArray<int64>& OutSizes) noexcept
	{
		OutValues = GetData<float>();
		OutSizes = GetDimensions();
	}

	// Blueprint Function to set the values and sizes of this tensor
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor", DisplayName = "Set Values(Float)", meta = (
		Keywords = "Torcher Tensor Float float Set Value Sizes"))
	FORCEINLINE void K2_SetValues(const TArray<float>& Values, const TArray<int64>& Sizes) noexcept
	{
		SetData<float>(Values);
	}
};

#undef LOCTEXT_NAMESPACE