// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Macros/TorcherPreProcMacros.h"
#include "Tensors/TorcherTensorBase.h"

#include "ITorcherLayer.generated.h"

namespace torch::nn
{
	class Module;
}

#define LOCTEXT_NAMESPACE "IITorcherLayer"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "Torcher Layer")
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

protected:

	bool bInitialized;

	ETorcherTensorDeviceType LayerDeviceType;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UE_NODISCARD_CTOR
	IITorcherLayer() noexcept;

	/*
	 * Set the libtorch device type for this layer
	 *
	 * @param NewDeviceType The new device type to use. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Torcher|Layer Operations")
	void SetLayerDeviceType(ETorcherTensorDeviceType NewDeviceType);

	/*
	 * Sets the layer's gradient to zero
	 *
	 * @param bSetToZero If true, will set the gradient to zero.
	 * @return Has the gradient been set to 0?
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Torcher|Layer Operations")
	bool SetGradientToZero(bool bSetToZero = true);

	/*
	 * Execute the forward pass on the input and populate the output
	 *
	 * @param InTensor The tensor to run the forward pass calculations on
	 * @param OutTensor The result of the forward pass on the InTensor
	 * @return Has the Forward pass succeeded?
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Torcher|Layer Operations")
	bool Forward(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor);

	/*
	 * Overload the () operator, and execute the forward pass when invoked
	 *
	 * @param InTensor The tensor to run the forward pass calculations on
	 * @param OutTensor The result of the forward pass on the InTensor
	 * @return Has the Forward pass succeeded?
	 */
	FORCEINLINE bool operator()(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor)
	{
		return Execute_Forward(_getUObject(), InTensor, OutTensor);
	}

	/*
	 * Gets this layer's current parameters
	 *
	 * @param Class Type of tensor implementation to use
	 * @param OutValues Array of all parameters
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Torcher|Layer Operations")
	void GetParameters(
		const UClass* Class,
		TMap<FString, UTorcherTensorBase*>& OutValues) const;

	/*
	 * Getter for Module as its base class
	 */
	[[nodiscard]]
	virtual const torch::nn::Module* GetBaseModule() const noexcept;

	/*
	 * Getter for Module as its base class
	 */
	[[nodiscard]]
	FORCEINLINE torch::nn::Module* GetBaseModule() noexcept
	{ return const_cast<torch::nn::Module*>(std::as_const(*this).GetBaseModule()); }

	/*
	 * Set the layer's base module using a base module
	 */
	virtual void SetBaseModule(torch::nn::Module* Value) noexcept;

protected:
	/*
	 * Function that runs when IITorcherLayer::Forward is called
	 *
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Torcher|Layer Operations")
	bool OnForward(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor);

	virtual bool OnForward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor) noexcept;
private:

	virtual void SetLayerDeviceType_Implementation(ETorcherTensorDeviceType NewDeviceType);
	
	virtual bool SetGradientToZero_Implementation(bool SetToZero = true);
	
	virtual bool Forward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor);

	virtual void GetParameters_Implementation(const UClass* Class, TMap<FString, UTorcherTensorBase*>& OutValues) const;
};

#undef LOCTEXT_NAMESPACE