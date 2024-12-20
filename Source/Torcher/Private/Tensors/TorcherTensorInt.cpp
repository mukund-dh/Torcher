// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/TorcherTensorInt.h"


#define LOCTEXT_NAMESPACE "TorcherTensorInt"

UTorcherTensorInt::UTorcherTensorInt(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
{
	TensorScalarType = ETorcherTensorScalarType::Int;
}

// Explicit template instantiation
template TArray<int32> ITorcherTensorBase::GetData<int32>() noexcept;
template void ITorcherTensorBase::SetData<int32>(const TArray<int32>& InArray) noexcept;

#undef LOCTEXT_NAMESPACE