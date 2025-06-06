﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BPUtils/TorcherLayerUtilities.h"
#include "UObject/Package.h"
#include "Layers/ITorcherLayer.h"

UObject* UTorcherLayerUtilities::CreateLayer(const UClass* Class, ETorcherTensorDeviceType TensorDeviceType, const float Gain, const float Confidence)
{
	check(Class && Class->ImplementsInterface(UITorcherLayer::StaticClass()));
       auto* const TorcherLayerObject = NewObject<UObject>(GetTransientPackage(), Class);
       auto* const TorcherLayer = CastChecked<IITorcherLayer>(TorcherLayerObject);

       TorcherLayer->SetLayerDeviceType(TensorDeviceType);
       TorcherLayer->InitializeLayerParams(Gain, Confidence);
       return TorcherLayerObject;
}
