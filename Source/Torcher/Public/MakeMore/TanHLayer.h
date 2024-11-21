// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MakeMore/MLPLayerBase.h"
#include "TanHLayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API UTanHLayer : public UMLPLayerBase
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UTanHLayer(const FObjectInitializer& ObjectInitializer);
	
	// Overridden Forward
	virtual at::Tensor Forward(const at::Tensor& InTensor) noexcept override;
};
