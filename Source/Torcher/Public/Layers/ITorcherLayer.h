// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Macros/TorcherPreProcMacros.h"
#include "Tensors/TorcherTensorBase.h"

#include "ITorcherLayer.generated.h"

struct FTorcherLayerBaseOptions;

namespace torch::nn
{
	class Module;
}

#define LOCTEXT_NAMESPACE "IITorcherLayer"

USTRUCT(BlueprintType)
struct FTorcherLayerParam
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Torcher|Layer Param")
	FName ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Torcher|Layer Param", meta = (MustImplement = "/Script/Torcher.TorcherTensorBase"))
	UObject* Tensor;

	FTorcherLayerParam() : ParamName(NAME_None), Tensor(nullptr)
	{}

	FTorcherLayerParam(FName ParameterName, UClass* TensorClass, TArray<int64> Sizes, ETorcherTensorDeviceType TensorDevice)
	{
		ParamName = ParameterName;
		Tensor = UTorcherTensorUtilities::CreateRandnTensor(TensorClass, Sizes, TensorDevice);
	}
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "Torcher Layer")
class UITorcherLayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * Network layer interface for creating deep learning ops
 */
class TORCHER_API IITorcherLayer
{
	GENERATED_BODY()

public:

	/*
	 * Initialize the parameters of this layer
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual void InitializeLayerParams() = 0;
	
	/*
	 * Return a list of parameters this layer uses.
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual TArray<FTorcherLayerParam> GetParameters() const = 0;
};

#undef LOCTEXT_NAMESPACE