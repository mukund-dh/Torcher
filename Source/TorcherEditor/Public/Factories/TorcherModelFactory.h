// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "TorcherModelFactory.generated.h"

/**
 * 
 */
UCLASS()
class TORCHEREDITOR_API UTorcherModelFactory : public UFactory
{
	GENERATED_BODY()

public:
	UTorcherModelFactory();
	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
