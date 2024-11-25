// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tensors/TorcherTensorBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Macros/TorcherPreProcMacros.h"

#include "TorchBlueprintUtilities.generated.h"

/**
 * 
 */
UCLASS()
class TORCHER_API UTorchBlueprintUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="TestFunction")
	static void TestTorchTensor(const UTorcherTensorBase* InTensor) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	static void InitTensorToRandn(UTorcherTensorBase* InTensor) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	static void InitTensorToZeros(UTorcherTensorBase* InTensor) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	static void InitTensorToOnes(UTorcherTensorBase* InTensor) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Torcher|Tensor Operations")
	static TArray<float> GetTensorAsFloatArray(UTorcherTensorBase* InTensor) noexcept;

	static std::vector<int64_t> ConvertIntArrayToVector(const TArray<int64>& InArray);
};
