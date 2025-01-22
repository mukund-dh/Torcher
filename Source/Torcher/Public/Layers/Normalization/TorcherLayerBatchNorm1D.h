// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Layers/ITorcherLayer.h"
#include "TorcherLayerBatchNorm1DOptions.h"
#include "TorcherLayerBatchNorm1D.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher BatchNorm1D Layer")
class TORCHER_API UTorcherLayerBatchNorm1D : public UObject, public IITorcherLayer
{
	GENERATED_BODY()

public:
	/*
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UTorcherLayerBatchNorm1D(const FObjectInitializer& ObjectInitializer);

	/*
	 * The Gamma Tensor. Parameters of the layer.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	TScriptInterface<ITorcherTensorBase> Gamma;

	/*
	 * The Beta Tensor. Parameters of the layer.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	TScriptInterface<ITorcherTensorBase> Beta;

	/*
	 * The Running Mean Tensor. Part of buffers, trained with running momentum update.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	TScriptInterface<ITorcherTensorBase> RunningMean;

	/*
	 * The Running Variance Tensor. Part of buffers, trained with running momentum update.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatchNorm1D Layer|Params")
	TScriptInterface<ITorcherTensorBase> RunningVariance;

	/*
	 * The BatchNorm1D Options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layers|BatchNorm1D Params")
	FTorcherLayerBatchNorm1DOptions TorcherLayerBatchNorm1DOptions;
	
	/*
	 * Initialize the Parameters of this Layer. In this case, they are the Weights and Bias Tensors.
	 * Weights are a torch::randn, bias is a torch::zeros
	 * @param Gain The amount of gain to apply to this layer
	 * @param Confidence Manipulates the confidence of this layer
	 * 
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
