// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/ITorcherLayer.h"

#include "Tensors/TorcherDeviceType.h"
#include "Tensors/TorcherTensorByte.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Tensors/TorcherTensorInt.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END

#define LOCTEXT_NAMESPACE "IITorcherLayer"



#undef LOCTEXT_NAMESPACE