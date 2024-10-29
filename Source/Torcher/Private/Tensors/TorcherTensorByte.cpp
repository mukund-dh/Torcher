// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/TorcherTensorByte.h"

#define LOCTEXT_NAMESPACE "TorcherTensorByte"

UTorcherTensorByte::UTorcherTensorByte() noexcept
{
	ScalarType = ETorcherTensorScalarType::Byte;
}


#undef LOCTEXT_NAMESPACE