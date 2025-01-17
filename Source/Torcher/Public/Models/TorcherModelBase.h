// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TorcherGraph/TorcherRuntimeGraph.h"

#include <functional>

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

public:
	// Our Interface
	void SetPreSaveListener(std::function<void()> OnPreSaveListener) { _onPreSaveListener = OnPreSaveListener; }

public:
	// UObject Interface
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
private:
	// Members
	std::function<void()> _onPreSaveListener = nullptr;
	
};
