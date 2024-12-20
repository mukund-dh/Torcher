// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Macros/TorcherPreProcMacros.h"
#include "Tensors/TorcherTensorBase.h"

#include "ITorcherLayer.generated.h"

struct FTorcherLayerBaseOptions;

namespace torch::nn
{
	class Module;
}

#define LOCTEXT_NAMESPACE "IITorcherLayer"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "Torcher Layer")
class UITorcherLayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * Network layer interface for creating deep learning ops
 */
class TORCHER_API IITorcherLayer
{
	GENERATED_BODY()


};

#undef LOCTEXT_NAMESPACE