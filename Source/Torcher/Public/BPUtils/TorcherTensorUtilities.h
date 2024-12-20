// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tensors/TorcherTensorBase.h"
#include "Tensors/TorcherDeviceType.h"
#include "TorcherTensorUtilities.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "Torcher Tensor Utilities")
class TORCHER_API UTorcherTensorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Create Empty Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Empty Tensors", meta =(
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Empty Tensor",
		Keywords = "Torcher Empty Tensor Create"
	))
	static UObject* CreateEmptyTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const TArray<int64> Sizes,
		ETorcherTensorDeviceType TensorDeviceType);

	// Create Eye/Identity Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Eye Tensors", meta =(
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Identity Tensor",
		Keywords = "Torcher Eye Identity Tensor Create"
	))
	static UObject* CreateEyeTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const int64 Size,
		ETorcherTensorDeviceType TensorDeviceType);

	// Create Zero Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Zero Tensors", meta =(
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Zero Tensor",
		Keywords = "Torcher Zero Tensor Create"
	))
	static UObject* CreateZeroTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const TArray<int64> Sizes,
		ETorcherTensorDeviceType TensorDeviceType);

	// Create Ones Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Ones Tensors", meta =(
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Ones Tensor",
		Keywords = "Torcher Ones Tensor Create"
	))
	static UObject* CreateOnesTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const TArray<int64> Sizes,
		ETorcherTensorDeviceType TensorDeviceType);

	// Create Rand Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Rand Tensors", meta =(
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Random Tensor",
		Keywords = "Torcher Rand Random Tensor Create"
	))
	static UObject* CreateRandTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const TArray<int64> Sizes,
		ETorcherTensorDeviceType TensorDeviceType);

	// Create Normalized Rand Tensors
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensors", DisplayName = "Create Randn Tensors", meta =(
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Randn Tensor",
		Keywords = "Torcher Randn NormalizedRand Tensor Create"
	))
	static UObject* CreateRandnTensor(
		UPARAM(meta=(MustImplement = "/Script/Torcher.TorcherTensorBase")) const UClass* Class,
		const TArray<int64> Sizes,
		ETorcherTensorDeviceType TensorDeviceType);

	/*
	 * Blueprint function to call ITorcherTensor::ToString
	 *
	 * @param Tensor Generic Tensor Object
	 * @return The tensor as a string
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "Torcher|Tensors", DisplayName = "Tensor to String", CustomThunk, meta = (
		BlueprintAutocast,
		CompactNodeTitle = "->",
		Keywords = "Torcher Cast Tensor To String"))
	static FORCEINLINE FString Conv_TensorToString(const TScriptInterface<const ITorcherTensorBase>& Tensor)
	{ return Tensor ? Tensor->ToString() : TEXT(""); }

private:

	DECLARE_FUNCTION(execConv_TensorToString);
};
