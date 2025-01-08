// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Layers/ITorcherLayer.h"
#include "TorcherLayerBatchNorm1D.generated.h"

/**
 * 
 */
UCLASS()
class TORCHER_API UTorcherLayerBatchNorm1D : public UObject, public IITorcherLayer
{
	GENERATED_BODY()
};
