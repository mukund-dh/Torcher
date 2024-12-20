// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TorcherModelBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DisplayName = "Torcher Model Definition Base")
class TORCHER_API UTorcherModelBase : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(Transient, NonTransactional)
	mutable TArray<const UClass*> LayerTypesConst;

protected:
	// List of layer types
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = "GetLayerTypes", meta = (AllowPrivateAccess, MustImplement = "/Script/Torcher.ITorcherLayer"))
	TArray<TObjectPtr<const UClass>> LayerTypes;

public:
	// Get a list of layer types
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Layer Types"))
	const TArray<const UClass*>& GetLayerTypes() const;

private:
	DECLARE_FUNCTION(execGetLayerTypes);
};
