// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Layers/ITorcherLayer.h"
#include "TorcherLayerLinear.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "Torcher Linear Layer")
class TORCHER_API UTorcherLayerLinear : public UObject, public IITorcherLayer
{
	GENERATED_BODY()

public:

	UE_NODISCARD_CTOR
	UTorcherLayerLinear(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Linear Layer|Params")
	ETorcherTensorDeviceType LayerDeviceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Linear Layer|Params")
	TScriptInterface<ITorcherTensorBase> Weights;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Linear Layer|Params")
	TArray<int64> WeightsDims;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Linear Layer|Params")
	TScriptInterface<ITorcherTensorBase> Bias;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Linear Layer|Params")
	TArray<int64> BiasDims;

	virtual void InitializeLayerParams() override;
	virtual TArray<TScriptInterface<ITorcherTensorBase>> GetParameters() const override;
};
