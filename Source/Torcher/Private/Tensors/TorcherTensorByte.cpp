// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/TorcherTensorByte.h"

#define LOCTEXT_NAMESPACE "TorcherTensorByte"

UTorcherTensorByte::UTorcherTensorByte(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
{
	TensorScalarType = ETorcherTensorScalarType::Byte;
}

// Explicit template instantiation
template TArray<uint8> UTorcherTensorBase::GetData<uint8>() noexcept;
template void UTorcherTensorBase::SetData<uint8>(const TArray<uint8>& InArray) noexcept;

#undef LOCTEXT_NAMESPACE