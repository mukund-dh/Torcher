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
	 *
	 * @return A list of Torcher Tensors
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual TArray<TScriptInterface<ITorcherTensorBase>> GetParameters() const = 0;

	/*
	 * Forward the Tensor through the layer's operations
	 *
	 * @param Input the tensor to operate on
	 * @param Output the resultant tensor
	 * @return Whether the Forward pass succeeded or not
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual bool Forward(const TScriptInterface<ITorcherTensorBase>& Input, TScriptInterface<ITorcherTensorBase>& Output) const = 0;

	/*
	 * Set the gradient of this tensor to 0
	 *
	 * @param bSetToNone should we set the gradient to none instead?
	 * @return was the operation successful
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual bool SetGradientToZero(bool bSetToNone = false) = 0;

	/*
	 * Set the device type of this layer. This should propagate out to any parameters this layer contains.
	 *
	 * @param DeviceType The device type to set this layer to
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual void SetLayerDeviceType(ETorcherTensorDeviceType DeviceType) = 0;

	/*
	 * Clone the data in this layer
	 *
	 * @param OutClone Cloned layer
	 * @param Outer Clone's outer object
	 */
	UFUNCTION(BlueprintCallable, Category = "Torcher|Layers")
	virtual void CloneData(TScriptInterface<ITorcherTensorBase>& OutClone, UObject* Outer = nullptr) = 0;
};

#undef LOCTEXT_NAMESPACE