// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MLP.generated.h"

class UMMTokenizer;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API UMLP : public UObject
{
	GENERATED_BODY()

	UMLP(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tokens")
	UMMTokenizer* Tokenizer;
};
