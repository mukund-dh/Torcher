// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TorcherGraph/TorcherRuntimeGraph.h"
#include "TorcherModelBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DisplayName = "Torcher Model Definition Base", ClassGroup = Torcher, Category = "Torcher Models")
class TORCHER_API UTorcherModelBase : public UObject
{
	GENERATED_BODY()

public:

	UTorcherModelBase(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	UTorcherRuntimeGraph* ModelGraph = nullptr;
};
