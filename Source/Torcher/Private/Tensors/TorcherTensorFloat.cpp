// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorFloat.h"

#define LOCTEXT_NAMESPACE "TorcherTensorFloat"

UTorcherTensorFloat::UTorcherTensorFloat(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
{
	TensorScalarType = ETorcherTensorScalarType::Float;
}

// Explicit template instantiation
template TArray<float> ITorcherTensorBase::GetData<float>() noexcept;
template void ITorcherTensorBase::SetData<float>(const TArray<float>& InArray) noexcept;

#undef LOCTEXT_NAMESPACE
