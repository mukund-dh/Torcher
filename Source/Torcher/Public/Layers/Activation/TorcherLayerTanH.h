﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Layers/ITorcherLayer.h"
#include "Layers/Activation/TorcherLayerTanHOptions.h"
#include "TorcherLayerTanH.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher TanH Layer")
class TORCHER_API UTorcherLayerTanH : public UObject, public IITorcherLayer
{
	GENERATED_BODY()

public:
	/*
	 * The Layer Device Type
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	FTorcherLayerTanHOptions TanHLayerOptions;

	UTorcherLayerTanH(const FObjectInitializer& ObjectInitializer);

	/*
	 * Initialize the Parameters of this Layer. In this case, they are the Weights and Bias Tensors.
	 * Weights are a torch::randn, bias is a torch::zeros
	 */
	virtual void InitializeLayerParams(const float Gain = 1.0, const float Confidence = 1.0) override;

	/*
	 * Get the Parameters of this layer as an array
	 *
	 * @return An array of TorcherTensors
	 */
	virtual TArray<TScriptInterface<ITorcherTensorBase>> GetParameters() const override;

	/*
	 * Forward pass of the Linear Layer. Does a torch::matmul on Weights & the input.
	 * Adds in the bias if bUseBias is set to true.
	 *
	 * @param Input The tensor to run the forward pass with
	 * @param Output The resultant tensor of the forward pass
	 * @return Was this operation successful
	 */
	virtual bool Forward(const TScriptInterface<ITorcherTensorBase>& Input, TScriptInterface<ITorcherTensorBase>& Output) const override;

	/*
	 * Set the gradients of the Bias and Weights tensors to 0
	 *
	 * @param bSetToNone Set the gradient to none if this is set to true
	 * @return Was this operation successful?
	 */
	virtual bool SetGradientToZero(bool bSetToNone) override;

	/*
	 * Clone the Weights Tensor
	 *
	 * @param OutClone The Output cloned tensor.
	 * @param Outer The outer object of the tensor.
	 */
	virtual void CloneData(TScriptInterface<ITorcherTensorBase>& OutClone, UObject* Outer) override;

	/*
	 * Set the layer's device type, and by extension, the device type of all the parameters
	 * of this layer to provided input
	 *
	 * @param DeviceType The Tensor device type to use.
	 */
	virtual void SetLayerDeviceType(ETorcherTensorDeviceType DeviceType) override; 
};
