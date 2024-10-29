// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/TorcherTensorInt.h"


#define LOCTEXT_NAMESPACE "TorcherTensorInt"

UTorcherTensorInt::UTorcherTensorInt() noexcept
{
	ScalarType = ETorcherTensorScalarType::Int;
}


#undef LOCTEXT_NAMESPACE