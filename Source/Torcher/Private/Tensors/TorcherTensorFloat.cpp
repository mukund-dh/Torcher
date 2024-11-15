// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorFloat.h"

#define LOCTEXT_NAMESPACE "TorcherTensorFloat"

UTorcherTensorFloat::UTorcherTensorFloat() noexcept
{
	//SetDeviceType(ETorcherTensorDeviceType::Cpu);
	ScalarType = ETorcherTensorScalarType::Float;
}

#undef LOCTEXT_NAMESPACE
