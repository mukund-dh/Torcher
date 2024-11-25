// Fill out your copyright notice in the Description page of Project Settings.


#include "Tensors/TorcherTensorFloat.h"

#define LOCTEXT_NAMESPACE "TorcherTensorFloat"

UTorcherTensorFloat::UTorcherTensorFloat(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
{
	TensorScalarType = ETorcherTensorScalarType::Float;
}

// Explicit template instantiation
template TArray<float> UTorcherTensorBase::GetData<float>() noexcept;
template void UTorcherTensorBase::SetData<float>(const TArray<float>& InArray) noexcept;

#undef LOCTEXT_NAMESPACE
