// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/MLPLayerBase.h"
#include "Macros/TorcherLogs.h"


UMLPLayerBase::UMLPLayerBase(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
{
	Out = NewObject<UTorcherTensorFloat>();
	Out->SetTensorDevice(ETorcherTensorDeviceType::Cuda);
}
