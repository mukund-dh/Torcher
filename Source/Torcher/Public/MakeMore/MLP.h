// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tensors/TorcherTensorFloat.h"
#include "MLP.generated.h"

class UMMTokenizer;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API UMLP : public UObject
{
	GENERATED_BODY()

public:

	UE_NODISCARD_CTOR
	UMLP(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tokens")
	UMMTokenizer* Tokenizer;

	UPROPERTY(BlueprintReadWrite, Category = "Tokens")
	UTorcherTensorFloat* FloatTensor;

	UFUNCTION(BlueprintCallable, Category = "Tensors")
	void InitTensors() noexcept;
};
