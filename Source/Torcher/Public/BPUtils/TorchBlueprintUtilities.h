// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/generated/variable_factories.h>
TORCH_INCLUDES_END

#include "TorchBlueprintUtilities.generated.h"


//struct Net : torch::nn::Module
//{
//	Net()
//	{
//		// Construct and register two linear submodules
//	}
//};

/**
 * 
 */
UCLASS()
class TORCHER_API UTorchBlueprintUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:

	

public:

	UFUNCTION(BlueprintCallable, Category="TestFunction")
	static void TestTorchTensor() noexcept;
	
};
