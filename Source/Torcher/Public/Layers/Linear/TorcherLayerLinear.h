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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Linear Layer|Params")
	FTorcherLayerParam Weights;

	virtual void InitializeLayerParams() override;
	virtual TArray<FTorcherLayerParam> GetParameters() const override;
};
